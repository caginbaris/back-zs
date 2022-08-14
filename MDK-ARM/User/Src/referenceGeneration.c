#include "references.h"
#include "controlRoutines.h"
#include "measurements.h"

#define dc2ac 0.612 // no 3rd
#define idc2ac (1.0/dc2ac) 
#define Lvalue 0.001
#define Xvalue (Lvalue*2*3.14159*50)
#define ratedCurrent 10.0
#define requiredVoltage (ratedCurrent*Xvalue)
#define sqrt3 1.732050807568877


reference ref={0};

static float ref_oz=0;

static float fofCoefficents1e0[2]={

0.0000628279055607806,
-0.999874344188878

};
	
void init_references(void){


ref.Vdc=56;
ref.Vdc_final=65;	
	
ref.Q=0;
ref.I=0;		
ref.dTermD=0;
ref.dTermQ=0;


}	
	

void references(void){
	
	
	ref.I=ref.Iline*1.732f;
	
	FOF((tRMS[rms_Van].out+ref.Iline*0.314f)*2.83f*0.87f,ref_oz,ref.Vdc_opt,fofCoefficents1e0);
	
	
	ref.thirdHarmTheta=3*scVal.sinVal-4*scVal.sinVal*scVal.sinVal*scVal.sinVal;
	ref.thirHarmOut=tRMS[3].out*1.414f*0.1667f*ref.thirdHarmTheta;
	
	//ref.I = (Vdf > 10.0) ? ref.Q/Vdf : ref.I;
	
	//FOF((tRMS[rms_Vab].out*1.414),ref_iz,ref.Vdc_initial,fofCoefficents1e0);
	//FOF((tRMS[rms_Van].out+requiredVoltage)*sqrt3*idc2ac,ref_fz,ref.Vdc_final,fofCoefficents1e0);
	
	
								

}






