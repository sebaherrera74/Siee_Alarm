#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
public:

    Button(uint8_t pin);

    void begin();

    void update();

    bool isPressed() const;

    bool wasPressed();

private:

    uint8_t _pin;

    bool _state;
    bool _lastState;

    bool _pressedEvent;

    unsigned long _lastChangeTime;
};

#endif
