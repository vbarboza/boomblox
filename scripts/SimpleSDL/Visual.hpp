#ifndef _VISUAL_
#define _VISUAL_

#include <SDL2/SDL.h>

class Visual
{
public:
    Visual(SDL_Renderer *);
    ~Visual();

    virtual void Free();

    SDL_Point GetSize();
    virtual void SetSize(SDL_Point);

    SDL_Point GetPosition();
    virtual void SetPosition(SDL_Point);

    SDL_Color GetColor();
    virtual void SetColor(SDL_Color);

protected:
    SDL_Renderer *mRenderer;
    SDL_Point mSize;
    SDL_Point mPosition;
    SDL_Color mColor;
};
#endif
