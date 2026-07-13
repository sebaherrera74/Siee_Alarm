#ifndef ALARM_H
#define ALARM_H

enum AlarmState
{
    DISARMED,
    EXIT_DELAY,
    ARMED,
    ALARM_TRIGGERED
};

class Alarm
{
public:

    bool begin();

    void update();

    void arm();

    void disarm();

    void trigger();

    AlarmState getState();

private:

    AlarmState _state;
};

#endif
