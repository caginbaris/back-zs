
#ifndef __transformations_h
#define __transformations_h


#define i2 0.5
#define sqrt_2over3_ 0.81649658092772603273242802490196
#define sqrt_2over12_ 0.40824829046386301636621401245098
#define sqrt_1over2_ 0.70710678118654752440084436210485

typedef struct phase{

	double a;
	double b;
	double c;
	
}phase;


typedef struct clarke{

	double alpha;
	double beta;
	
}clarke;


typedef struct park{

	double d;
	double q;
	
}park;


typedef struct sincosValues{

	double sinVal;
	double cosVal;
	
}sincosValues;

void tCalculations(double theta,sincosValues* tVal);
void clarkeParkTransform(phase x, clarke* c, park* p ,sincosValues tVal);
void inverseClarkeParkTransform(park p, clarke* c, phase* x ,sincosValues tVal);


#endif

