CC := gcc
CC_FLAGS := -Wall -fsanitize=address -g
LD_FLAGS := -lSDL2 -lSDL2_image
GAMETESTFILES := render.c main.c screen.c controls.c raytracer.c  

all:
	$(CC) $(GAMETESTFILES) $(CC_FLAGS) $(LD_FLAGS) -o gameTest

clean:
	rm gameTest

memoryLeakChecker:
	$(CC_FLAGS) += -fsanitize=address -fanalyzer

debug:	memoryLeakChecker all
