#include "main.h"
#include "ios.h"
#include "flagHandling.h"
#include "states.h"
#include "plib.h"

flags flag={0};

delay_parameters resetOffDelay={0,samplingFrequency*0.01,0};
transition_parameters resetOn={0};

void flagHandling(void){
	
// reset handling	

if(panelInput.ch.reset==1 && currentState==fault){flag.ch.reset=1;}

low2highTransition(flag.ch.reset,&resetOn);

off_delay(resetOn.output,&resetOffDelay);

flag.ch.reset=resetOffDelay.output;
	

}
