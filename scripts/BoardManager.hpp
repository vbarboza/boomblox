#include <array>
#include <list>

#include "SimpleSDL/Audio.hpp"
#include "SimpleSDL/EventListener.hpp"
#include "SimpleSDL/GameObject.hpp"
#include "SimpleSDL/Timer.hpp"

#include "Defines.hpp"
#include "Pad.hpp"

typedef std::array<std::array<int, BOARD_COLS>, BOARD_ROWS> TBoard;

class BoardManager : public GameObject, public EventListener
{
public:
    BoardManager();
    ~BoardManager();

    void Reset();

    void Load() override;
    void Update() override;

private:
    const SDL_Color PadColors[BOARD_COLORS + 1] = {
        BOARD_COLOR_0,
        BOARD_COLOR_1,
        BOARD_COLOR_2,
        BOARD_COLOR_3};

    TBoard mBoard;
    Audio *mKick;
    Pad *mPads[BOARD_ROWS][BOARD_COLS];
    Timer mTimer;

    bool mStarted;
    bool mPaused;
    bool mGameOver;
    bool mShouldPlay;
    int mExpandCounter;
    int mGameOverCounter;

    void PadsSetup();
    void PadsLoad();
    void PadsUpdate();
    void PadsNotify(SDL_Event *);
    void PadsFree();

    SDL_Color GetPadColor(int label);

    void BoardSetup();
    int BoardRemove(int, int);
    TBoard BoardNeighborhood(int, int, int *);
    bool BoardExpandLeft(int);
    bool BoardCollapseRight(int);

    int OnEvent(SDL_Event *) override;
    void TriggerEventChangeScore(int);
};
