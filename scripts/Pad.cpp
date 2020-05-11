#include <cstdio>

#include "SimpleSDL/Texture.hpp"

#include "Defines.hpp"
#include "Pad.hpp"
#include "System.hpp"

Pad::Pad(SDL_Point index) : Button(
                                System::Instance()->GetRenderer(),
                                PAD_FILE,
                                NULL)
{
    mIndex = index;
    Free();
}

Pad::~Pad()
{
    Free();
}

void Pad::Callback(void *instance)
{
    SDL_Event event;
    SDL_UserEvent userEvent;

    userEvent.type = SDL_USEREVENT;
    userEvent.code = EVENT_PAD_CLICK;
    userEvent.data1 = &mIndex;

    event.type = SDL_USEREVENT;
    event.user = userEvent;

    SDL_PushEvent(&event);
}
