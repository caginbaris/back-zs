
#include "clib.h"
#include "mlib.h"
#include "plib.h"
#include "measurements.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "testBenches.h"
#include "states.h"

pll_parameters pll={0};

static delay_parameters syncCheck={0,samplingFrequency*0.1,0};


/*

>> [b,a]=butter(1,1/(10e3*0.5),'high')

b =0.999685939389360  -0.999685939389360
a =1.000000000000000  -0.999371878778719

*/

void pllHandling(void){
	
	static float Vf=0,Vz=0;

	//hp for dc removal
	Vf=0.999685939389360f*(adc.ch.Van-Vz)+(0.999371878778719f)*Vf;
	Vz=adc.ch.Van;
	
	
	
	if(tRMS[rms_Van].out>10.0f){ 
		
	PLL(Vf/(tRMS[rms_Van].out*1.414f),&pll);
		
	}else{
		
		
	if(currentState==run)	{
		
	faultWord.bit.referenceLoss=1;	}
	
	}
	
	on_delay(pll.q>0.1f && currentState==run,&syncCheck);
	
	if(syncCheck.output){faultWord.bit.synchronization=1;}
		

}

