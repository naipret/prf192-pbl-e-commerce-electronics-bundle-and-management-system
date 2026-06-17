ifeq ($(OS),Windows_NT)
SHELL := cmd.exe
EXE_EXT := .exe
FIX_PATH = $(subst /,\,$1)
MKDIR = if not exist $(call FIX_PATH,$1) mkdir $(call FIX_PATH,$1)
RM = if exist $(call FIX_PATH,$1) rmdir /S /Q $(call FIX_PATH,$1)
else
EXE_EXT :=
MKDIR = mkdir -p $1
RM = rm -rf $1
endif

INC_DIR := include
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

CC := clang
CFLAGS := -std=c17 -m64 -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wformat=2 \
    -Wformat-security -Wfloat-equal -Wundef -Wsign-conversion -Wcast-align \
    -Wcast-qual -Wmissing-prototypes -Wmissing-declarations -Wunreachable-code \
    -Wnull-dereference -Wimplicit-fallthrough -Wswitch-enum -Wpointer-arith \
    -I$(INC_DIR)
LDFLAGS := -m64

TARGET_NAME := prf192-pbl-e-commerce-electronics-bundle-and-management-system
TARGET := $(BIN_DIR)/$(TARGET_NAME)$(EXE_EXT)

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

.PHONY: all clean format tidy

all: $(TARGET)

$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BIN_DIR):
	@$(call MKDIR,$(BIN_DIR))

$(OBJ_DIR):
	@$(call MKDIR,$(OBJ_DIR))

clean:
	@$(call RM,$(OBJ_DIR))
	@$(call RM,$(BIN_DIR))

format:
	clang-format -i $(INC_DIR)/*.h $(SRC_DIR)/*.c

tidy:
	clang-tidy $(SRC) -- $(CFLAGS)
