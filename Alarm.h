#ifndef ALARM_H
#define ALARM_H

enum class AlarmState
{
    Disarmed,
    Armed
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

private:

    AlarmState _state;
};

#endif
