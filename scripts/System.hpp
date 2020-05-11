#ifndef _SYSTEM_
#define _SYSTEM_

#include <SDL2/SDL.h>

class System
{
public:
    static System *Instance();

    void Init();

    SDL_Renderer *GetRenderer();

private:
    System();
    ~System();

    void InitSDL();
    void SetupScaling();
    void CreateWindow();
    bool CreateRenderer();
    void InitIMG();
    void InitTTF();
    void InitMix();

    static System *cInstance;

    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
};

#endif
