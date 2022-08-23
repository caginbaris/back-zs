#include <math.h>
#include "mlib.h"
#include "clib.h"
#include "controlRoutines.h"
#include "pllHandling.h"

phase Vtest={0};
clarke cTest;
park pTest,pTestF;
sincosValues sc;


dqFilterBuffers b={0};

pll_parameters pllT={0};
float pllDiff;

//1*sin(wt) transforms to 1.224 dc value during dq

#define pi_3 1.047f
#define pi_2 1.570f

void dqTransformSignalling(void){
	
static uint8_t counter=0;


Vtest.a=sinf(2*3.14159f*counter/200.0f);
Vtest.b=1.0f*sinf(2*3.14159f*counter/200.0f-2.0f*pi_3);
Vtest.c=-Vtest.a-Vtest.b;
	
sc.sinVal=sinf(2*3.14159f*counter/200.0f);
sc.cosVal=cosf(2*3.14159f*counter/200.0f);	
	
counter++;

if(counter==200){counter=0;}	

clarkeParkTransform(Vtest,&cTest,&pTest,sc);
dqFiltering(pTest, &pTestF,&b);

PLL(Vtest.a,&pllT);
pllDiff= Vtest.a-1*sinf(pllT.theta);

}