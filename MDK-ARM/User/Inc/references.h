#ifndef __references_h
#define __references_h


typedef struct reference{

float Q;
float I;	
float Iline;	
	

	
float Vdc;
float Vdc_opt; 	
float Vdc_final; 
	
float dTermD;	
float dTermQ;

float thirdHarmMag;
float thirdHarmOut;	
	

}reference;


extern reference ref;


void references(void);

#endif


