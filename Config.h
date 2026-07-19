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

//==================================================
// Entradas
//==================================================

constexpr uint8_t PIN_DOOR = 26;
constexpr uint8_t PIN_PIR  = 27;
//==================================================
// Indicadores
//==================================================


//==================================================
// Botones
//==================================================

constexpr uint8_t PIN_BUTTON_ARM  = 33;
constexpr uint8_t PIN_BUTTON_MENU = 32;

//==================================================
// Tiempos
//==================================================

constexpr uint16_t EXIT_DELAY_SEC = 20;
constexpr uint16_t ENTRY_DELAY_SEC = 15;

constexpr uint8_t PIN_BUZZER = 18;

constexpr uint8_t PIN_RELAY=16;
// Nivel lógico que activa el relé
constexpr uint8_t RELAY_ON  = LOW;
constexpr uint8_t RELAY_OFF = HIGH;

#endif
