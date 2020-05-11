#include "SimpleSDL/EventListener.hpp"
#include "SimpleSDL/GameObject.hpp"
#include "SimpleSDL/Text.hpp"

class ScoreManager : public GameObject, public EventListener
{
public:
    ScoreManager();
    ~ScoreManager();

    void Reset();

    void Load() override;
    void Update() override;

private:
    typedef enum
    {
        Miss,
        Good,
        Perfect
    } ScoreComboState;

    Text *mComboLabel;
    Text *mScoreLabel;
    Text *mPauseLabel;

    bool mStarted;
    bool mPaused;
    bool mGameOver;

    int mScore;
    int mCombo;
    ScoreComboState mState;

    void SetupComboLabel();
    void SetupScoreLabel();
    void SetupPauseLabel();

    int OnEvent(SDL_Event *) override;
};
