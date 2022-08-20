#include "states.h"
#include "adcHandling.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "LEDs.h"
#include "flagHandling.h"

static transition_parameters startTrigger={0,0};

stateID ready_state(void){
	
// board indicators	
	
LED.out._2=1;
LED.out._3=0;		
	
//panel indicators	
	
panelOutput.ch.statcomTrip=0;		
panelOutput.ch.statcomReady=1;			
panelOutput.ch.statcomRunning=0;
	

low2highTransition(flag.ch.start,&startTrigger);	

if(startTrigger.output){currentState=charged;}
if(faultWord.all){currentState=fault;}

if(currentState!=ready){

previousState=ready;
startTrigger.back=0;

}

return currentState;

}

