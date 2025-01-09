#pragma once

#include <SDL2/SDL.h>

class Timer
{
public:
    Timer();

    void start();
    void stop();

    Uint32 getTicks();

    bool isStarted();

private:
    Uint32 mStartedTicks;

    bool mStarted;
};