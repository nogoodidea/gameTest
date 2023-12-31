#ifndef OBJECT_H
#define OBJECT_H

// math time :(
typedef struct vector_s {
	double X;
	double Y;
	double Z;
} vector;
// colors for objects

typedef struct {
	unsigned int R;
	unsigned int G;
	unsigned int B;
} color;

// square objects
typedef struct subObject_s{
	vector vec[3]; // triangle
	color colors;
} subObject;

// object in area, used 
typedef struct object_s {
	subObject **obj;
	unsigned int count;
} object;

// vector math
void vectorSet(vector *vec,double X,double Y,double Z);

void vectorCopy(vector *vec0,vector vec1);

void vectorCrossProduct(vector *vecOut,vector vec0,vector vec1);

void vectorScaler(vector *vecOut,vector vec0,double scaler);

void vectorAdd(vector *vecOut,vector vec0,vector vec1);

void vectorSub(vector *vecOut,vector vec0,vector vec1);

void vectorMult(vector *vecOut,vector vec0,vector vec1);

void vectorNormal(vector *vec);

void vectorRotate(vector *vec,vector line,vector point,double theta);

double vectorDotProduct(vector vec0,vector vec1);

// obj functions
void objectRotate(object obj,vector line,vector point,double theta);

void objectScaler(object obj,double scaler);

void subObjectCopy(subObject *subObjOut,subObject subObj);

void subObjectSet(subObject *subObjOut,vector vec0,vector vec1,vector vec2);
//object int/add/free
subObject *initSubObject();

object *initObject(unsigned int amt);

void addSubObject(object *obj,subObject *objAdd);

void freeSubObject(subObject **obj);

void freeObject(object **obj);

// logging
void vectorPrint(vector vec,char *name);

void subObjectPrint(subObject subObj,char *name);

#endif //OBJECT_H
