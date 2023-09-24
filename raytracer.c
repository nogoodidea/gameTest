#include<stdbool.h>
#include<stdlib.h>

#include "screen.h"
#include "object.h"

#define CUTOFF .0000001 
#define PI 3.1415926
#define INTERSECTFAIL 	free(edge0);\
	free(edge1);\
	free(h);\
	free(s);\
	free(q);

typedef struct {
	vector pos;
	vector dir;
} camera;




//going to need a list for every object and a linked list for every object rendered in a given area
object **objectArry=NULL;




double checkIntersect(vector rayOrigin,vector rayVector,subObject tri){
	// adapted from
	// https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
	vector *edge0 = malloc(sizeof(vector));
	vector *edge1 = malloc(sizeof(vector));
	vector *h = malloc(sizeof(vector));
	vector *s = malloc(sizeof(vector));
	vector *q = malloc(sizeof(vector));
	
	double a=0,f=0,u=0,v=0;
	vectorSub(edge0,*tri.vec[1],*tri.vec[0]);
	vectorSub(edge1,*tri.vec[2],*tri.vec[0]);

	vectorCrossProduct(h,rayOrigin,*edge1);
	a = vectorDotProduct(*edge0,*h);
	// gets the normal vector from the plane
	// i think
	
	if(a>-CUTOFF && a < CUTOFF){
		INTERSECTFAIL
		return -1;
	}

	f = 1.0/a;
	vectorSub(s,rayOrigin,*tri.vec[0]);
	u = f * vectorDotProduct(*s,*h);

	if(u<0.0||u+v>1.0){
		INTERSECTFAIL
		return -1;
	}

	vectorCrossProduct(q,*s,*edge0);
	v = f *vectorDotProduct(rayVector,*q);
	
	if(u<0.0||u+v>1.0){
		INTERSECTFAIL
		return -1;
	}
	
	double t = f *vectorDotProduct(*edge1,*q);
	
	INTERSECTFAIL
	if(t>CUTOFF){
		return -1;
	}
	return t;
}

void raytrace(pixelColor *pixel,vector camera,vector angle){
	if(objectArry==NULL){
		return;
	}
	double t=0;
	double temp=0;
	color *colors = NULL;
	for(unsigned int o=0;;o+=1){
		for(unsigned int i=0;i<objectArry[o]->count;i+=1){
			temp = checkIntersect(camera,angle,objectArry[o]->objects[i]);
			if(temp > t){
				t=temp;
				colors = &((objectArry[o]->objects[i]).colors);
			}
		}
	}
	if(colors != NULL){
		pixel->bight = t;
		pixel->red = colors->R;
		pixel->green= colors->G;
		pixel->blue = colors->B;
	}
}

// does the raytraceing
bool render(screenBuffer *screen,subObject camera){
	// does the fov calculations
	// https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
	const double fov = PI/2;// human fov

	vector *angle = malloc(sizeof(vector));
	vectorCrossProduct(angle,*camera.vec[1],*camera.vec[2]);
	vectorNormal(angle);
	//camera->vec[0] Camera possition
	// the other vects are for normalazation

	for(unsigned int y=0;y<screen->y;y+=1){
		for(unsigned int x=0;x<screen->x;x+=1){

			screenZeroPixel(&(screen->buffer[y][x]));
			raytrace(&(screen->buffer[y][x]),*camera.vec[0],*angle);
		}
	}
	free(angle);
	return true;
}


