#include "BoardManager.hpp"

BoardManager::BoardManager()
{
    srand(time(NULL));
    PadsSetup();
    BoardSetup();
    mKick = new Audio("assets/kick.wav");
    mStarted = false;
    mPaused = false;
    mGameOver = false;
    mExpandCounter = 0;
    mGameOverCounter = 0;
}

void BoardManager::Reset()
{
    srand(time(NULL));
    BoardSetup();
}

BoardManager::~BoardManager()
{
    free(mKick);
    PadsFree();
}

void BoardManager::Load()
{
    PadsLoad();
    mTimer.Start();
    mKick->LoadSFX();
}

void BoardManager::Update()
{
    if (mStarted && !mPaused)
    {
        PadsUpdate();
    }
}

#pragma region Pads
void BoardManager::PadsSetup()
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            SDL_Point padIndex = {j, i};
            Pad *pad = new Pad(padIndex);
            pad->SetSize({PAD_SIZE, PAD_SIZE});
            pad->SetPosition({
                j * PAD_SIZE + PAD_HORIZONTAL_OFFSET,
                i * PAD_SIZE + PAD_VERTICAL_OFFSET,
            });
            mPads[i][j] = pad;
        }
    }
}

void BoardManager::PadsLoad()
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            mPads[i][j]->Load();
        }
    }
}

void BoardManager::PadsUpdate()
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            int label = mBoard[i][j];
            SDL_Color color = GetPadColor(label);

            mPads[i][j]->SetColor(color);
            mPads[i][j]->Update();
        }
    }
}

void BoardManager::PadsNotify(SDL_Event *event)
{
}

void BoardManager::PadsFree()
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            if (mPads[i][j] != NULL)
            {
                free(mPads[i][j]);
            }
        }
    }
}
#pragma endregion Pads

#pragma region Board
void BoardManager::BoardSetup()
{
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            mBoard[i][j] = 0;
        }
    }

    BoardExpandLeft(BOARD_INITIAL_COLS);
}

bool BoardManager::BoardExpandLeft(int cols)
{
    bool success = true;

    if (cols == 0)
    {
        return success;
    }

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        if (mBoard[i][0] != 0)
        {
            success = false;
            break;
        }
    }

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS - cols; j++)
        {
            mBoard[i][j] = mBoard[i][j + cols];
        }
    }

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = BOARD_COLS - cols; j < BOARD_COLS; j++)
        {
            mBoard[i][j] = rand() % BOARD_COLORS + 1;
        }
    }

    return success;
}

bool BoardManager::BoardCollapseRight(int offset)
{
    bool filledGap = false;

    if (offset >= BOARD_COLS - 1)
    {
        return filledGap;
    }

    for (int j = BOARD_COLS - 1 - offset; j > 0; j--)
    {
        for (int i = 0; i < BOARD_ROWS; i++)
        {
            mBoard[i][j] = mBoard[i][j - 1];

            if (!filledGap && mBoard[i][j])
            {
                filledGap = true;
            }
        }
    }

    for (int i = 0; i < BOARD_ROWS; i++)
    {
        mBoard[i][0] = 0;
    }

    return filledGap;
}

int BoardManager::BoardRemove(int row, int col)
{
    int blobCount = 0;

    TBoard neighborhood = BoardNeighborhood(row, col, &blobCount);

    if (blobCount >= MIN_BLOB_COUNT)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            int currentRow = BOARD_ROWS - 1;
            int swapRow = BOARD_ROWS - 1;

            if (!mBoard[currentRow][j])
            {
                continue;
            }

            for (; currentRow >= 0; currentRow--)
            {
                if (!neighborhood[currentRow][j])
                {
                    continue;
                }

                if (swapRow > currentRow)
                {
                    swapRow = currentRow;
                }

                for (swapRow--; swapRow >= 0; swapRow--)
                {
                    if (!neighborhood[swapRow][j])
                    {
                        int currentLabel = mBoard[currentRow][j];
                        mBoard[currentRow][j] = mBoard[swapRow][j];
                        mBoard[swapRow][j] = currentLabel;
                        neighborhood[swapRow][j] = 1;
                        break;
                    }
                }

                if (swapRow < 0)
                {
                    mBoard[currentRow][j] = 0;
                    swapRow = currentRow;
                }
            }
        }

        for (int j = BOARD_COLS - 1; j >= 0; j--)
        {
            if (mBoard[BOARD_ROWS - 1][j] == 0)
            {
                if (BoardCollapseRight(BOARD_COLS - 1 - j))
                {
                    j++;
                }
            }
        }
    }

    return blobCount;
}

TBoard BoardManager::BoardNeighborhood(int row, int col, int *outCount)
{
    int count = 0;
    int label = mBoard[row][col];

    TBoard neighborhood;
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        for (int j = 0; j < BOARD_COLS; j++)
        {
            neighborhood[i][j] = 0;
        }
    }

    if (label != 0)
    {
        std::list<SDL_Point> toVisit;
        toVisit.push_back({col, row});

        for (auto position : toVisit)
        {
            count++;
            neighborhood[position.y][position.x] = label;

            if (position.x > 0 &&
                mBoard[position.y][position.x - 1] == label &&
                neighborhood[position.y][position.x - 1] != label)
            {
                toVisit.push_back({position.x - 1, position.y});
            }

            if (position.y > 0 &&
                mBoard[position.y - 1][position.x] == label &&
                neighborhood[position.y - 1][position.x] != label)
            {
                toVisit.push_back({position.x, position.y - 1});
            }

            if (position.x < BOARD_COLS - 1 &&
                mBoard[position.y][position.x + 1] == label &&
                neighborhood[position.y][position.x + 1] != label)
            {
                toVisit.push_back({position.x + 1, position.y});
            }

            if (position.y < BOARD_ROWS - 1 &&
                mBoard[position.y + 1][position.x] == label &&
                neighborhood[position.y + 1][position.x] != label)
            {
                toVisit.push_back({position.x, position.y + 1});
            }
        }
    }

    if (outCount != NULL)
    {
        *outCount = count;
    }

    return neighborhood;
}
#pragma endregion Board

int BoardManager::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_SPACE:
            BoardExpandLeft(1);
            break;
        }
    }

    if (event->type == SDL_USEREVENT)
    {
        switch (event->user.code)
        {
        case EVENT_RHYTHM_ON_BEAT:
        {
            mExpandCounter = (mExpandCounter + 1) % BOARD_COUNT_TO_SHIFT;

            if (mExpandCounter == 0)
            {
                mGameOver = !BoardExpandLeft(1);
            }
            mTimer.Start();

            if (mShouldPlay)
            {
                mShouldPlay = false;
                mKick->Play();
            }
        }
        break;
        case EVENT_PAD_CLICK:
            if (mStarted && !mPaused && !mGameOver)
            {
                SDL_Point *index = (SDL_Point *)event->user.data1;
                int count = BoardRemove(index->y, index->x);

                if (count >= MIN_BLOB_COUNT)
                {
                    mShouldPlay = true;
                    SendUserEvent(EVENT_SCORE_CHANGE, &count);
                }
            }
            break;
        case EVENT_GAME_START:
            if (!mStarted || mPaused)
            {
                Reset();
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
            mStarted = false;
            mPaused = false;
            mTimer.Stop();
            break;
        }
    }
}

SDL_Color BoardManager::GetPadColor(int label)
{
    SDL_Color color = mGameOver ? SDL_Color(BOARD_COLOR_RED)
                                : PadColors[label];

    if (label == 0 || mTimer.GetTicks() < RHYTHM_PULSE)
    {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
    }

    if (mGameOver && mTimer.GetTicks() > 3 * RHYTHM_PULSE)
    {
        mTimer.Start();
        mGameOverCounter++;
    }

    if (mGameOverCounter > 3)
    {
        mStarted = false;
        SendUserEvent(EVENT_GAME_OVER);
    }

    return color;
}
