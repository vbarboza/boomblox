#include "SimpleSDL/EventListener.hpp"
#include "SimpleSDL/GameObject.hpp"
#include "SimpleSDL/Text.hpp"

#include "Defines.hpp"

class MenuManager : public GameObject, EventListener
{
public:
    MenuManager();
    ~MenuManager();

    void Load() override;
    void Update() override;

private:
    Text *mTitleLabel;
    Text *mNewGameLabel;
    Text *mPauseLabel;
    Text *mGameOverLabel;
    Text *mScoreLabel;
    Text *mScoreValueLabel;

    bool mStarted;
    bool mPaused;
    bool mGameOver;
    bool mHasScore;

    void SetupTitleLabel();
    void SetupNewGameLabel();
    void SetupPauseLabel();
    void SetupGameOverLabel();
    void SetupScoreLabel();

    int OnEvent(SDL_Event *event) override;
};
