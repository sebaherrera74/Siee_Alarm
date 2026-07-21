#ifndef TELEGRAM_MANAGER_H
#define TELEGRAM_MANAGER_H

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

class TelegramManager
{
public:

    TelegramManager();

    void begin();

    bool sendMessage(const String& text);

private:

    WiFiClientSecure _client;
    UniversalTelegramBot* _bot;
};

#endif
