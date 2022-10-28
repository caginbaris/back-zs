#include "main.h"
#include "ios.h"
#include "flagHandling.h"
#include "states.h"
#include "plib.h"

flags flag={0};

static delay_parameters resetOffDelay={0,samplingFrequency*0.1,0};
static transition_parameters resetOn={0};

static delay_parameters startOffDelay={0,samplingFrequency*0.1,0};
static transition_parameters startOn={0};

static delay_parameters stopOffDelay={0,samplingFrequency*0.1,0};
static transition_parameters stopOn={0};


void flagHandling(void){
	
// reset handling	

if(panelInput.ch.reset==1 && currentState==fault){flag.ch.reset=1;}

low2highTransition(flag.ch.reset,&resetOn);

off_delay(resetOn.output,&resetOffDelay);

flag.ch.reset=resetOffDelay.output;

// start handling


if(panelInput.ch.start==1 && currentState==ready){flag.ch.start=1;}

low2highTransition(flag.ch.start,&startOn);

off_delay(startOn.output,&startOffDelay);

flag.ch.start=startOffDelay.output;



// stop handling

if(panelInput.ch.stop==1){flag.ch.stop=1;}

low2highTransition(flag.ch.stop,&stopOn);

off_delay(stopOn.output,&stopOffDelay);

flag.ch.stop=stopOffDelay.output;
	

}
