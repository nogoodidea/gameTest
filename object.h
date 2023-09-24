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
	vector *vec[3]; // triangle
	color colors;
} subObject;

// object in area, used 
typedef struct object_s {
	subObject *objects;
	unsigned int count;
} object;


// vector math
void vectorSet(vector *vec,double X,double Y,double Z);

void vectorCopy(vector *vec0,vector vec1);

void vectorCrossProduct(vector *vecOut,vector vec0,vector vec1);

void vectorScaler(vector *vecOut,vector vec0,double scaler);

void vectorAdd(vector *vecOut,vector vec0,vector vec1);

void vectorSub(vector *vecOut,vector vec0,vector vec1);

void vectorNormal(vector *vec);

void vectorRotate(vector *vec,vector line,vector point,double theta);

double vectorDotProduct(vector vec0,vector vec1);


