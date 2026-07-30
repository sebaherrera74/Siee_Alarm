#ifndef TELEGRAM_MANAGER_H
#define TELEGRAM_MANAGER_H

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

enum class TelegramCommand
{
  None,
  Status,
  Arm,
  Disarm
};

class TelegramManager
{
  public:

    TelegramManager();

    void begin();

    bool sendMessage(const String& text);
    TelegramCommand getCommand();
    void update();

  private:

    WiFiClientSecure _client;
    UniversalTelegramBot* _bot;
    TelegramCommand _command = TelegramCommand::None;
};

#endif
