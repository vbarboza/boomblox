#ifndef _TEXTURE_
#define _TEXTURE_

#include <string>

#include <SDL2/SDL.h>

#include "Visual.hpp"

class Texture : public Visual
{
public:
    Texture(SDL_Renderer *renderer, const std::string path);
    ~Texture();

    bool Load();
    void Free() override;

    std::string GetPath();
    void SetPath(std::string);

    void Render(SDL_Rect *clip = NULL);

private:
    SDL_Texture *mTexture;
    std::string mPath;
};

#endif
