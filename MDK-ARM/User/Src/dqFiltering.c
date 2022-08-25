
#include "mlib.h"
#include "clib.h"
#include "controlRoutines.h"

/*
%notch filter
[bn,an]=butter(1,[90 111.2]/(fs*0.5),'stop');
*/


static float sosCoefficentsNotch[]={
	
	 0.993383790867002f,  -1.982843956421446f,   0.993383790867002f,
  -1.982843956421515f,   0.986767581734073f

};

static float fofCoefficents150hz[2]={

0.045035005911131f,
-0.909929988177738f

};



//example usage -- dqFiltering(pV,&pVf,intervalue(array with 2 elements),sosP(sos array with 2 elements),fofP(array with 2 elements)

/*
void dqFiltering(park in, park* out,float* interValue,sos_parameters* sosP, float* fofP){


interValue[0]=sos_implementation(in.d,interValue[0],sosCoefficentsNotch,&sosP[0]);
out->d=fof_implementation(interValue[0],&fofP[0],out->d,fofCoefficents150hz); 

interValue[1]=sos_implementation(in.q,interValue[1],sosCoefficentsNotch,&sosP[1]);
out->q=fof_implementation(interValue[1],&fofP[1],out->q,fofCoefficents150hz); 

}*/


void dqFiltering(park in, park* out,dqFilterBuffers* b){


b->filterBuffer[0]=sos_implementation(in.d,b->filterBuffer[0],sosCoefficentsNotch,&b->sosBuffer[0]);
out->d=fof_implementation(b->filterBuffer[0],&(b->fofBuffer[0]),out->d,fofCoefficents150hz); 

b->filterBuffer[1]=sos_implementation(in.q,b->filterBuffer[1],sosCoefficentsNotch,&b->sosBuffer[1]);
out->q=fof_implementation(b->filterBuffer[1],&(b->fofBuffer[1]),out->q,fofCoefficents150hz); 

}

