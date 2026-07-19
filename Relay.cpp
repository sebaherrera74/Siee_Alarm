#include "Relay.h"
#include "Config.h"

Relay::Relay(uint8_t pin)
  : _pin(pin),
    _state(false)
   {
}

void Relay::begin()
{
    pinMode(_pin, OUTPUT);

    off();
  
}

void Relay::on()
{
  digitalWrite(_pin, RELAY_ON );

    _state = true;
}

void Relay::off()
{
   digitalWrite(_pin, RELAY_OFF );

    _state = false;
  
}

bool Relay::isOn() const
{
    return _state;
  
}
