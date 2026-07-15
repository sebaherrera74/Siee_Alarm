#include "config.h"
#include "Logger.h"
#include "Display.h"
#include "Sensor.h"
#include "Button.h"
#include "Alarm.h"
#include "Timmer.h"

Timer testTimer;
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

    display.showStatus(false,door.isActive(), pir.isActive());

    door.begin();
    pir.begin();

    Logger::info("Sensores inicializados");

    buttonArm.begin();
    buttonMenu.begin();

    Logger::info("Botones inicializados");
    alarm.begin();
    testTimer.start(5000);

    Logger::info("Timer iniciado");
}

void loop()
{
    // Entradas
    buttonArm.update();
    buttonMenu.update();

    door.update();
    pir.update();

    // Lógica
    alarm.update();

    if (buttonArm.wasPressed())
    {
        alarm.toggle();
    }

    // Interfaz
    switch (alarm.getState())
    {
        case AlarmState::Disarmed:

            display.showStatus(
                false,
                door.isActive(),
                pir.isActive());
            break;

        case AlarmState::ExitDelay:

            display.showExitDelay(
                alarm.exitDelayRemaining());
            break;

        case AlarmState::Armed:

            display.showStatus(
                true,
                door.isActive(),
                pir.isActive());
            break;

        default:
            break;
    }
}
