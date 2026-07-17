#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer
{
public:
    explicit Buzzer(uint8_t pin);

    void begin();

    void on();
    void off();

    void beep(uint16_t duration);

    void update();

private:
    uint8_t _pin;

    bool _beeping;

    unsigned long _startTime;
    uint16_t _duration;
};

#endif
