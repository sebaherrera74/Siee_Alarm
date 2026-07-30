
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

void TaskAlarm(void *pvParameters)
{

  Serial.println("TaskAlarm iniciada");
  while (true)
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

    // Detectar un único cambio de estado
    bool stateChanged = alarmSystem.stateChanged();

    if (stateChanged)
    {
      switch (alarmSystem.getState())
      {
        case AlarmState::Disarmed:
          //telegram.sendMessage("⚪ Alarma DESARMADA");
          buzzer.play(BuzzerPattern::Double);
          relay.off();
          break;

        case AlarmState::ExitDelay:
          //telegram.sendMessage("🟡 Retardo de salida");
          buzzer.play(BuzzerPattern::Periodic);
          relay.off();
          break;

        case AlarmState::Armed:
          //telegram.sendMessage("🟢 Alarma ARMADA");
          buzzer.stop();
          relay.off();
          break;

        case AlarmState::EntryDelay:
          //telegram.sendMessage("🟠 Retardo de entrada");
          buzzer.stop();
          relay.off();
          break;

        case AlarmState::Triggered:
          //telegram.sendMessage("🚨🚨 ALARMA DISPARADA 🚨🚨");
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
    //telegram.update();
    //TelegramCommand cmd = telegram.getCommand();

    /*

      switch (cmd)
      {
       case TelegramCommand::Status:
           telegram.sendMessage("Comando /estado recibido");
           break;

       case TelegramCommand::Arm:
           telegram.sendMessage("Comando /armar recibido");
           break;

       case TelegramCommand::Disarm:
           telegram.sendMessage("Comando /desarmar recibido");
           break;

       default:
           break;
      }*/
    vTaskDelay(1);

  }
}


void TaskTelegram(void *pvParameters)
{
  Serial.println("TaskTelegram iniciada");
  while (true)
  {
    telegram.update();

    vTaskDelay(pdMS_TO_TICKS(500));
  }
}
void setup()
{

  Serial.begin(115200);

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
  xTaskCreatePinnedToCore(
    TaskAlarm,      // función
    "TaskAlarm",    // nombre
    4096,           // stack
    NULL,           // parámetro
    2,              // prioridad
    NULL,           // handle
    1               // Core
  );

  xTaskCreatePinnedToCore(
    TaskTelegram,        // función
    "TaskTelegram",     // nombre
    8192,               // stack
    NULL,                // parámetro
    1,                    // prioridad
    NULL,               // handle
    0                   // Core
  );

}



void loop()
{

}
