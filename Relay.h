#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>
#include "Timmer.h"


class Relay
{
public:
    explicit Relay(uint8_t pin);

    void begin();

    void on();

    void off();

    bool isOn() const;

private:
    uint8_t _pin;

    bool _state;

   
};



#endif // RELAY_H
