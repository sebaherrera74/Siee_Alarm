#include "Timmer.h"

Timer::Timer()
{
    _startTime = 0;
    _interval = 0;
    _running = false;
}

void Timer::start(uint32_t interval)
{
    _startTime = millis();
    _interval = interval;
    _running = true;
}

void Timer::stop()
{
    _running = false;
}

bool Timer::running() const
{
    return _running;
}

bool Timer::expired()
{
    if (!_running)
        return false;

    if (millis() - _startTime >= _interval)
    {
        _running = false;
        return true;
    }

    return false;
}

uint32_t Timer::remaining() const
{
    if (!_running)
        return 0;

    uint32_t elapsed = millis() - _startTime;

    if (elapsed >= _interval)
        return 0;

    return _interval - elapsed;
}
