#include "Button.h"

constexpr uint16_t DEBOUNCE_TIME = 20;

Button::Button(uint8_t pin)
{
    _pin = pin;

    _state = HIGH;
    _lastState = HIGH;

    _pressedEvent = false;

    _lastChangeTime = 0;
}

void Button::begin()
{
    pinMode(_pin, INPUT_PULLUP);

    _state = digitalRead(_pin);
    _lastState = _state;
}

void Button::update()
{
    bool reading = digitalRead(_pin);

    _pressedEvent = false;

    if (reading != _lastState)
    {
        _lastChangeTime = millis();
        _lastState = reading;
    }

    if ((millis() - _lastChangeTime) > DEBOUNCE_TIME)
    {
        if (reading != _state)
        {
            _state = reading;

            if (_state == LOW)
            {
                _pressedEvent = true;
            }
        }
    }
}

bool Button::isPressed() const
{
    return (_state == LOW);
}

bool Button::wasPressed()
{
    return _pressedEvent;
}
