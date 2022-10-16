#include "mapHandling.h"
#include "ios.h"
#include "plib.h"
#include "maphandling.h"

static transition_parameters hf1on,hf1off={0,0};
static transition_parameters hf2on,hf2off={0,0};

static delay_parameters hf1Enable={0,samplingFrequency*60,0};
static delay_parameters hf2Enable={0,samplingFrequency*60,0};

//cau call before ios

void hfHandling(void){
	
	if(komutlar.ch._1){
		
		panelOutput.ch.hf1=komutlar.ch._2;
		panelOutput.ch.hf2=komutlar.ch._3;
	
	}
	
	
	// part added for delay between switching
	high2lowTransition(panelOutput.ch.hf1,&hf1off);
	high2lowTransition(panelOutput.ch.hf2,&hf2off);
	
	off_delay(hf1off.output,&hf1Enable);
	off_delay(hf2off.output,&hf2Enable);
	
	if(hf1Enable.output==1){panelOutput.ch.hf1=0;}
	if(hf2Enable.output==1){panelOutput.ch.hf2=0;}

}