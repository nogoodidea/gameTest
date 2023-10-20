#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#include "screen.h"
#include "object.h"
#include "world.h"

#define CUTOFF .0000001 
#define PI 3.1415926

typedef struct {
	vector pos;
	vector dir;
	vector up;
} camera;

camera cam;

bool raytracerInit(){
	// inital camera position and vecters
	vectorSet(&cam.pos,0.0,0.0,0.0);
	vectorSet(&cam.dir,1.0,0.0,0.0);
	vectorSet(&cam.up,0.0,1.0,0.0);
	return true;
}

//going to need a list for every object and a linked list for every object rendered in a given area

double checkIntersect(vector rayOrigin,vector rayVector,subObject tri){
	// adapted from
	// https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
	vector edge0,edge1,h,s,q;
	
	double a=0,f=0,u=0,v=0;
	vectorSub(&edge0,tri.vec[1],tri.vec[0]);
	vectorSub(&edge1,tri.vec[2],tri.vec[0]);

	vectorCrossProduct(&h,rayOrigin,edge1);
	a = vectorDotProduct(edge0,h);
	// gets the normal vector from the plane
	// i think
		
	if(a>-CUTOFF && a < CUTOFF){
		return -1;
	}

	f = 1.0/a;
	vectorSub(&s,rayOrigin,tri.vec[0]);
	u = f * vectorDotProduct(s,h);

	if(u<0.0||u+v>1.0){
		return -1;
	}

	vectorCrossProduct(&q,s,edge0);
	v = f *vectorDotProduct(rayVector,q);
	
	if(u<0.0||u+v>1.0){
		return -1;
	}
	
	double t = f *vectorDotProduct(edge1,q);
	
	if(t>CUTOFF){
		printf("WE GOT A HIT :)");
		return t;
	}
	return -1;
}

void raytraceRay(pixelColor *pixel,vector camera,vector angle,objectArray world){
	double t=0;
	double temp=0;
	color *colors = NULL;
	for(unsigned int o=0;o<world.count;o+=1){
		for(unsigned int i=0;i<world.obj[o]->count;i+=1){
			temp = checkIntersect(camera,angle,*(world.obj[o]->obj[i]));
			if(temp > t){
				t=temp;
				colors = &((world.obj[o]->obj[i])->colors);
			}
		}
	}
	if(colors != NULL){
		pixel->bright = t*10;
		pixel->red = colors->R;
		pixel->green= colors->G;
		pixel->blue = colors->B;
	}
}

// does the raytraceing
bool raytrace(screenBuffer *screen,objectArray world){
	// does the fov calculations
	// https://en.wikipedia.org/wiki/Ray_tracing_(graphics)#Calculate_rays_for_rectangular_viewport
	const double dist = screen->y; // edit to change ray angle

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
			raytraceRay(&(screen->buffer[y][x]),cam.pos,ray,world);
		}
	}
	return true;
}


