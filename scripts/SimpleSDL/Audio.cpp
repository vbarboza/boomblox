#include "Audio.hpp"

Audio::Audio(std::string path)
{
    mPath = path;
    mBGM = NULL;
    mSFX = NULL;
}

Audio::~Audio()
{
    Free();
}

bool Audio::LoadBGM()
{
    Free();

    mBGM = Mix_LoadMUS(mPath.c_str());
    if (mBGM == NULL)
    {
        fprintf(stderr, "%s\n", Mix_GetError());
        return false;
    }
    return true;
}

bool Audio::LoadSFX()
{
    Free();

    mSFX = Mix_LoadWAV(mPath.c_str());
    if (mSFX == NULL)
    {
        fprintf(stderr, "%s\n", Mix_GetError());
        return false;
    }

    return true;
}

void Audio::Free()
{
    if (mBGM != NULL)
    {
        Mix_FreeMusic(mBGM);
    }

    if (mSFX != NULL)
    {
        Mix_FreeChunk(mSFX);
    }

    mBGM = NULL;
    mSFX = NULL;
}

std::string Audio::GetPath()
{
    return mPath;
}

void Audio::SetPath(std::string path)
{
    mPath = path;
}

void Audio::Play()
{
    if (mBGM != NULL)
    {
        if (Mix_PausedMusic())
        {
            Mix_ResumeMusic();
        }
        else
        {
            Mix_PlayMusic(mBGM, -1);
        }
    }

    if (mSFX != NULL)
    {
        Mix_PlayChannelTimed(-1, mSFX, 0, 100);
    }
}

void Pause()
{
    if (Mix_PlayingMusic())
    {
        Mix_PauseMusic();
    }
}
