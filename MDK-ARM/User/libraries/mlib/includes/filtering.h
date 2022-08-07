
#ifndef __filtering_h
#define __filtering_h


#include <stdint.h>


typedef struct sos_parameters{
	
	double xz2;
	double xz1;
	double yz2;		
	
	
}sos_parameters;

double filtering(double rtInput,  double *coeff, uint16_t coeffLength, double *zValues);

double fof_implementation(double rtInput,double* xz,double yz,  double *coeffs);
double sos_implementation(double x ,double yBack,   double *coeffs, sos_parameters *back);

//macros

#define FOF(x,xz,y,coeffs)  		y=fof_implementation(x,&xz,y,coeffs)
#define SOS(x,y,coeffs,params)  y=sos_implementation(x,y,coeffs,&params)


#endif

