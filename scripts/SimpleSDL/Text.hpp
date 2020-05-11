#ifndef _TEXT_
#define _TEXT_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Visual.hpp"

class Text : public Visual
{
public:
    Text(SDL_Renderer *,
         std::string,
         int,
         std::string);
    ~Text();

    bool Load();
    void Free();

    std::string GetPath();
    void SetPath(std::string);
    int GetFontSize();
    void SetFontSize(int);
    std::string GetText();
    void SetText(std::string);

    void Render();

private:
    TTF_Font *mFont;
    SDL_Texture *mTexture;
    std::string mFontPath;
    int mFontSize;
    std::string mText;

    bool DrawTexture();
};

#endif
