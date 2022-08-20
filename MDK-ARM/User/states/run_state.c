#include "states.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "clib.h"
#include "measurements.h"
#include "LEDs.h"
//#include "pwmGeneration.h"
//#include "controlRoutines.h"
#include "references.h"
//#include "testBenches.h"
#include "flagHandling.h"

static delay_parameters wait4InitialConditions={0,samplingRate*5,0};
static delay_parameters timeout={0,samplingRate*15,0};
static transition_parameters checked={0};

static uint8_t dcRamp=0;


stateID run_state(void){
	
	
uint8_t initialCheck;	

//board indicators	
LED.out._2=1;
	
//panel indicators
panelOutput.ch.statcomTrip=0;		
panelOutput.ch.statcomReady=0 ;			
panelOutput.ch.statcomRunning=1;		

//initialCheck=	(panelInput.ch.cb1No==1 || panelInput.ch.cb2No==1) && tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.2f;

initialCheck=1;		
	
on_delay(initialCheck,&wait4InitialConditions);
	
on_delay(wait4InitialConditions.output==0,&timeout);


if(timeout.output==1){ 

	if(flag.ch.switchingStarted==0){

		stateFault.bit.run_state_error=1;
	
	}

}	
	
	
low2highTransition(wait4InitialConditions.output,&checked);



if(checked.output){
	
	LED.out._3=1; 
	
	//modulatorEnable();
	flag.ch.switchingStarted=1;
	
	pidcf.flag.enable=1;
	piqf.flag.enable=1;
	pidf.flag.enable=1;

	recorder();	
  	

}
	
	
//cau dc ramp is removed due 3rd injection


if(flag.ch.switchingStarted){

ref.Vdc=ref.Vdc_opt;

}


//modulator();


if(panelInput.ch.stop){currentState=stopped;}
if(faultWord.all || stateFault.all){currentState=fault;}



if(currentState!=run){
	
	
	//modulatorDisable();
	
	recorder();
	
	pidcf.flag.enable=0;
	piqf.flag.enable=0;
	pidf.flag.enable=0;	
	
	dcRamp=0;
	
	previousState=run;
	
	wait4InitialConditions.count=0;
	wait4InitialConditions.output=0;
	
	timeout.count=0;
	timeout.output=0;

	checked.output=0;
	checked.back=0;
	
	flag.ch.switchingStarted=0;
	
	
}

return currentState;
	

}

