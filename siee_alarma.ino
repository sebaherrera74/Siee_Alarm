#include "config.h"
#include "Logger.h"
#include "Display.h"
#include "Sensor.h"
#include "Button.h"
#include "Alarm.h"

Display display;
Alarm alarm;
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
    alarm.begin();
}

void loop()
{

  buttonArm.update();
buttonMenu.update();
    if(buttonArm.wasPressed())
{
    alarm.toggle();

    if(alarm.isArmed())
    {
        Logger::info("Sistema ARMADO");

        display.showStatus("ARMADA");
    }
    else
    {
        Logger::info("Sistema DESARMADO");

        display.showStatus("DESARMADA");
    }
}
}
