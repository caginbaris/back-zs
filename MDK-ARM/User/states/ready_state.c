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
	
//output signal set
	
panelOutput.ch.openCB1=1;
panelOutput.ch.openCB2=1;
	
panelOutput.ch.closeCB1=0;
panelOutput.ch.closeCB2=0;	
	
panelOutput.ch.closePrechargeCB1=0;
panelOutput.ch.closePrechargeCB2=0;		
	
//get start
low2highTransition(flag.ch.start,&startTrigger);//cau panel input start should be OR'ed

if(startTrigger.output){currentState=charged;}
if(faultWord.all || stateFault.all ){currentState=fault;}

if(currentState!=ready){

previousState=ready;

//start trigger reset	
startTrigger.back=0;
startTrigger.output=0;	
	
//output	
panelOutput.ch.openCB1=0;
panelOutput.ch.openCB2=0;

//reset start flag
flag.ch.start=0;	

}

return currentState;

}

