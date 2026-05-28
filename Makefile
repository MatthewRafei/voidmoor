CC = gcc
CFLAGS = -std=c99 -I/usr/include/SDL3 -Wall -Wextra -Wstrict-prototypes -Werror
LDFLAGS = -lSDL3
all:
	$(CC) $(CFLAGS) -o voidmoor ./src/*.c $(LDFLAGS)
clean:
	rm -f voidmoor
.PHONY: clean all
