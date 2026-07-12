#ifndef CONFIG_H
#define CONFIG_H

//==================================================
// System
//==================================================

#define DEFAULT_DELAY           1000
#define BAUD_RATE               19200

//==================================================
// SD Card
//==================================================

#define SPI_SCK                 8
#define SPI_MOSI                10
#define SPI_MISO                9
#define SD_CS                   2

//==================================================
// Temperature Sensor
//==================================================

#define DS18B20_PIN             3

//==================================================
// Pressure Sensor
//==================================================

#define PRESSURE_ADDRESS        0x40
#define PRESSURE_MIN            0.0f
#define PRESSURE_MAX            10.0f

//==================================================
// Environmental Constants
//==================================================

#define ATM_PRESSURE_BAR        1.01325f
#define WATER_DENSITY           997.0f
#define GRAVITY                 9.80665f

//==================================================
// Sleep
//==================================================

#define LOG_INTERVAL_SECONDS    30
#define UNIX_TIME               1000000ULL

#endif
