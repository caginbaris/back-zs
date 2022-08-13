
#ifndef __filtering_h
#define __filtering_h


#include <stdint.h>


typedef struct sos_parameters{
	
	float xz2;
	float xz1;
	float yz2;		
	
	
}sos_parameters;

float filtering(float rtInput,  float *coeff, uint16_t coeffLength, float *zValues);

float fof_implementation(float rtInput,float* xz,float yz,  float *coeffs);
float sos_implementation(float x ,float yBack,   float *coeffs, sos_parameters *back);

//macros

#define FOF(x,xz,y,coeffs)  		y=fof_implementation(x,&xz,y,coeffs)
#define SOS(x,y,coeffs,params)  y=sos_implementation(x,y,coeffs,&params)


#endif

