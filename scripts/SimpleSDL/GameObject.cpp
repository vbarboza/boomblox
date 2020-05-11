#include "GameObject.hpp"

GameObject::GameObject()
{
    mActive = true;
}

bool GameObject::IsActive()
{
    return mActive;
}

void GameObject::SetActive(bool active)
{
    mActive = active;
}

void GameObject::Load()
{
}

void GameObject::Update()
{
}

void GameObject::SendUserEvent(int code, void *data1, void *data2)
{
    SDL_Event event;
    SDL_UserEvent userEvent;

    userEvent.type = SDL_USEREVENT;
    userEvent.code = code;
    userEvent.data1 = data1;
    userEvent.data2 = data2;

    event.type = SDL_USEREVENT;
    event.user = userEvent;

    SDL_PushEvent(&event);
}
