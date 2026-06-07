#ifndef CONFIG_H
#define CONFIG_H

#define I2C_SDA                6
#define I2C_SCL                7

#define SPI_SCK                4
#define SPI_MISO               2
#define SPI_MOSI               3

#define SD_CS                  5

#define ADS1220_CS             9
#define ADS1220_DRDY           10

#define RTC_WAKE_PIN           GPIO_NUM_0

#define SENSOR_MIN_V           0.5f
#define SENSOR_MAX_V           2.5f
#define SENSOR_MAX_PSI         100.0f

#define ADC_REFERENCE          2.048f

#endif