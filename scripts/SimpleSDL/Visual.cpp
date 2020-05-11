#include <cstdio>
#include "Visual.hpp"

Visual::Visual(SDL_Renderer *renderer)
{
    mRenderer = renderer;
    Free();
}

Visual::~Visual()
{
    Free();
}

void Visual::Free()
{
    mSize = {0, 0};
    mPosition = {0, 0};
    mColor = {0x00, 0x00, 0x00};
}

SDL_Point Visual::GetSize()
{
    return mSize;
}

void Visual::SetSize(SDL_Point size)
{
    mSize = size;
}

SDL_Point Visual::GetPosition()
{
    return mPosition;
}

void Visual::SetPosition(SDL_Point position)
{
    mPosition = position;
}

SDL_Color Visual::GetColor()
{
    return mColor;
}

void Visual::SetColor(SDL_Color color)
{
    mColor = color;
}
