#include "Alarm.h"

void Alarm::begin()
{
    _armed = false;
}

void Alarm::arm()
{
    _armed = true;
}

void Alarm::disarm()
{
    _armed = false;
}

bool Alarm::isArmed() const
{
    return _armed;
}
