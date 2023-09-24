#ifndef RAYTRACER_GAME_TEST_H
#define RAYTRACER_GAME_TEST_H

#include "screen.h"


//vector for 3d position in space
typedef struct vector_S {
	double X;
	double Y;
	double Z;
} vector;

typedef struct {
	vector pos;
	vector dir;
} camera;

//
bool raytracerInit();


//// does the raytraser stuff
bool raytrace(screenBuffer *screen);


#endif //RAYTRACER_GAME_TEST_H
