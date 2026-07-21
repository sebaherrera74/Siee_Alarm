
#include "config.h"
#include "Logger.h"
#include "Display.h"
#include "Sensor.h"
#include "Button.h"
#include "Alarm.h"
#include "Timmer.h"
#include "Buzzer.h"
#include "Relay.h"
#include "WiFiManager.h"
#include "TelegramManager.h"

Timer testTimer;
Display display;
Alarm alarmSystem;
Sensor door(PIN_DOOR);
Sensor pir(PIN_PIR);
Buzzer buzzer(PIN_BUZZER);



Button buttonArm(PIN_BUTTON_ARM);

Button buttonMenu(PIN_BUTTON_MENU);

Relay relay(PIN_RELAY);

WiFiManager wifi;

TelegramManager telegram;
void setup()
{ Serial.begin(115200);

  //logger.begin();

  display.begin();

  door.begin();
  pir.begin();

  buttonArm.begin();
  buttonMenu.begin();

  buzzer.begin();

  alarmSystem.begin();
  relay.begin();
  wifi.begin();

  telegram.begin();

  telegram.sendMessage("✅ SIEE Alarm iniciada correctamente.");

}



void loop()
{
  // Actualizar entradas
  buttonArm.update();
  buttonMenu.update();

  door.update();
  pir.update();


  // Procesar eventos de entrada

  if (buttonArm.wasPressed())
  {
    alarmSystem.toggle();
  }

  if (alarmSystem.isArmed())
  {
    if (door.isActive() || pir.isActive())
    {
      alarmSystem.triggerEntryDelay();
    }
  }

  // Actualizar lógica
  alarmSystem.update();



  // Eventos (solo cuando cambia el estado)
  if (alarmSystem.stateChanged())
  {
    switch (alarmSystem.getState())
    {
      case AlarmState::Disarmed:
        buzzer.play(BuzzerPattern::Double);
        relay.off();
        break;

      case AlarmState::ExitDelay:
        buzzer.play(BuzzerPattern::Periodic);
        relay.off();
        break;

      case AlarmState::Armed:
        buzzer.stop();
        relay.off();
        break;

      case AlarmState::EntryDelay:
        buzzer.stop();
        relay.off();
        break;

      case AlarmState::Triggered:
        buzzer.stop();
        relay.on();
        break;
    }
  }

  // Actualizar buzzer
  buzzer.update();

  // Actualizar display
  switch (alarmSystem.getState())
  {
    case AlarmState::Disarmed:
      display.showStatus(false, door.isActive(), pir.isActive());
      break;

    case AlarmState::ExitDelay:
      display.showExitDelay(alarmSystem.exitDelayRemaining());
      break;

    case AlarmState::Armed:
      display.showStatus(true, door.isActive(), pir.isActive());
      break;

    case AlarmState::EntryDelay:
      display.showEntryDelay(alarmSystem.entryDelayRemaining());
      break;

    case AlarmState::Triggered:
      display.showAlarm();
      break;
  }
  
  wifi.update();
}
