#include <sstream>
#include <iomanip>

#include "Defines.hpp"
#include "ScoreManager.hpp"
#include "System.hpp"

ScoreManager::ScoreManager()
{
    Reset();
}

void ScoreManager::Reset()
{
    SetupComboLabel();
    SetupScoreLabel();
    SetupPauseLabel();

    mStarted = false;
    mPaused = false;
    mGameOver = false;

    mScore = 0;
    mCombo = 0;
    mState = Miss;
}

ScoreManager::~ScoreManager()
{
    free(mComboLabel);
    free(mScoreLabel);
    free(mPauseLabel);
}

void ScoreManager::Load()
{
    mComboLabel->Load();
    mScoreLabel->Load();
    mPauseLabel->Load();
}

void ScoreManager::Update()
{
    if (mStarted && !mPaused)
    {
        mScoreLabel->Render();
        mComboLabel->Render();
        mPauseLabel->Render();
    }
}

int ScoreManager::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_USEREVENT)
    {
        switch (event->user.code)
        {
        case EVENT_SCORE_CHANGE:
        {
            int count = *(int *)event->user.data1;

            int multiplier = 1;

            switch (mState)
            {
            case Perfect:
                mComboLabel->SetText("PERFECT");
                mCombo += 1;
                break;
            case Good:
                mComboLabel->SetText("GOOD");
                mCombo += 1;
                break;
            case Miss:
                mComboLabel->SetText("-------");
                mCombo = 0;
                break;
            }

            multiplier += mCombo;
            mScore += count * SCORE_MULTIPLIER * multiplier;

            std::stringstream scoreText;
            scoreText << std::setfill('0') << std::setw(7) << mScore;
            mScoreLabel->SetText(scoreText.str());
        }
        break;
        case EVENT_RHYTHM_ON_BEAT:
            if (mState == Miss)
            {
                mComboLabel->SetText("-------");
            }
            break;
        case EVENT_RHYTHM_MISS:
            mState = Miss;
            break;
        case EVENT_RHYTHM_GOOD:
            mState = Good;
            break;
        case EVENT_RHYTHM_PERFECT:
            mState = Perfect;
            break;
        case EVENT_GAME_START:
            if (!mStarted || mPaused)
            {
                mComboLabel->SetText("-------");
                mScoreLabel->SetText("0000000");
                mStarted = true;
                mPaused = false;
            }
            break;
        case EVENT_GAME_PAUSE:
            if (mStarted)
            {
                mPaused = !mPaused;
            }
            break;
        case EVENT_GAME_OVER:
            SendUserEvent(EVENT_SCORE_FINAL, &mScore);
            mStarted = false;
            mPaused = false;
            break;
        }
    }
}

void ScoreManager::SetupComboLabel()
{
    mComboLabel = new Text(System::Instance()->GetRenderer(),
                           LABEL_FONT,
                           16,
                           "-------");

    mComboLabel->SetPosition({SCREEN_WIDTH / 6, 32});
    mComboLabel->SetColor({0xFF, 0xFF, 0xFF});
}

void ScoreManager::SetupScoreLabel()
{
    mScoreLabel = new Text(System::Instance()->GetRenderer(),
                           LABEL_FONT,
                           16,
                           "0000000");

    mScoreLabel->SetPosition({SCREEN_WIDTH / 2, 32});
    mScoreLabel->SetColor({0xFF, 0xFF, 0xFF});
}

void ScoreManager::SetupPauseLabel()
{
    mPauseLabel = new Text(System::Instance()->GetRenderer(),
                           LABEL_FONT,
                           14,
                           "[P]ause");

    mPauseLabel->SetPosition({SCREEN_WIDTH * 5 / 6, 32});
    mPauseLabel->SetColor({0xFF, 0xFF, 0xFF});
}
