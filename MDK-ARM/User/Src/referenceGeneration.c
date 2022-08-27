#include "references.h"
#include "controlRoutines.h"
#include "measurements.h"

#define dc2ac 0.707f 
#define idc2ac (1.0f/dc2ac) 
#define Lvalue 0.0008f
#define Xvalue (Lvalue*2.0f*3.14159f*50.0f)
#define sqrt3 (1.732f)
#define sqrt2 (1.414f)



reference ref={0};
static float ref_oz=0;


void initReferences(void){

ref.Vdc=47.0f;

}



float fofCoefficents1em1[2]={

0.0000314149396167807f,
-0.999937170120766f

};

void references(void){
	
	
	ref.I=ref.Iline*1.732f;
	
	FOF((max3p(tRMS[rms_Van].out,tRMS[rms_Vbn].out,tRMS[rms_Vcn].out)-piqf.signal.ref_rateLimited*Xvalue)*sqrt3*idc2ac,ref_oz,ref.Vdc_opt,fofCoefficents1em1);
	
	// third harmonic generation
	ref.thirdHarmMag=pVf.d*0.8125f*0.16667f;
	ref.thirdHarmOut=sinf(3.0f *pll.theta)*ref.thirdHarmMag;
	 
								

}






