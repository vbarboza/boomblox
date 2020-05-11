#ifndef _EVENTLISTENER_
#define _EVENTLISTENER_

#include <SDL2/SDL.h>

class EventListener
{
public:
    EventListener();
    ~EventListener();

protected:
    virtual int OnEvent(SDL_Event *);

private:
    EventListener *listener;

    static int OnEvent(void *,
                       SDL_Event *);
};
#endif
