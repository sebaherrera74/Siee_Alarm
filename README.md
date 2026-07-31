
# SIEE Alarm

Sistema de alarma residencial desarrollado sobre ESP32 utilizando FreeRTOS y una arquitectura basada en eventos.

El proyecto busca ser una plataforma modular y escalable para futuras versiones con teclado matricial, RFID, aplicación móvil, MQTT, Home Assistant y monitoreo remoto.

---

## Características

- ESP32
- FreeRTOS
- Máquina de estados
- Comunicación mediante Queues
- Pantalla OLED SSD1306
- Sensores magnéticos (NC)
- Sensores PIR (NC)
- Buzzer
- Relé para sirena
- Bot de Telegram
- WiFi

---

## Arquitectura

El firmware está dividido en tareas independientes.

```
                Telegram
                    │
                    ▼
             TaskTelegram
                    │
             commandQueue
                    │
                    ▼
               TaskAlarm
                    │
            Máquina de estados
                    │
              eventQueue
                    │
                    ▼
             TaskTelegram
```

Las tareas nunca llaman directamente a otras clases.

Toda la comunicación se realiza mediante colas de FreeRTOS.

---

## Estados de la alarma

- Disarmed
- ExitDelay
- Armed
- EntryDelay
- Triggered

---

## Eventos

- Armed
- Disarmed
- ExitDelay
- EntryDelay
- Triggered

---

## Comandos

Actualmente soportados desde Telegram:

- /armar
- /desarmar
- /estado

---

## Hardware

- ESP32 DevKit
- Display OLED SSD1306 I2C
- Sensor magnético NC
- Sensor PIR NC
- Relé
- Buzzer

---

## Librerías

- WiFi
- UniversalTelegramBot
- ArduinoJson
- Adafruit SSD1306
- Adafruit GFX

---

## Estado del proyecto

Versión actual: **v0.6**

### Funcionalidades implementadas

- Máquina de estados
- Display OLED
- Buzzer
- Relé
- Telegram
- FreeRTOS
- TaskAlarm
- TaskTelegram
- commandQueue
- eventQueue

---

## Próximas funcionalidades

- Registro de eventos
- Teclado matricial 4x4
- RFID
- OTA
- MQTT
- Home Assistant
- Aplicación móvil
- PCB propia

## Estado del proyecto

## Historial

### v0.6
- Arquitectura basada en eventos
- commandQueue
- eventQueue
- Separación de comunicaciones

### v0.5
- Migración a FreeRTOS
- TaskAlarm
- TaskTelegram

### v0.4
- Integración con Telegram

### v0.3
- Máquina de estados

### v0.2
- Display OLED

### v0.1
- Primera versión funcional