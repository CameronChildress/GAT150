#include "pch.h"
#include "Timer.h"

namespace nc
{
    void Timer::Reset()
    {
        m_timePoint = clock::now();
    }

   Timer::clock::rep Timer::ElapsedTicks()
    {
       clock_duration duration = (clock::now() - m_timePoint);

        return duration.count();
    }

    Timer::clock::rep Timer::TicksPerSecond()
    {
        return clock_duration::period::den;
    }

    double Timer::ElapsedSeconds()
    {
        return ElapsedTicks() / static_cast<double>(TicksPerSecond());
    }

    void FrameTimer::Tick()
    {
        m_dt = static_cast<float>(ElapsedSeconds());
        m_timePoint = clock::now();
    }
}