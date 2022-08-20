#include "states.h"
#include "ios.h"
#include "faultHandling.h"
#include "measurements.h"
#include "LEDs.h"
#include "flagHandling.h"

stateID fault_state(void){

// board indicators	
LED.out._2=0;
LED.out._3=0;

//panel indicators
panelOutput.ch.statcomTrip=1;		
panelOutput.ch.statcomReady=0 ;			
panelOutput.ch.statcomRunning=0;

//set signals
panelOutput.ch.openCB1=1;
panelOutput.ch.openCB2=1;
	
panelOutput.ch.closeCB1=0;
panelOutput.ch.closeCB2=0;	
	
panelOutput.ch.closePrechargeCB1=0;
panelOutput.ch.closePrechargeCB2=0;		
	

if(flag.ch.reset){
	

if(faultWord.all==0){currentState=ready;}

if(currentState!=fault){previousState=fault;}

panelOutput.ch.openCB1=0;
panelOutput.ch.openCB2=0;

}

return currentState;

}
