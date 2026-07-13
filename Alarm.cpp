#include "Alarm.h"

bool Alarm::begin()
{
    _state = DISARMED;
    return true;
}

void Alarm::update()
{

}

void Alarm::arm()
{
    _state = ARMED;
}

void Alarm::disarm()
{
    _state = DISARMED;
}

void Alarm::trigger()
{
    _state = ALARM_TRIGGERED;
}

AlarmState Alarm::getState()
{
    return _state;
}
