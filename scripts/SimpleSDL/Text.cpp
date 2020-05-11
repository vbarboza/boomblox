#include <cstdio>

#include "Text.hpp"

Text::Text(SDL_Renderer *renderer,
           std::string fontPath,
           int fontSize,
           std::string text) : Visual(renderer)
{
    mFontPath = fontPath;
    mFontSize = fontSize;
    mText = text;

    mTexture = NULL;
}

Text::~Text()
{
    Visual::Free();
    Free();
}

bool Text::Load()
{
    Free();

    mFont = TTF_OpenFont(mFontPath.c_str(), mFontSize);
    if (mFont == NULL)
    {
        printf("%s\n", TTF_GetError());
        return false;
    }

    return DrawTexture();
}

bool Text::DrawTexture()
{
    SDL_Surface *surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
    if (surface == NULL)
    {
        printf("%s\n", TTF_GetError());
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (texture == NULL)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }

    mSize = {surface->w, surface->h};
    SDL_FreeSurface(surface);

    mTexture = texture;

    return true;
}

void Text::Free()
{
    if (mTexture != NULL)
    {
        TTF_CloseFont(mFont);
        SDL_DestroyTexture(mTexture);
    }

    mFont = NULL;
    mTexture = NULL;
}

void Text::Render()
{
    SDL_Rect rect = {mPosition.x - mSize.x / 2,
                     mPosition.y - mSize.y / 2,
                     mSize.x,
                     mSize.y};
    SDL_SetTextureColorMod(mTexture, mColor.r, mColor.g, mColor.b);
    SDL_RenderCopy(mRenderer, mTexture, NULL, &rect);
}

std::string Text::GetPath()
{
    return mFontPath;
}

void Text::SetPath(std::string fontPath)
{
    mFontPath = fontPath;
}

int Text::GetFontSize()
{
    return mFontSize;
}

void Text::SetFontSize(int fontSize)
{
    mFontSize = fontSize;
}

std::string Text::GetText()
{
    return mText;
}

void Text::SetText(std::string text)
{
    mText = text;
    DrawTexture();
}
