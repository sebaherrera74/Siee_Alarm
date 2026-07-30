#include "TelegramManager.h"
#include "config.h"

TelegramManager::TelegramManager()
{
  _bot = nullptr;
}

void TelegramManager::begin()
{
  Serial.println("Inicializando Telegram...");

  _client.setInsecure();

  _bot = new UniversalTelegramBot(TELEGRAM_BOT_TOKEN, _client);

  Serial.println("Telegram listo.");
}

bool TelegramManager::sendMessage(const String& text)
{
  if (_bot == nullptr)
  {
    Serial.println("ERROR: Bot no inicializado.");
    return false;
  }

  Serial.println("Enviando mensaje...");

  bool ok = _bot->sendMessage(TELEGRAM_CHAT_ID, text);

  Serial.print("Resultado = ");
  Serial.println(ok);

  return ok;
}

void TelegramManager::update()
{
  if (_bot == nullptr)
    return;

  int numNewMessages = _bot->getUpdates(_bot->last_message_received + 1);

  while (numNewMessages)
  {
    for (int i = 0; i < numNewMessages; i++)
    {
      Serial.print("Mensaje recibido: ");
      Serial.println(_bot->messages[i].text);
      String text = _bot->messages[i].text;

      if (text == "/estado")
        _command = TelegramCommand::Status;

      else if (text == "/armar")
        _command = TelegramCommand::Arm;

      else if (text == "/desarmar")
        _command = TelegramCommand::Disarm;
    }

    numNewMessages = _bot->getUpdates(_bot->last_message_received + 1);
  }
}

TelegramCommand TelegramManager::getCommand()
{
  TelegramCommand cmd = _command;
  _command = TelegramCommand::None;
  return cmd;
}
