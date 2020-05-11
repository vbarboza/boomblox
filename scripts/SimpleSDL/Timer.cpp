#include "Timer.hpp"

Timer::Timer()
{
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void Timer::Start()
{
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void Timer::Stop()
{
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPausedTicks = 0;
}

bool Timer::IsStarted()
{
    return mStarted;
}

void Timer::Pause()
{
    if (mStarted && !mPaused)
    {
        mPaused = true;
        mStartTicks = 0;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
    }
}

void Timer::Unpause()
{
    if (mStarted && mPaused)
    {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

bool Timer::IsPaused()
{
    return mPaused;
}

Uint32 Timer::GetTicks()
{
    Uint32 time = 0;

    if (mStarted)
    {
        if (mPaused)
        {
            time = mPausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}
