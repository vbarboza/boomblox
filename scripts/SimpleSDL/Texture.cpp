#include <cstdio>

#include <SDL2/SDL_image.h>

#include "Texture.hpp"

Texture::Texture(SDL_Renderer *renderer, const std::string path) : Visual(renderer)
{
    mTexture = NULL;
    mPath = path;
}

Texture::~Texture()
{
    Visual::Free();
    Free();
}

bool Texture::Load()
{
    Free();

    SDL_Surface *surface = IMG_Load(mPath.c_str());
    if (surface == NULL)
    {
        printf("Failed to load image %s:\n\t%s\n",
               mPath.c_str(), IMG_GetError());
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (texture == NULL)
    {
        printf("Failed to create texture %s:\n\t%s",
               mPath.c_str(), SDL_GetError());
        return false;
    }

    if (mSize.x == 0 && mSize.y == 0)
    {
        mSize = {surface->w, surface->h};
    }
    SDL_FreeSurface(surface);

    mTexture = texture;

    return true;
}

void Texture::Free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
    }

    mTexture = NULL;
}

std::string Texture::GetPath()
{
    return mPath;
}

void Texture::SetPath(std::string path)
{
    mPath = path;
}

void Texture::Render(SDL_Rect *clip)
{
    SDL_Rect rect = {mPosition.x, mPosition.y, mSize.x, mSize.y};

    if (clip != NULL)
    {
        rect.w = clip->w;
        rect.h = clip->h;
    }

    SDL_SetTextureColorMod(mTexture, mColor.r, mColor.g, mColor.b);
    SDL_RenderCopy(mRenderer, mTexture, clip, &rect);
}
