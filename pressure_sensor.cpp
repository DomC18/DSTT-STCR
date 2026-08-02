#include <Arduino.h>
#include <Wire.h>
#include "pressure_sensor.h"
#include "config.h"

float PRESSURE_MIN;
float PRESSURE_MAX;

/*
    * Reads one 16-bit memory cell from the Keller sensor's MTP memory.
    *
    * According to the Keller protocol:
    *
    * 1. Send the memory address to the sensor
    * 2. Wait approximately 0.6 ms
    * 3. Read back:
    *      STATUS
    *      MEM_MSB
    *      MEM_LSB
    *
    * The returned memory value is therefore:
    *      value = (MSB << 8) | LSB
    *
    * Returns:
    *      true  = successful read
    *      false = communication or sensor error
*/
bool readMemoryWord(uint8_t address, uint16_t &value) {
    // Start talking to I2C
    Wire.beginTransmission(PRESSURE_ADDRESS);
    Wire.write(address);

    // Send Request: STATUS, MEM_MSB, MEM_LSB
    // Directly from docs
    if (Wire.endTransmission() != 0) {
        Serial.println("error in transmission of memory");
        return false;
    }
    delay(1);
    if (Wire.requestFrom(PRESSURE_ADDRESS, (uint8_t)3) != 3) {
        Serial.println("error in request of memory");
        return false;
    }

    uint8_t status = Wire.read();
    bool busy = status & 0x80;
    uint8_t mode = (status >> 5) & 0x03;
    bool memError = status & 0x08;

    if (busy) {
        Serial.println("Sensor busy");
        return false;
    }

    if (memError) {
        Serial.println("Memory checksum error");
        return false;
    }

    // Reconstruct the 16-bit memory value.
    value = ((uint16_t)Wire.read() << 8) | Wire.read();

    return true;
}

/*
    * Reads a 32-bit floating-point value stored in
    * two consecutive memory locations.
    *
    * Keller stores calibration values as: 
    *      0x13 + 0x14 = Pmin
    *      0x15 + 0x16 = Pmax
    *
    * Each memory address contains 16 bits.
    *
    * Therefore:
    *      upper 16 bits
    *      +
    *      lower 16 bits
    *      =
    *      32-bit IEEE754 float
    *
    * Returns:
    *      true  = success
    *      false = failure
*/
bool readMemoryFloat(uint8_t addressMSB, float &value) {
    uint16_t highWord;
    uint16_t lowWord;

    // Read upper, then lower half
    if (!readMemoryWord(addressMSB, highWord)) {
        Serial.println("error reading high word");
        return false;
    }
    if (!readMemoryWord(addressMSB + 1, lowWord)) {
        Serial.println("error reading low word");
        return false;
    }

    // Reinterpret the raw 32-bit value as a float.
    union {
        uint32_t raw;
        float number;
    } data;

    // Reconstruct complete 32-bit value.
    data.raw = ((uint32_t)highWord << 16) | lowWord;
    value = data.number;

    return true;
}

/*
    * Reads pressure calibration range from the sensor.
    *
    * Example:
    *   PRESSURE_MIN = 0.0 bar
    *   PRESSURE_MAX = 10.0 bar
    *
    * These values are used later to convert
    * raw pressure counts into real pressure.
*/
bool readCalibration() {
    if (!readMemoryFloat(PMIN_START, PRESSURE_MIN)) return false;
    if (!readMemoryFloat(PMAX_START, PRESSURE_MAX)) return false;
    Serial.print("Pressure Minimum: ");
    Serial.println(PRESSURE_MIN);
    Serial.print("Pressure Maximum: ");
    Serial.println(PRESSURE_MAX);
    Serial.println();
    
    return true;
}

/*
    * Initializes I2C communication and reads
    * calibration data from the sensor.
    *
    * This should be called once in setup().
*/
bool initPressureSensor() { 
    Wire.begin(I2C_SDA, I2C_SCL); 
    Wire.setClock(50000);

    if (!readCalibration()) { 
        Serial.println("error reading calibration"); 
        return false; 
    } 

    return true; 
}

/*
    * Converts pressure into water depth.
    *
    * 1. Remove atmospheric pressure
    *      (surface pressure)
    *
    * 2. Convert bar -> Pascals
    *
    * 3. Apply hydrostatic equation:
    *      depth = P / (ρg)
    *      P = pressure (Pa)
    *      ρ = water density
    *      g = gravity
*/
float calculateDepth(PressureData &pressureData) {
    float pressurePa = (pressureData.pressureBar - ATM_PRESSURE_BAR) * 100000.0f;
    if (pressurePa < 0) pressurePa = 0;
    
    return pressurePa / (SEAWATER_DENSITY * GRAVITY);
}

/*
    * Reads one complete measurement from the sensor.
    *
    * Returns:
    *   pressureBar
    *   temperatureC
    *   depthM
*/
bool readPressureSensor(PressureData &pressureData) {
    Wire.beginTransmission(PRESSURE_ADDRESS);
    Wire.write(PRESSURE_REQUEST);
    
    /*
        * Read 5-byte response.
        * Byte 0 = Status
        * Byte 1 = Pressure MSB
        * Byte 2 = Pressure LSB
        * Byte 3 = Temperature MSB
        * Byte 4 = Temperature LSB
    */
    if (Wire.endTransmission() != 0) {
        Serial.println("error in transmission of pressure");
        return false;
    }
    delay(15);
    if (Wire.requestFrom(PRESSURE_ADDRESS, (uint8_t)5) != 5) {
        Serial.println("error in request of pressure");
        return false;
    }
    
    uint8_t status = Wire.read();
    uint16_t pressureRaw = (Wire.read() << 8) | Wire.read();
    uint16_t temperatureRaw = (Wire.read() << 8) | Wire.read();
    pressureData.pressureRaw = pressureRaw;
    pressureData.temperatureRaw = temperatureRaw;

    // Convert raw pressure, temperature into correct units and values. Taken directly from docs
    // Keller pressure conversion: 16384 -> Pmin; 49152 -> Pmax
    pressureData.pressureBar = (((float)pressureRaw - 16384.0f) * (PRESSURE_MAX - PRESSURE_MIN) / 32768.0f) + PRESSURE_MIN;
    pressureData.temperatureC = ((((float)(temperatureRaw >> 4)) - 24.0f) * 0.05f) - 50.0f;
    pressureData.depthM = calculateDepth(pressureData);

    return true;
}

// Prints current sensor readings to the Serial Monitor.
void printPressureData(PressureData &pressureData) {
    Serial.print("Pressure (raw): ");
    Serial.println(pressureData.pressureRaw, 3);
    Serial.print("Pressure (bar): ");
    Serial.println(pressureData.pressureBar, 3);
    Serial.print("Temperature (raw): ");
    Serial.println(pressureData.temperatureRaw, 3);
    Serial.print("Temperature (C): ");
    Serial.println(pressureData.temperatureC, 2);
    Serial.print("Depth (m): ");
    Serial.println(pressureData.depthM, 3);
    
    Serial.print("State: ");
    if (currentstate == SUBMERGED) {
        Serial.println("submerged");
    } else {
        Serial.println("surfaced");
    }
}
