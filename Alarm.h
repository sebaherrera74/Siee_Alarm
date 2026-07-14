#ifndef ALARM_H
#define ALARM_H

class Alarm
{
public:

    void begin();

    void arm();

    void disarm();

    bool isArmed() const;

private:

    bool _armed;
};

#endif
