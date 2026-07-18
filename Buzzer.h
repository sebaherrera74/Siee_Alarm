#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "Timmer.h"

enum class BuzzerPattern
{
    None,
    Single,
    Double,
    Periodic
};

class Buzzer
{
public:

    explicit Buzzer(uint8_t pin);

    void begin();

    void update();

    void play(BuzzerPattern pattern);

    void stop();
    void test();

private:

    void on();
    void off();

    uint8_t _pin;

    Timer _timer;

    bool _output;

    uint8_t _step;

    BuzzerPattern _pattern;
};

#endif // BUZZER_H
