#ifndef _PAD_
#define _PAD_

#include <SDL2/SDL.h>

#include "SimpleSDL/Button.hpp"
#include "SimpleSDL/Texture.hpp"

class Pad : public Button
{
public:
    Pad(SDL_Point mIndex);
    ~Pad();

    void Callback(void *) override;

private:
    SDL_Point mIndex;
};

#endif
