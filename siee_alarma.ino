#include "config.h"
#include "Alarm.h"

Alarm alarm;

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("==========================");
    Serial.println(PROJECT_NAME);
    Serial.println(VERSION);
    Serial.println("==========================");

    alarm.begin();

    Serial.println("Sistema iniciado.");
}

void loop()
{
    alarm.update();
}
