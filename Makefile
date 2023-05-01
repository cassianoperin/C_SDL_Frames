SRC_DIR = src
# BUILD_DIR = build/debug
BUILD_DIR = src/
CC = gcc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_NAME = main
INCLUDE_PATHS = -Iinclude
LIBRARY_PATHS = -Llib
# COMPILER_FLAGS = -std=c++11 -pedantic -Wall -O0 -g
COMPILER_FLAGS = -std=c11 -Wall -O0 -g
# LINKER_FLAGS = -lsdl2 -lSDL2_image
LINKER_FLAGS = -lsdl2 -lSDL2_ttf

all:
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)