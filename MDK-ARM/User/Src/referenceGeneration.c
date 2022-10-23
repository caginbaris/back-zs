#include "references.h"
#include "controlRoutines.h"
#include "measurements.h"
#include "mapHandling.h"
#include "flagHandling.h"
#include "ios.h"


#define dc2ac 0.707f 
#define idc2ac (1.0f/dc2ac) 
#define Lvalue 0.0008f
#define Xvalue (Lvalue*2.0f*3.14159f*50.0f)
#define sqrt3 (1.732f)
#define sqrt2 (1.414f)

#define currentLimit 100.0f

reference ref={0};
static float ref_oz=0;
float Qhf;

void initReferences(void){

ref.Vdc=47.0f;

}



static float fofCoefficents1e1[2]={

0.003131764229193,
-0.993736471541615
};

void references(void){
	
	
	//opt vdc generation
	FOF((max3p(tRMS[rms_Van].out,tRMS[rms_Vbn].out,tRMS[rms_Vcn].out)-piqf.signal.ref_rateLimited*Xvalue)*sqrt3*idc2ac,ref_oz,ref.Vdc_opt,fofCoefficents1e1);
	
	
	// third harmonic generation
	ref.thirdHarmMag=ref.Vdc_opt*0.0962f;
	ref.thirdHarmOut=sinf(3.0f *pll.theta)*ref.thirdHarmMag;
	
	//hf and reactive references
	Qhf=-25000.0f*(panelInput.ch.hf1+panelInput.ch.hf2);							
	
	
	if(flag.ch.local==0 && flag.ch.remote==0){
	
		flag.ch.local=1;
	}
	
	if(flag.ch.local){
		
		if(pVf.d>300.0f){
			
			ref.I=(QrefLocalStatcom-Qhf)/pVf.d;
			
		}	
		
	}
	
	
	if(flag.ch.remote){
		
		if(pVf.d>300.0f){
			
			ref.I=(QrefRemoteStatcom-Qhf)/pVf.d;
			
		}
		
	}
	
	
	
	

	
	
}






