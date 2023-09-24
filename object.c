#include<stdlib.h>
#include<math.h>

#include"object.h"

#define MAXPRESISION 0.00000001

subObject *intSubObject(){
	subObject *object = malloc(sizeof(subObject));
	// allways has 3 vectors
	for(int i=0;i<3;i+=1){
		object->vec[i] = malloc(sizeof(vector));
		//TODO error check for malloc calls
	}
	return object;
}

void freeSubObject(subObject **object){
	for(int i=0;i<4;i+=1){
		free((*object)->vec[i]);
	}
	free((*object));
	object = NULL;
}

// math ahead
void vectorCrossProduct(vector *vecOut,vector vec0,vector vec1){
	//https://www.mathsisfun.com/algebra/vectors-cross-product.html
	vecOut->X=(((vec0.Y)*(vec1.Z))-((vec0.Z)*(vec1.Y)));
	vecOut->Y=(((vec0.Z)*(vec1.X))-((vec0.X)*(vec1.Z)));
	vecOut->Z=(((vec0.X)*(vec1.Y))-((vec0.Y)*(vec1.X)));
}

void vectorScaler(vector *vecOut,vector vec0,double scaler){
	vecOut->X = vec0.X*scaler;
	vecOut->Y = vec0.Y*scaler;
	vecOut->Z = vec0.Z*scaler;
}

void vectorAdd(vector *vecOut,vector vec0,vector vec1){
	vecOut->X = vec0.X+vec1.X;
	vecOut->Y = vec0.Y+vec1.Y;
	vecOut->Z = vec0.Z+vec1.Z;
}

void vectorSub(vector *vecOut,vector vec0,vector vec1){
	vecOut->X = vec0.X-vec1.X;
	vecOut->Y = vec0.Y-vec1.Y;
	vecOut->Z = vec0.Z-vec1.Z;
}

void vectorNormal(vector *vec){
	double sum = sqrt((pow(vec->X,2))+(pow(vec->Y,2))+(pow(vec->Z,2)));
	vec->X /= sum;
	vec->Y /= sum;
	vec->Z /= sum;
};

double vectorDotProduct(vector vec0,vector vec1){
	double out=0.0f;
	out += vec0.X*vec1.X;
	out += vec0.Y*vec1.Y;
	out += vec0.Z*vec1.Z;
	return out;
}
