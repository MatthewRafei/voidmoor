CC = gcc
CFLAGS = -std=c99 -Iengine -Igame -Icommon -Wall -Wextra -Wstrict-prototypes -Werror
LDFLAGS = -lSDL3

# SDL3 detection
SDL_CFLAGS := $(shell sdl3-config --cflags 2>/dev/null || echo "")
SDL_LDFLAGS := $(shell sdl3-config --libs 2>/dev/null || echo "-lSDL3")
CFLAGS += $(SDL_CFLAGS)
LDFLAGS += $(SDL_LDFLAGS)

ENGINE_SRC = $(wildcard src/*.c) $(wildcard engine/*.c) $(wildcard common/*.c)
GAME_SRC = $(ENGINE_SRC) $(wildcard game/*.c)

# Engine binary
voidforge: $(ENGINE_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Game binary
voidmoor: $(GAME_SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

all: voidmoor

clean:
	rm -f voidmoor voidforge

.PHONY: all clean voidmoor voidforge
