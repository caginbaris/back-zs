#include <stdint.h>
#include "pwmGeneration.h"
#include "plib.h"
#include "LEDs.h"

uint8_t switchingEnable=0;

static transition_parameters swHTransition={0,0};
static transition_parameters swLTransition={0,0};
static delay_parameters swEnable={0,1000,0};

void switchingTest(void){
	
	low2highTransition(switchingEnable,&swHTransition);
	off_delay(swHTransition.output,&swEnable);
	high2lowTransition(swEnable.output,&swLTransition);
	
	if(swHTransition.output){
	
	//modulatorEnable();
	switchingEnable=0;

	}
	
	if(swLTransition.output){
	
	modulatorDisable();
	
	}
	

	
	modulator();


}
