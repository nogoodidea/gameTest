CC := gcc
CC_FLAGS := -Wall -fsanitize=address -g
LD_FLAGS := -lm -lSDL2 -lSDL2_image
GAMETESTFILES := render.c main.c screen.c controls.c object.c raytracer.c world.c
all:
	$(CC) $(GAMETESTFILES) $(CC_FLAGS) $(LD_FLAGS) -o gameTest

clean:
	rm gameTest

memoryLeakChecker:
	$(CC_FLAGS) += -fsanitize=address -fanalyzer

debug:	memoryLeakChecker all
