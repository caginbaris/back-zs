#ifndef __controlRoutines_h
#define __controlRoutines_h

#include "clib.h"
#include "mlib.h"


extern pll_parameters pll;
extern phase V,I;
extern clarke cV,cI;
extern park  pV,pI;
extern float theta;

extern phase  cOut,final;

extern piInit pidInit,piqInit,pidcInit;
extern piData pidf,piqf,pidcf;

extern sincosValues scVal;


void controlRoutines(void);

//void dqFiltering(park in, park* out,float* interValue,sos_parameters* sosP, float* fofP);

typedef struct dqFilterBuffers{
	

float filterBuffer[2];
sos_parameters sosBuffer[2];
float fofBuffer[2];


}dqFilterBuffers;

void dqFiltering(park in, park* out,dqFilterBuffers* b);
#endif


