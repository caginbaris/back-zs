#ifndef __controlRoutines_h
#define __controlRoutines_h

#include "clib.h"
#include "mlib.h"


extern pll_parameters pll;
extern phase V,I;
extern clarke cV,cI;
extern park  pV,pI;
extern float theta;

extern phase  posOut,negOut,final;

extern piInit pidInit,piqInit,pidcInit;

extern piData pidf,piqf,pidcf;
extern piData pidnf,piqnf;

extern sincosValues scVal;


extern park ipV;




void controlRoutines(void);

//void dqFiltering(park in, park* out,float* interValue,sos_parameters* sosP, float* fofP);

typedef struct dqFilterBuffers{
	

float filterBuffer[2];
sos_parameters sosBuffer[2];
float fofBuffer[2];


}dqFilterBuffers;


typedef struct decouplingTerms{
	

float Pd;
float Pq;	
float Nd;
float Nq;	

}decouplingTerms;

void dqFiltering(park in, park* out,dqFilterBuffers* b);
#endif


