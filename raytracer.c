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
	vector up;
} camera;

camera cam;

bool raytracerInit(){
	// inital camera position and vecters
	vectorSet(&(cam.pos),0.0f,0.0f,0.0f);
	vectorSet(&(cam.dir),1.0f,0.0f,0.0f);
	vectorSet(&(cam.up),0.0f,1.0f,0.0f);
	return true;
}

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

void raytraceFrame(pixelColor *pixel,vector camera,vector angle){
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
		pixel->bright = t;
		pixel->red = colors->R;
		pixel->green= colors->G;
		pixel->blue = colors->B;
	}
}

// does the raytraceing
bool raytrace(screenBuffer *screen){
	// does the fov calculations
	// https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
	const double dist = 10.0; // edit to change ray angle

	vector right,yTemp,xTemp,zTemp,temp,first,ray;
	vectorCopy(&right,cam.up);
	vectorRotate(&right,cam.dir,cam.pos,PI/2); // gets
	
	
	vectorScaler(&yTemp,cam.up,(screen->y)/2);
	vectorScaler(&xTemp,right,(screen->x)/2);
	vectorScaler(&zTemp,cam.dir,dist);

	vectorSub(&temp,zTemp,xTemp);
	vectorSub(&first,temp,yTemp);

	vector xVector,yVector;
	vectorScaler(&xVector,right,(screen->x)/((screen->x/2)-1));
	vectorScaler(&yVector,cam.up,(screen->y)/((screen->y/2)-1));
	
	for(unsigned int y=0;y<screen->y;y+=1){
		vectorScaler(&yTemp,yVector,y);
		for(unsigned int x=0;x<screen->x;x+=1){
			vectorScaler(&xTemp,xVector,x);
			vectorAdd(&temp,first,xTemp);
			vectorAdd(&ray,temp,yTemp);
			// zero the screen buffer	
			screenZeroPixel(&(screen->buffer[y][x]));
			// trace the rays
			raytraceFrame(&(screen->buffer[y][x]),cam.pos,ray);
		}
	}
	return true;
}


