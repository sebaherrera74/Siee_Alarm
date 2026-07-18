#include "Buzzer.h"

#define BUZZER_CHANNEL 0
#define BUZZER_FREQ    4000
#define BUZZER_RES     8

#define SINGLE_BEEP_TIME     100
#define PERIODIC_ON_TIME     100
#define PERIODIC_OFF_TIME    900
#define DOUBLE_ON_TIME      100
#define DOUBLE_OFF_TIME     100

Buzzer::Buzzer(uint8_t pin)
  : _pin(pin),
    _output(false),
    _step(0),
    _pattern(BuzzerPattern::None)
{
}

void Buzzer::begin()
{
  ledcSetup(BUZZER_CHANNEL, BUZZER_FREQ, BUZZER_RES);
  ledcAttachPin(_pin, BUZZER_CHANNEL);

  off();
}

void Buzzer::on()
{
  ledcWrite(BUZZER_CHANNEL, 128);
  _output = true;
}

void Buzzer::off()
{
  ledcWrite(BUZZER_CHANNEL, 0);
  _output = false;
}

void Buzzer::play(BuzzerPattern pattern)
{
  if (_pattern == pattern)
    return;

  off();

  _pattern = pattern;
  _step = 0;
}
void Buzzer::stop()
{
  _pattern = BuzzerPattern::None;
  _step = 0;
  off();
}

void Buzzer::update()
{
  switch (_pattern)
  {
    case BuzzerPattern::None:
      break;

    case BuzzerPattern::Single:

      switch (_step)
      {
        case 0:

          on();

          _timer.start(SINGLE_BEEP_TIME);

          _step = 1;

          break;

        case 1:

          if (_timer.expired())
          {
            off();

            _pattern = BuzzerPattern::None;

            _step = 0;
          }

          break;
      }

      break;


    case BuzzerPattern::Double:

      switch (_step)
      {
        case 0:

          on();

          _timer.start(DOUBLE_ON_TIME);

          _step = 1;

          break;

        case 1:

          if (_timer.expired())
          {
            off();

            _timer.start(DOUBLE_OFF_TIME);

            _step = 2;
          }

          break;

        case 2:

          if (_timer.expired())
          {
            on();

            _timer.start(DOUBLE_OFF_TIME);

            _step = 3;
          }

          break;

        case 3:

          if (_timer.expired())
          {
            off();

            _pattern = BuzzerPattern::None;

            _step = 0;
          }

          break;
      }

      break;
      break;

    case BuzzerPattern::Periodic:


      switch (_step)
      {
        case 0:

          on();

          _timer.start(PERIODIC_ON_TIME);      // Buzzer encendido 100 ms

          _step = 1;

          break;

        case 1:

          if (_timer.expired())
          {
            off();

            _timer.start(PERIODIC_OFF_TIME);  // Silencio 900 ms

            _step = 2;
          }

          break;

        case 2:

          if (_timer.expired())
          {
            _step = 0;
          }

          break;
      }

      break;

  }
}


void Buzzer::test()
{
  on();
}
