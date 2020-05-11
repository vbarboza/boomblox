OBJS = scripts/SimpleSDL/Visual.cpp \
	scripts/SimpleSDL/Texture.cpp \
	scripts/SimpleSDL/Text.cpp \
	scripts/SimpleSDL/Audio.cpp \
	scripts/SimpleSDL/Timer.cpp \
	scripts/SimpleSDL/EventListener.cpp \
	scripts/SimpleSDL/GameObject.cpp \
	scripts/SimpleSDL/GameScene.cpp \
	scripts/SimpleSDL/Button.cpp \
	scripts/Pad.cpp \
	scripts/RhythmManager.cpp \
	scripts/BoardManager.cpp \
	scripts/MenuManager.cpp \
	scripts/ScoreManager.cpp \
	scripts/System.cpp \
	scripts/Game.cpp \
	scripts/main.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = boomblox

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
