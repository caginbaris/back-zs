#include "states.h"
#include "plib.h"
#include "ios.h"
#include "faultHandling.h"
#include "LEDs.h"
#include "flagHandling.h"

static delay_parameters timeout={0,samplingRate*5,0};

stateID stopped_state(void){
	
// board indicators	
LED.out._2=0;
LED.out._3=0;

//panel indicators
panelOutput.ch.statcomTrip=0;		
panelOutput.ch.statcomReady=0 ;			
panelOutput.ch.statcomRunning=0;

//set signals
panelOutput.ch.openCB1=1;
panelOutput.ch.openCB2=1;
	
panelOutput.ch.closeCB1=0;
panelOutput.ch.closeCB2=0;	
	
panelOutput.ch.closePrechargeCB1=0;
panelOutput.ch.closePrechargeCB2=0;		
	

on_delay(1,&timeout);
	
if(timeout.output){
	
currentState=ready;
flag.ch.stop=0;	
	
if(faultWord.all){currentState=fault;}

previousState=stopped;

timeout.count=0;
timeout.output=0;

panelOutput.ch.openCB1=0;
panelOutput.ch.openCB2=0;

}

return currentState;

}

