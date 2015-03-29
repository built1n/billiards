CC = gcc

OBJ = src/billiards.o \
      src/maths.o \
      src/ball.o \

CFLAGS = -Isrc/ -O3 -std=gnu99

SDLOBJ = platforms/sdl/sdl.o

SDLFLAGS = -lm -lSDL -Iplatforms/sdl

sdl: $(OBJ) $(SDLOBJ) Makefile
	@echo "CC $<"
	@$(CC) $(OBJ) $(SDLOBJ) -o billiards_sdl $(CFLAGS) $(SDLFLAGS)

%.o: %.c Makefile
	@echo "CC $<"
	@$(CC) $(CFLAGS) $(SDLFLAGS) -c $< -o $@
