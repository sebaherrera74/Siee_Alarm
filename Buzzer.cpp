#include "Buzzer.h"



#define BUZZER_CHANNEL 0
#define BUZZER_FREQ    4000
#define BUZZER_RES     8

Buzzer::Buzzer(uint8_t pin)
: _pin(pin),
  _mode(BuzzerMode::Off),
  _output(false),
  _beeping(false),
  _startTime(0),
  _duration(0)
{
}

void Buzzer::begin()
{
    ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RES);
    ledcAttachPin(_pin, BUZZER_CHANNEL);
}

void Buzzer::on()
{
    ledcWrite(BUZZER_CHANNEL, 128);   // 50% duty cycle
}

void Buzzer::off()
{
    ledcWrite(BUZZER_CHANNEL, 0);
}

void Buzzer::beep(uint16_t duration)
{
    _duration = duration;
    _startTime = millis();
    _beeping = true;

    on();
}

void Buzzer::update()
{
    switch (_mode)
    {
        case BuzzerMode::Off:

            off();

            break;

        case BuzzerMode::Periodic:

            if (_timer.expired())
            {
                _output = !_output;

                if (_output)
                    on();
                else
                    off();

                _timer.start(250);
            }

            break;

        default:
            break;
    }
}

void Buzzer::setMode(BuzzerMode mode)
{
    if (_mode == mode)
        return;

    _mode = mode;

    off();

    _output = false;

    if (_mode == BuzzerMode::Periodic)
    {
        _timer.start(1000);
    }
}
