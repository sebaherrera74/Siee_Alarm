#ifndef TIMMER_H
#define TIMMER_H

#include <Arduino.h>

class Timer
{
public:

    Timer();

    void start(uint32_t interval);

    void stop();

    bool running() const;

    bool expired();

    uint32_t remaining() const;

private:

    uint32_t _startTime;
    uint32_t _interval;
    bool _running;
};

#endif
