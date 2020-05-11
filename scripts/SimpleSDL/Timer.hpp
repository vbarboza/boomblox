#ifndef _TIMER_
#define _TIMER_

#include <SDL2/SDL.h>

class Timer
{
public:
    Timer();

    void Start();
    void Stop();
    bool IsStarted();

    void Pause();
    void Unpause();
    bool IsPaused();

    Uint32 GetTicks();

private:
    Uint32 mStartTicks;
    Uint32 mPausedTicks;

    bool mStarted;
    bool mPaused;
};
#endif
