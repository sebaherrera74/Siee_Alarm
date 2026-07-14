#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{
public:

    Sensor(uint8_t pin);

    void begin();

    void update();

    bool isActive() const;

    bool hasChanged() const;

private:

    uint8_t _pin;

    bool _state;

    bool _lastState;

    bool _changed;
};

#endif
