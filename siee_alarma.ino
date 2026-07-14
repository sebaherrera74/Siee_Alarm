#include "config.h"
#include "Logger.h"
#include "Display.h"
#include "Sensor.h"
#include "Button.h"

Display display;

Sensor door(PIN_DOOR);
Sensor pir(PIN_PIR);

Button buttonArm(PIN_BUTTON_ARM);

Button buttonMenu(PIN_BUTTON_MENU);
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

    buttonArm.begin();
    buttonMenu.begin();

    Logger::info("Botones inicializados");
}

void loop()
{
    buttonArm.update();
    buttonMenu.update();

if (buttonArm.wasPressed())
{
    Logger::info("Boton ARM");
}

if (buttonMenu.wasPressed())
{
    Logger::info("Boton MENU");
}
}
