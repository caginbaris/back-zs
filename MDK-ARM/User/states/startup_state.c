#include "states.h"
#include "plib.h"
#include "ios.h"
#include "LEDs.h"
#include "faultHandling.h"
#include "ios.h"
#include "flagHandling.h"
#include "pwmGeneration.h"

static delay_parameters startupPassTime={0,samplingRate*6,0};
static delay_parameters startupToggle={0,samplingRate*1,0};

stateID startup_state(void){

//initial DO & LED action

fToggle(1,&startupToggle);

LED.out._2=startupToggle.output;
LED.out._3=startupToggle.output;
	
// panel indicators	
	
panelOutput.ch.statcomTrip=startupToggle.output;		
panelOutput.ch.statcomReady=startupToggle.output;			
panelOutput.ch.statcomRunning=0;	
	
	
//output signal set
	
panelOutput.ch.openCB1=1;
panelOutput.ch.openCB2=1;
	
panelOutput.ch.closeCB1=0;
panelOutput.ch.closeCB2=0;	
	
panelOutput.ch.closePrechargeCB1=0;
panelOutput.ch.closePrechargeCB2=0;	


on_delay(1,&startupPassTime);
	
	
if(startupPassTime.output){
	
startupPassTime.count=0;

currentState=ready;
previousState=startup;
	
flag.ch.reset=1; // reset raised before exiting
	

panelOutput.ch.openCB1=0;
panelOutput.ch.openCB2=0;
	
modulatorDisable();	

}

return currentState;

}

