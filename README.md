# SIEE Alarm

Sistema de alarma para el hogar basado en ESP32, desarrollado como un proyecto modular y escalable por **SIEE (Sistemas Integrales Electrónicos Eléctricos)**.

## Descripción

SIEE Alarm tiene como objetivo desarrollar una central de alarma confiable, sencilla de instalar y fácil de ampliar. El proyecto está pensado inicialmente para aplicaciones residenciales, utilizando un ESP32 como unidad central y una arquitectura de software modular que facilite futuras mejoras.

El desarrollo se realiza de forma incremental, incorporando y validando cada módulo antes de añadir nuevas funcionalidades.

## Hardware

* ESP32 DevKit V1
* Display OLED SSD1306 128x64 (I²C)
* Sensor magnético para puertas o ventanas
* Sensor PIR (inicialmente simulado durante el desarrollo)
* Buzzer
* LED de estado
* Pulsadores de control

## Funciones previstas

* Armado y desarmado del sistema
* Retardo de salida
* Retardo de entrada
* Detección de intrusión
* Activación de sirena
* Indicaciones mediante display OLED
* Señalización por LEDs
* Registro de eventos
* Configuración mediante interfaz web (futuras versiones)
* Notificaciones remotas (futuras versiones)

## Arquitectura del software

El proyecto está organizado en módulos independientes para facilitar el mantenimiento y la reutilización del código.

* Configuración
* Logger
* Display
* Sensores
* Temporizadores
* Control de la alarma
* Buzzer

## Estado del proyecto

**Versión:** 0.1.0

Actualmente se encuentra en etapa de desarrollo, comenzando por la implementación de la arquitectura base y la lógica principal del sistema.

