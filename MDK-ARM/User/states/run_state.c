#include "states.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "clib.h"
#include "measurements.h"
#include "LEDs.h"
#include "pwmGeneration.h"
#include "controlRoutines.h"
#include "references.h"
//#include "testBenches.h"
#include "flagHandling.h"
#include "mapHandling.h"

static delay_parameters timeout={0,samplingRate*15,0};
static delay_parameters wait4InitialConditions={0,samplingRate*5,0};
static transition_parameters checked={0};


stateID run_state(void){
	
	
uint8_t initialCheck;	

//board indicators	
LED.out._2=1;
	
//panel indicators
panelOutput.ch.statcomTrip=0;		
panelOutput.ch.statcomReady=0 ;			
panelOutput.ch.statcomRunning=1;		

//timeout
on_delay(1,&timeout);

if(timeout.output && flag.ch.switchingStarted==0){
stateFault.bit.run_timeOut=1;
}

initialCheck=	(panelInput.ch.cb1No==1 || panelInput.ch.cb2No==1) && tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.3f;

	
on_delay(initialCheck,&wait4InitialConditions);	
low2highTransition(wait4InitialConditions.output,&checked);



if(checked.output){
	
	LED.out._3=1; 
	
	if(flag.ch.coldRun==0){
	
	modulatorEnable();
	
	}
	
	flag.ch.switchingStarted=1;
	
	pidcf.flag.enable=1;
	
	pidf.flag.enable=1;
	piqf.flag.enable=1;
	
	pidnf.flag.enable=1;
	piqnf.flag.enable=1;

	//recorder();	
  	

}
	
	


ref.Vdc=ref.Vdc_opt;

modulator();


if(flag.ch.stop){currentState=stopped;}
if(faultWord.all || stateFault.all){currentState=fault;}



if(currentState!=run){
	
	recorder();
	modulatorDisable();
	
	
	
	pidcf.flag.enable=0;
	piqf.flag.enable=0;
	pidf.flag.enable=0;

	pidnf.flag.enable=0;
	piqnf.flag.enable=0;
	
	previousState=run;
	
	timeout.count=0;
	timeout.output=0;
	
	wait4InitialConditions.count=0;
	wait4InitialConditions.output=0;
	
	checked.output=0;
	checked.back=0;
	
	ref.Iline=0;
	ref.I=0;
	
	flag.ch.switchingStarted=0;
	
	
}

return currentState;
	

}

