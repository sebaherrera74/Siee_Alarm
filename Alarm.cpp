#include "Alarm.h"

void Alarm::begin()
{
    _state = AlarmState::Disarmed;
}

void Alarm::arm()
{
    _state = AlarmState::Armed;
}

void Alarm::disarm()
{
    _state = AlarmState::Disarmed;
}

void Alarm::toggle()
{
    if (_state == AlarmState::Disarmed)
        arm();
    else
        disarm();
}

AlarmState Alarm::getState() const
{
    return _state;
}

bool Alarm::isArmed() const
{
    return (_state == AlarmState::Armed);
}
