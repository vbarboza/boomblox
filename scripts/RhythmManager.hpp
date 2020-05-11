#include <array>
#include <list>

#include "SimpleSDL/Audio.hpp"
#include "SimpleSDL/EventListener.hpp"
#include "SimpleSDL/GameObject.hpp"
#include "SimpleSDL/Timer.hpp"

#include "Defines.hpp"

class RhythmManager : public GameObject, public EventListener
{
public:
    RhythmManager();
    ~RhythmManager();

    void Load() override;
    void Update() override;

    int OnEvent(SDL_Event *event) override;

private:
    typedef enum
    {
        None,
        EarlyGood,
        EarlyPerfect,
        Perfect,
        LatePerfect,
        LateGood
    } RhythmBeatState;

    Timer mTimer;
    Timer mHihatTimer;
    Audio *mHihat;

    bool mStarted;
    bool mPaused;
    RhythmBeatState mState;
    int mBars;
    int mTicks;
    int mTicksPerBeat;

    void HandleEarlyGoodBeat(int);
    void HandleEarlyPerfectBeat(int);
    void HandleLatePerfectBeat(int);
    void HandleLateGoodBeat(int);
    void HandleBeat(int);
};
