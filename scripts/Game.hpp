#ifndef _GAME_
#define _GAME_

#include "SimpleSDL/GameScene.hpp"

#include "BoardManager.hpp"
#include "MenuManager.hpp"
#include "ScoreManager.hpp"
#include "RhythmManager.hpp"

class Game : public GameScene
{
public:
    Game(SDL_Renderer *renderer);
    ~Game();

private:
    BoardManager *mBoardManager;
    ScoreManager *mScoreManager;
    MenuManager *mMenuManager;
    RhythmManager *mRhythmManager;
};

#endif
