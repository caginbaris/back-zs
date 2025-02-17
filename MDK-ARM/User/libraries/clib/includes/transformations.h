
#ifndef __transformations_h
#define __transformations_h


#define i2 0.5f
#define sqrt_2over3_ 0.81649658092772603273242802490196f
#define sqrt_2over12_ 0.40824829046386301636621401245098f
#define sqrt_1over2_ 0.70710678118654752440084436210485f

typedef struct phase{

	float a;
	float b;
	float c;
	
}phase;


typedef struct clarke{

	float alpha;
	float beta;
	
}clarke;


typedef struct park{

	float d;
	float q;
	
}park;


typedef struct sincosValues{

	float sinVal;
	float cosVal;
	
}sincosValues;

void tCalculations(float theta,sincosValues* tVal);
void clarkeParkTransform(phase x, clarke* c, park* p ,sincosValues tVal);
void inverseClarkeParkTransform(park p, clarke* c, phase* x ,sincosValues tVal);


#endif

