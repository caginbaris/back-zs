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

ref.Vdc=30;

}


void references(void){
	
	
	ref.I=ref.Iline*1.732f;
	
	FOF((tRMS[rms_Van].out+ref.Iline*Xvalue)*sqrt3*idc2ac,ref_oz,ref.Vdc_opt,fofCoefficents1e0);
	
	// third harmonic generation
	ref.thirdHarmMag=sqrtf(ipV.d*ipV.d + ipV.q*ipV.q)*0.16667f;
	ref.thirdHarmOut=sinf(3.0f *pll.theta)*ref.thirdHarmMag;
	 
								

}






