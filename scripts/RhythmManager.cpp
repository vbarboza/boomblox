#include "RhythmManager.hpp"

RhythmManager::RhythmManager()
{
    mTicksPerBeat = RHYTHM_MS_PER_MINUTE / RHYTHM_BPM;

    mHihat = new Audio("assets/hihat.wav");

    mState = None;
    mStarted = false;
    mPaused = false;
}

RhythmManager::~RhythmManager()
{
    free(mHihat);
}

void RhythmManager::Load()
{
    mHihat->LoadSFX();
}

void RhythmManager::Update()
{
    if (!mStarted || mPaused)
    {
        return;
    }

    int ticks = mTimer.GetTicks();

    switch (mState)
    {
    case None:
        HandleEarlyGoodBeat(ticks);
        break;
    case EarlyGood:
        HandleEarlyPerfectBeat(ticks);
        break;
    case EarlyPerfect:
        HandleLatePerfectBeat(ticks);
        break;
    case LatePerfect:
        HandleLateGoodBeat(ticks);
        break;
    case LateGood:
        mState = None;
        break;
    }

    HandleBeat(ticks);
}

void RhythmManager::HandleEarlyGoodBeat(int ticks)
{
    if (ticks >= RHYTHM_EARLY_GOOD * mTicksPerBeat)
    {
        SendUserEvent(EVENT_RHYTHM_GOOD);
        mState = EarlyGood;
    }
}

void RhythmManager::HandleEarlyPerfectBeat(int ticks)
{
    if (ticks >= RHYTHM_EARLY_PERFECT * mTicksPerBeat)
    {
        SendUserEvent(EVENT_RHYTHM_PERFECT);
        mState = EarlyPerfect;
    }
}

void RhythmManager::HandleLatePerfectBeat(int ticks)
{
    if (ticks <= RHYTHM_LATE_PERFECT * mTicksPerBeat)
    {
        SendUserEvent(EVENT_RHYTHM_GOOD);
        mState = LatePerfect;
    }
}

void RhythmManager::HandleLateGoodBeat(int ticks)
{
    if (ticks <= RHYTHM_LATE_GOOD * mTicksPerBeat)
    {
        SendUserEvent(EVENT_RHYTHM_MISS);
        mState = LateGood;
    }
}

void RhythmManager::HandleBeat(int ticks)
{
    if (mHihatTimer.GetTicks() >= mTicksPerBeat / 2)
    {
        mHihat->Play();
        mHihatTimer.Start();
    }
    if (ticks >= mTicksPerBeat)
    {
        mTimer.Start();
        SendUserEvent(EVENT_RHYTHM_ON_BEAT);
    }
}

int RhythmManager::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_USEREVENT)
    {
        switch (event->user.code)
        {
        case EVENT_GAME_START:
            if (!mStarted || mPaused)
            {
                mStarted = true;
                mPaused = false;
                mTimer.Start();
                mHihatTimer.Start();
            }
            break;
        case EVENT_GAME_PAUSE:
            if (mStarted)
            {
                if (mPaused)
                {
                    mTimer.Unpause();
                }
                else
                {
                    mTimer.Pause();
                }
                mPaused = !mPaused;
            }
            break;
        case EVENT_GAME_OVER:
            mStarted = false;
            mPaused = false;
            mTimer.Stop();
            break;
        }
    }
}
