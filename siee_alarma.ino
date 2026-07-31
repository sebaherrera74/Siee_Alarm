
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

#include "AlarmCommand.h"
#include "AlarmEvent.h"

QueueHandle_t commandQueue;
QueueHandle_t eventQueue;

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

QueueHandle_t telegramQueue;

void TaskAlarm(void *pvParameters)
{

  Serial.println("TaskAlarm iniciada");
  while (true)
  {

    // ===== Recibir comandos de otras tareas =====
    AlarmCommand cmd;

    if (xQueueReceive(commandQueue, &cmd, 0) == pdTRUE)
    {
      Serial.print("Comando recibido: ");

      switch (cmd)
      {
        case AlarmCommand::Arm:
          Serial.println("ARM");
          break;

        case AlarmCommand::Disarm:
          Serial.println("DISARM");
          break;

        case AlarmCommand::Status:
          Serial.println("STATUS");
          break;

        case AlarmCommand::Panic:
          Serial.println("PANIC");
          break;

        default:
          break;
      }
    }
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
        case AlarmState::Disarmed:{

          AlarmEvent event = AlarmEvent::Disarmed;
          xQueueSend(eventQueue, &event, 0);

          buzzer.play(BuzzerPattern::Double);
          relay.off();
          break;
        }
        case AlarmState::ExitDelay:{
          AlarmEvent event = AlarmEvent::ExitDelay;
          xQueueSend(eventQueue, &event, 0);

          buzzer.play(BuzzerPattern::Periodic);
          relay.off();
          break;}

        case AlarmState::Armed:{
          AlarmEvent event = AlarmEvent::Armed;
          xQueueSend(eventQueue, &event, 0);

          buzzer.stop();
          relay.off();
          break;}

        case AlarmState::EntryDelay:{
          AlarmEvent event = AlarmEvent::EntryDelay;
          xQueueSend(eventQueue, &event, 0);
          buzzer.stop();
          relay.off();
          break;}

        case AlarmState::Triggered:{
          AlarmEvent event = AlarmEvent::Triggered;
          xQueueSend(eventQueue, &event, 0);

          buzzer.stop();
          relay.on();
          break;}
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
    wifi.update();

    telegram.update();

    TelegramCommand cmd = telegram.getCommand();

    switch (cmd)
    {
      case TelegramCommand::Status:
        Serial.println("Comando /estado");

        telegram.sendMessage("Estado recibido");
        break;

      case TelegramCommand::Arm:
        {
          AlarmCommand cmd = AlarmCommand::Arm;

          xQueueSend(commandQueue, &cmd, 0);

          telegram.sendMessage("Comando ARMAR enviado a TaskAlarm");

          break;
        }
        telegram.sendMessage("Comando ARMAR recibido");
        break;

      case TelegramCommand::Disarm:
        Serial.println("Comando /desarmar");

        telegram.sendMessage("Comando DESARMAR recibido");
        break;

      default:
        break;
    }

    AlarmEvent event;

if (xQueueReceive(eventQueue, &event, 0) == pdTRUE)
{
    switch (event)
    {
        case AlarmEvent::Armed:
            telegram.sendMessage("🟢 Alarma ARMADA");
            break;

        case AlarmEvent::Disarmed:
            telegram.sendMessage("⚪ Alarma DESARMADA");
            break;

        case AlarmEvent::ExitDelay:
            telegram.sendMessage("🟡 Retardo de salida");
            break;

        case AlarmEvent::EntryDelay:
            telegram.sendMessage("🟠 Retardo de entrada");
            break;

        case AlarmEvent::Triggered:
            telegram.sendMessage("🚨🚨 ALARMA DISPARADA 🚨🚨");
            break;

        default:
            break;
    }
}

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

  commandQueue = xQueueCreate(10, sizeof(AlarmCommand));
  eventQueue   = xQueueCreate(10, sizeof(AlarmEvent));
  if (commandQueue == NULL || eventQueue == NULL)
  {
    Serial.println("Error creando las Queue");
  }
  else
  {
    Serial.println("Queues creadas correctamente");
  }


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
