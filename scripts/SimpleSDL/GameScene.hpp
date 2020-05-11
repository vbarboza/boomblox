#ifndef _GAMESCENE_
#define _GAMESCENE_

#include <list>

#include <SDL2/SDL.h>

#include "GameObject.hpp"

class GameScene
{
public:
    GameScene(SDL_Renderer *);
    ~GameScene();

    void Load();
    void Update();

    bool IsRunning();
    void Start();
    void Stop();
    int Loop();

protected:
    void AddGameObject(GameObject *);

private:
    SDL_Renderer *mRenderer;
    std::list<GameObject *> mGameObjects;
    bool isRunning;
};
#endif
