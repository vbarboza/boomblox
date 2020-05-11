#include "EventListener.hpp"

EventListener::EventListener()
{
    SDL_AddEventWatch(OnEvent, this);
}

EventListener::~EventListener() {}

int EventListener::OnEvent(void *instance, SDL_Event *event)
{
    return ((EventListener *)instance)->OnEvent(event);
}

int EventListener::OnEvent(SDL_Event *event) {}
