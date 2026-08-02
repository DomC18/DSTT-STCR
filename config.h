#ifndef CONFIG_H
#define CONFIG_H

//==================================================
// System
//==================================================

#define BAUD_RATE               19200
#define DEFAULT_DELAY           1000

//==================================================
// SD Card
//==================================================

#define SPI_SCK                 D8
#define SPI_MISO                D6
#define SPI_MOSI                D10
#define SD_CS                   D3

//==================================================
// Pressure Sensor
//==================================================

#define PRESSURE_POWER          0
#define PMIN_START              0x13
#define PMAX_START              0x15
#define PRESSURE_ADDRESS        0x40
#define PRESSURE_REQUEST        0xAC
#define PRESSURE_EOC            D3
#define I2C_SDA                 D4
#define I2C_SCL                 D5

//==================================================
// State Manager
//==================================================

#define DRY_COUNT_THRESHOLD     3
#define DRY_THRESHOLD_MARGIN    0.05f
#define WET_THRESHOLD_MARGIN    0.10f
#define SURFACE_WINDOW_SECONDS  60
#define SUBMERGED_INTERVAL_SEC  3600
#define SURFACED_INTERVAL_SEC   1
#define DRY_BASELINE            1.0095f

//==================================================
// Environmental Constants
//==================================================

#define ATM_PRESSURE_BAR        1.01325f
#define WATER_DENSITY           997.0f
#define SEAWATER_DENSITY        1025.0f
#define GRAVITY                 9.80665f

//==================================================
// Sleep
//==================================================

#define LOG_INTERVAL_SECONDS    30
#define SURFACED_INTERVAL_SEC   60
#define SUBMERGED_INTERVAL_SEC  3600
#define UNIX_TIME               1000000ULL

#endif
