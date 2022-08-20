#include "states.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "measurements.h"
#include "LEDs.h"

static delay_parameters idleToggle={0,samplingRate*0.5,0};
static delay_parameters waiting4dcLevel={0,samplingRate*5,0};

stateID idle_state(void){
	
	
fToggle(1,&idleToggle);	
	
//boards indicator	
LED.out._2=idleToggle.output;
LED.out._3=0;


//panel indicators
panelOutput.ch.statcomTrip=0;		
panelOutput.ch.statcomReady=idleToggle.output ;			
panelOutput.ch.statcomRunning=0;	

on_delay(1,&waiting4dcLevel);	

on_delay(1,&waiting4dcLevel);
	
if(waiting4dcLevel.output==1){

	//if(tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.2f && (panelInput.ch.cb1No==1 || panelInput.ch.cb2No==1)){
	
	if(1){
		
	currentState=run;	

	}else{

	stateFault.bit.idle_state_error=1;
	
	}
	
}	
	
if(faultWord.all || stateFault.all){currentState=fault ;}

if(currentState!=idle){
waiting4dcLevel.output=0;
waiting4dcLevel.count=0;
previousState=idle;}

return currentState;

}

