#ifndef ALARM_H
#define ALARM_H

#include "Timmer.h"
enum class AlarmState
{
    Disarmed,
    ExitDelay,
    Armed,
    EntryDelay,
    Triggered
};
class Alarm
{
public:

    void begin();

    void arm();

    void disarm();

    void toggle();

    AlarmState getState() const;

    bool isArmed() const;
    void update();
    uint8_t exitDelayRemaining() const;
    uint8_t entryDelayRemaining() const;

    void triggerEntryDelay();
    bool stateChanged();


private:

    AlarmState _state;
    AlarmState _previousState;
    Timer _exitTimer;
    Timer _entryTimer;
    
};

#endif
