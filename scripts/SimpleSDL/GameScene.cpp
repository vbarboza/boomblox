#include "GameScene.hpp"

GameScene::GameScene(SDL_Renderer *renderer)
{
    mRenderer = renderer;
    isRunning = false;
}

GameScene::~GameScene()
{
    mRenderer = NULL;
    isRunning = false;
}

void GameScene::Load()
{
    for (auto gameObject : mGameObjects)
    {
        if (gameObject->IsActive())
        {
            gameObject->Load();
        }
    }
}

void GameScene::Update()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
        Stop();
        return;
    }

    SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(mRenderer);

    for (auto &gameObject : mGameObjects)
    {
        if (gameObject->IsActive())
        {
            gameObject->Update();
        }
    }

    SDL_RenderPresent(mRenderer);
}

bool GameScene::IsRunning()
{
    return isRunning;
}

void GameScene::Start()
{
    isRunning = true;
    Loop();
}

void GameScene::Stop()
{
    isRunning = false;
}

int GameScene::Loop()
{
    while (isRunning)
    {
        Update();
    }
}

void GameScene::AddGameObject(GameObject *gameObject)
{
    mGameObjects.push_back(gameObject);
}
