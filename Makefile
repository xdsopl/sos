
CFLAGS = $(shell sdl-config --cflags) -std=c99 -Wall -W -O3 -Wextra -fno-math-errno -ffinite-math-only -fno-rounding-math -fno-signaling-nans -fno-trapping-math -fcx-limited-range -fsingle-precision-constant -g
LDFLAGS = $(shell sdl-config --libs) -lm -lGL

WIN32_CC = i686-mingw32-gcc
WIN32_CFLAGS = -I../SDL-1.2.15/include/SDL -DM_PI="3.14159265358979323846" -D_GNU_SOURCE=1 -Dmain=SDL_main -std=c99 -Wall -W -O3 -Wextra -fno-math-errno -ffinite-math-only -fno-rounding-math -fno-signaling-nans -fno-trapping-math -fcx-limited-range -fsingle-precision-constant -msse -msse2 -mfpmath=sse
WIN32_LDFLAGS = -L../SDL-1.2.15/lib -lmingw32 -lSDLmain -lSDL -mwindows -lopengl32

all: sos
win: win32/sos.exe

test: sos
	./sos

sos: sos.c *.h Makefile
	$(CC) -o sos sos.c $(CFLAGS) $(LDFLAGS)

win32/sos.exe: sos.c *.h Makefile
	$(WIN32_CC) -o win32/sos.exe sos.c $(WIN32_CFLAGS) $(WIN32_LDFLAGS)

clean:
	rm -f sos win32/sos.exe

