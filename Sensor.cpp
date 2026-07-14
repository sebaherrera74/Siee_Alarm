#include "Sensor.h"

Sensor::Sensor(uint8_t pin)
{
    _pin = pin;

    _state = false;
    _lastState = false;
    _changed = false;
}

void Sensor::begin()
{
    pinMode(_pin, INPUT_PULLUP);

    _state = digitalRead(_pin);
    _lastState = _state;
}

void Sensor::update()
{
    _lastState = _state;

    _state = digitalRead(_pin);

    _changed = (_state != _lastState);
}

bool Sensor::isActive() const
{
    return _state;
}

bool Sensor::hasChanged() const
{
    return _changed;
}
