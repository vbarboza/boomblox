#ifndef _AUDIO_
#define _AUDIO_

#include <string>

#include <SDL2/SDL_mixer.h>

class Audio
{
public:
    Audio(std::string);
    ~Audio();

    bool LoadBGM();
    bool LoadSFX();
    void Free();

    std::string GetPath();
    void SetPath(std::string);

    void Play();
    void Pause();

private:
    Mix_Music *mBGM;
    Mix_Chunk *mSFX;
    std::string mPath;
};
#endif
