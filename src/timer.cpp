#include "timer.hpp"

Timer::Timer()
{
    mStartedTicks = 0;

    mStarted = false;
}

void Timer::start()
{
    mStarted = true;

    mStartedTicks = SDL_GetTicks();
}

void Timer::stop()
{
    mStarted = false;

    mStartedTicks = 0;
}

Uint32 Timer::getTicks()
{
    if (mStarted) return SDL_GetTicks() - mStartedTicks;

    return 0; 
}

bool Timer::isStarted()
{
    return mStarted;
}
