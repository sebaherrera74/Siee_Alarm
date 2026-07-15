#include "Alarm.h"
#include "config.h"
void Alarm::begin()
{
    _state = AlarmState::Disarmed;
}

void Alarm::arm()
{
    _state = AlarmState::ExitDelay;

    _exitTimer.start(EXIT_DELAY_SEC * 1000);
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

uint8_t Alarm::exitDelayRemaining() const
{
    return _exitTimer.remaining() / 1000;
}

bool Alarm::isArmed() const
{
    return (_state == AlarmState::Armed);
}

void Alarm::update()
{
    switch (_state)
    {
        case AlarmState::ExitDelay:

            if (_exitTimer.expired())
            {
                _state = AlarmState::Armed;
            }

            break;

        default:
            break;
    }
}

AlarmState Alarm::getState() const
{
    return _state;
}
