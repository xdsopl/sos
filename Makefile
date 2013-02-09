
CFLAGS = $(shell sdl-config --cflags) -std=c99 -Wall -W -O3 -Wextra -ffast-math -g
LDFLAGS = $(shell sdl-config --libs) -lm -lGL

all: sos

test: sos
	./sos

sos: sos.c

clean:
	rm -f sos

