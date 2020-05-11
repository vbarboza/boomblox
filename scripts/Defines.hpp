#define SCREEN_WIDTH (360)
#define SCREEN_HEIGHT (400)

#define EVENT_GAME_START (1)
#define EVENT_GAME_PAUSE (2)
#define EVENT_GAME_OVER (3)
#define EVENT_PAD_CLICK (4)
#define EVENT_SCORE_CHANGE (5)
#define EVENT_SCORE_FINAL (6)
#define EVENT_RHYTHM_PERFECT (7)
#define EVENT_RHYTHM_GOOD (8)
#define EVENT_RHYTHM_MISS (9)
#define EVENT_RHYTHM_ON_BEAT (10)

#define LABEL_FONT "assets/font.ttf"

#define PAD_FILE "assets/pad.png"
#define PAD_SIZE (40)
#define PAD_VERTICAL_OFFSET (60)
#define PAD_HORIZONTAL_OFFSET (20)

#define SCORE_MULTIPLIER (10)

#define RHYTHM_BPM (60)
#define RHYTHM_MS_PER_MINUTE (60000)
#define RHYTHM_EARLY_GOOD (0.8)
#define RHYTHM_EARLY_PERFECT (0.9)
#define RHYTHM_LATE_PERFECT (0.1)
#define RHYTHM_LATE_GOOD (0.2)
#define RHYTHM_PULSE (100)

#define BOARD_ROWS (8)
#define BOARD_COLS (8)
#define BOARD_COLORS (3)
#define MIN_BLOB_COUNT (3)
#define BOARD_INITIAL_COLS (3)
#define BOARD_COUNT_TO_SHIFT (4)

#define BOARD_COLOR_0      \
    {                      \
        255, 255, 255, 255 \
    }
#define BOARD_COLOR_1      \
    {                      \
        162, 255, 243, 255 \
    }
#define BOARD_COLOR_2      \
    {                      \
        203, 243, 130, 255 \
    }
#define BOARD_COLOR_3      \
    {                      \
        255, 243, 146, 255 \
    }
#define BOARD_COLOR_4     \
    {                     \
        255, 97, 178, 255 \
    }
#define BOARD_COLOR_5      \
    {                      \
        162, 186, 255, 255 \
    }
#define BOARD_COLOR_RED  \
    {                    \
        196, 32, 32, 255 \
    }
