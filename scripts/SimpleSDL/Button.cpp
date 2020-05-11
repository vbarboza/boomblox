#include "Button.hpp"

Button::Button(SDL_Renderer *renderer,
               std::string texturePath,
               void *data) : Visual(renderer)
{
    mTexture = new Texture(renderer, texturePath);
    mData = data;
}

Button::~Button()
{
    if (mTexture != NULL)
    {
        printf("Button::Destroy()\n");
        mTexture->Free();
    }

    free(mTexture);

    Visual::Free();
    mTexture = NULL;
}

void Button::Load()
{
    mTexture->Load();
}

void Button::Update()
{
    mTexture->Render();
}

void Button::SetSize(SDL_Point size)
{
    mTexture->SetSize(size);
    mSize = size;
}

void Button::SetPosition(SDL_Point position)
{
    mTexture->SetPosition(position);
    mPosition = position;
}

void Button::SetColor(SDL_Color color)
{
    mTexture->SetColor(color);
    mColor = color;
}

int Button::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_MOUSEBUTTONUP)
    {
        SDL_Point click;
        SDL_GetMouseState(&click.x, &click.y);
        if (CheckCollision(click))
        {
            Callback(mData);
        }
    }
}

void Button::Callback(void *data) {}

bool Button::CheckCollision(SDL_Point position)
{
    int left = mPosition.x;
    int right = mPosition.x + mSize.x;
    int top = mPosition.y;
    int bottom = mPosition.y + mSize.y;

    return (position.x >= left && position.x <= right &&
            position.y >= top && position.y <= bottom);
}
