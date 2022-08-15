
#include "clib.h"
#include "mlib.h"
#include "plib.h"
#include "measurements.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "testBenches.h"

pll_parameters pll={0};

static delay_parameters syncCheck={0,2000,0};


static float fofCoefficents5em1[2]={

0.999968585060383f,
-0.999937170120766f

};



void pllHandling(void){
	
	
	if(tRMS[rms_Van].out>5.0f){ 
		
	PLL(adc.ch.Van/(tRMS[rms_Van].out*1.414f),&pll);
		
	}
	
	on_delay(pll.q<0.5f,&syncCheck);
	
	if(syncCheck.output){faultWord.bit.synchronization=1;}
		

}

