
#include "clib.h"
#include "mlib.h"
#include "plib.h"
#include "measurements.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "testBenches.h"

pll_parameters pll={0};

static delay_parameters syncCheck={0,2000,0};
static delay_parameters startupTimeout={0,100000,0};

static float fofCoefficents5em1[2]={

0.999968585060383f,
-0.999937170120766f

};



void pllHandling(void){
	
	
		pll_parameters resetPLL={0};
		
		if(startupTimeout.output){
		
			//pllTest();

			on_delay(pll.qf<0.5,&syncCheck);
			
			if(syncCheck.output){faultWord.bit.synchronization=1;}
		
	}else{
	
	
		pll=resetPLL;
	
	}
		

}