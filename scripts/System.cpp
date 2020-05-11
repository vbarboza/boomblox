#include <cstdio>
#include <exception>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "Defines.hpp"
#include "System.hpp"

System *System::cInstance;

System::System()
{
}

System::~System()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);

    mRenderer = NULL;
    mWindow = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

System *System::Instance()
{
    if (System::cInstance == NULL)
    {
        System::cInstance = new System();
    }
    return System::cInstance;
}

void System::InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        throw SDL_GetError();
    }
}

void System::SetupScaling()
{
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        fprintf(stderr, "Warning: Linear texture filtering not enabled!");
    }
}

void System::CreateWindow()
{
    mWindow = SDL_CreateWindow("BoomBlox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
        throw SDL_GetError();
    }
}

bool System::CreateRenderer()
{
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (mRenderer == NULL)
    {
        throw SDL_GetError();
    }
    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
}

void System::InitIMG()
{
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(IMG_INIT_PNG) & imgFlags))
    {
        throw IMG_GetError();
    }
}

void System::InitTTF()
{
    if (TTF_Init() == -1)
    {
        throw TTF_GetError();
    }
}

void System::InitMix()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        throw Mix_GetError();
    }
}

void System::Init()
{
    try
    {
        InitSDL();
        //SetupScaling();
        CreateWindow();
        CreateRenderer();
        InitIMG();
        InitTTF();
        InitMix();
    }
    catch (const std::exception &err)
    {
        throw err;
    }
}

SDL_Renderer *System::GetRenderer()
{
    return mRenderer;
}
