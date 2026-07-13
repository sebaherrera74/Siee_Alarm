#ifndef CONFIG_H
#define CONFIG_H

//==================================================
// Proyecto
//==================================================

#define PROJECT_NAME    "SIEE Alarm"
#define VERSION         "0.1.0"

//==================================================
// Display OLED
//==================================================

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64

#define OLED_ADDRESS    0x3C

#define SDA_PIN         21
#define SCL_PIN         22

//==================================================
// Sensores
//==================================================

#define PIN_MAGNETIC    26
#define PIN_PIR         27

//==================================================
// Indicadores
//==================================================

#define PIN_BUZZER      25

#define PIN_LED_RED     2
#define PIN_LED_GREEN   4

#endif
