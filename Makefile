# SDL_PATH = C:/SDL2
# FLAGS = -std=c++17 -Wall -Wextra
# INC = -I $(SDL_PATH)/include/SDL2 -I inc# -I engine/inc -I game/inc
# LIB = -L $(SDL_PATH)/lib
# LIBS = -lmingw32 -lSDL2main -lSDL2
# # SRC = game/src/*.cpp engine/src/*.cpp
# SRC = src/*.cpp
# CXX = g++
# EXE = bin/main.exe

# $(EXE): $(SRC)
# 	$(CXX) $(FLAGS) $(INC) $(LIB) $^ -o $@ $(LIBS)

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := ./bin
SDL_DIR := C:/SDL2

EXE := $(BIN_DIR)/main.exe
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXX      := g++
CPPFLAGS := -I $(SDL_DIR)/include/SDL2 -I inc -MMD -MP
CXXFLAGS := -Wall -Wextra -std=c++17 -ggdb
LDFLAGS  := -Llib -L $(SDL_DIR)/lib
LDLIBS   := -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

.PHONY: all clean run

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

run:
	$(EXE)

-include $(OBJ:.o=.d)