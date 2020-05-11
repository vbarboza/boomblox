#ifndef _BUTTON_
#define _BUTTON_

#include <string>

#include "EventListener.hpp"
#include "GameObject.hpp"
#include "Texture.hpp"
#include "Visual.hpp"

class Button : public Visual, GameObject, EventListener
{
public:
    Button(SDL_Renderer *,
           std::string,
           void *data);
    ~Button();

    void Load();
    void Update();

    void SetSize(SDL_Point) override;
    void SetPosition(SDL_Point) override;
    void SetColor(SDL_Color) override;

protected:
    int OnEvent(SDL_Event *);
    virtual void Callback(void *data);

private:
    Texture *mTexture;
    void *mData;

    bool CheckCollision(SDL_Point);
};

#endif
