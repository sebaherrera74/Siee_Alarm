#include "config.h"
#include "Logger.h"
#include "Display.h"
#include "Sensor.h"

Display display;

Sensor door(PIN_DOOR);
Sensor pir(PIN_PIR);

void setup()
{
    Logger::begin();

    Logger::info("Iniciando...");

    if(display.begin())
        Logger::info("Display OK");
    else
        Logger::error("Display NO encontrado");

    display.showStatus("DESARMADA");

    door.begin();
    pir.begin();

    Logger::info("Sensores inicializados");
}

void loop()
{
    door.update();
    pir.update();

    if (door.hasChanged())
    {
        if (door.isActive())
            Logger::warning("Puerta ABIERTA");
        else
            Logger::info("Puerta CERRADA");
    }

    if (pir.hasChanged())
    {
        if (pir.isActive())
            Logger::warning("Movimiento detectado");
        else
            Logger::info("Sin movimiento");
    }

    delay(50);
}
