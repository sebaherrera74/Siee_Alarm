#include "Logger.h"

void Logger::begin(unsigned long baudRate)
{
    Serial.begin(baudRate);

    while (!Serial)
    {
        delay(10);
    }

    Serial.println();
    Serial.println("========================================");
    Serial.println("             SIEE ALARM");
    Serial.println("========================================");
}

void Logger::info(const char *message)
{
    Serial.print("[INFO ] ");
    Serial.println(message);
}

void Logger::warning(const char *message)
{
    Serial.print("[WARN ] ");
    Serial.println(message);
}

void Logger::error(const char *message)
{
    Serial.print("[ERROR] ");
    Serial.println(message);
}

void Logger::debug(const char *message)
{
    Serial.print("[DEBUG] ");
    Serial.println(message);
}
