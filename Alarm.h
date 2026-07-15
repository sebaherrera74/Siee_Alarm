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



private:

    AlarmState _state;
  
    Timer _exitTimer;
};

#endif
