#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include <SDL2/SDL.h>

class GameObject
{
public:
    GameObject();

    virtual void Load();
    virtual void Update();

    bool IsActive();
    void SetActive(bool);

protected:
    void SendUserEvent(int code,
                       void *data1 = NULL,
                       void *data2 = NULL);

private:
    bool mActive;
};

#endif
