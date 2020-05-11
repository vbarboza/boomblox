#include "Defines.hpp"
#include "Game.hpp"

Game::Game(SDL_Renderer *renderer) : GameScene(renderer)
{
    mMenuManager = new MenuManager();
    mBoardManager = new BoardManager();
    mScoreManager = new ScoreManager();
    mRhythmManager = new RhythmManager();
    AddGameObject(mMenuManager);
    AddGameObject(mBoardManager);
    AddGameObject(mScoreManager);
    AddGameObject(mRhythmManager);
}

Game::~Game()
{
    free(mMenuManager);
    free(mBoardManager);
    free(mScoreManager);
    free(mRhythmManager);
}
