#include <sstream>
#include <iomanip>

#include "MenuManager.hpp"
#include "System.hpp"

MenuManager::MenuManager()
{
    SetupTitleLabel();
    SetupNewGameLabel();
    SetupPauseLabel();
    SetupGameOverLabel();
    SetupScoreLabel();
}

MenuManager::~MenuManager()
{
    free(mTitleLabel);
    free(mNewGameLabel);
    free(mPauseLabel);
    free(mGameOverLabel);
    free(mScoreLabel);
    free(mScoreValueLabel);
}

void MenuManager::Load()
{
    mTitleLabel->Load();
    mNewGameLabel->Load();
    mPauseLabel->Load();
    mGameOverLabel->Load();
    mScoreLabel->Load();
    mScoreValueLabel->Load();
}

void MenuManager::Update()
{
    if (!mStarted)
    {
        mTitleLabel->Render();
        mNewGameLabel->Render();
    }
    else if (mStarted && mPaused)
    {
        mTitleLabel->Render();
        mNewGameLabel->Render();
        mPauseLabel->Render();
    }
    if (mGameOver)
    {
        mGameOverLabel->Render();
    }
    if (mHasScore)
    {
        mScoreLabel->Render();
        mScoreValueLabel->Render();
    }
}

int MenuManager::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_p:
            if (mStarted)
            {
                mPaused = !mPaused;
                SendUserEvent(EVENT_GAME_PAUSE);
            }
            break;
        case SDLK_n:
            if (!mStarted || mPaused)
            {
                mStarted = true;
                mPaused = false;
                mHasScore = false;
                mGameOver = false;
                SendUserEvent(EVENT_GAME_START);
            }
            break;
        }
    }
    if (event->type == SDL_USEREVENT)
    {
        switch (event->user.code)
        {
        case EVENT_GAME_OVER:
            mStarted = false;
            mPaused = false;
            mGameOver = true;
            break;
        case EVENT_SCORE_FINAL:
            int score = *(int *)event->user.data1;
            std::stringstream scoreText;
            scoreText << std::setfill('0') << std::setw(7) << score;
            mScoreValueLabel->SetText(scoreText.str());
            mHasScore = true;
            break;
        }
    }
}

void MenuManager::SetupTitleLabel()
{
    mTitleLabel = new Text(System::Instance()->GetRenderer(),
                           LABEL_FONT,
                           32,
                           "BoomBlox");

    mTitleLabel->SetPosition({SCREEN_WIDTH / 2, 64});
    mTitleLabel->SetColor({0xFF, 0xFF, 0xFF});
}

void MenuManager::SetupNewGameLabel()
{
    mNewGameLabel = new Text(System::Instance()->GetRenderer(),
                             LABEL_FONT,
                             16,
                             "press [N] to start a new game");

    mNewGameLabel->SetPosition({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 32});
    mNewGameLabel->SetColor({0xFF, 0xFF, 0xFF});
}

void MenuManager::SetupPauseLabel()
{
    mPauseLabel = new Text(System::Instance()->GetRenderer(),
                           LABEL_FONT,
                           16,
                           "press [P] to unpause");

    mPauseLabel->SetPosition({SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT - 64});
    mPauseLabel->SetColor({0xFF, 0xFF, 0xFF});
}

void MenuManager::SetupGameOverLabel()
{
    mGameOverLabel = new Text(System::Instance()->GetRenderer(),
                              LABEL_FONT,
                              24,
                              "Game Over");

    mGameOverLabel->SetPosition({SCREEN_WIDTH / 2,
                                 128});
    mGameOverLabel->SetColor({0xFF, 0xFF, 0xFF});
}

void MenuManager::SetupScoreLabel()
{
    mScoreLabel = new Text(System::Instance()->GetRenderer(),
                           LABEL_FONT,
                           16,
                           "your score was:");

    mScoreLabel->SetPosition({SCREEN_WIDTH / 2,
                              SCREEN_HEIGHT / 2});
    mScoreLabel->SetColor({0xFF, 0xFF, 0xFF});

    mScoreValueLabel = new Text(System::Instance()->GetRenderer(),
                                LABEL_FONT,
                                24,
                                "-------");

    mScoreValueLabel->SetPosition({SCREEN_WIDTH / 2,
                                   SCREEN_HEIGHT / 2 + 32});
    mScoreValueLabel->SetColor({0xFF, 0xFF, 0xFF});
}
