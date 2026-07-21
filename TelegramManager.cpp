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
