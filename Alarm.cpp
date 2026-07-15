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
        case AlarmState::EntryDelay:
        
          if (_entryTimer.expired())
         {
            _state = AlarmState::Triggered;
         }

    break;
    }
}

AlarmState Alarm::getState() const
{
    return _state;
}

void Alarm::triggerEntryDelay()
{
    if (_state != AlarmState::Armed)
        return;

    _state = AlarmState::EntryDelay;

    _entryTimer.start(ENTRY_DELAY_SEC * 1000);
}

uint8_t Alarm::entryDelayRemaining() const
{
    return _entryTimer.remaining() / 1000;
}
