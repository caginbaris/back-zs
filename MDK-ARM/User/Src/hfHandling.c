#include "mapHandling.h"
#include "ios.h"
#include "plib.h"
#include "maphandling.h"
#include "flaghandling.h"

static transition_parameters hf1on,hf1off={0,0};
static transition_parameters hf2on,hf2off={0,0};

static delay_parameters hf1Enable={0,samplingFrequency*60,0};
static delay_parameters hf2Enable={0,samplingFrequency*60,0};


static delay_parameters bothActiveDelay={0,samplingFrequency*60,0};

static delay_parameters hf2DelayedOutput={0,samplingFrequency*0.5,0};


//cau call before ios

void hfHandling(void){
	
	uint8_t hf2Flag=0;
	
	on_off_delay((flag.ch.local==1 && QrefLocalStatcom<-50000.0f) || (flag.ch.remote==1 && QrefRemoteIncStatcom<-50000.0f) ,&bothActiveDelay);
	
	if(bothActiveDelay.output){
		
		panelOutput.ch.hf1=1;
		hf2Flag=1;
	
	}else{
		
		panelOutput.ch.hf1=0;
		panelOutput.ch.hf2=0;
	
	}
	
	//delay for simultaneous closing
	on_delay(hf2Flag,&hf2DelayedOutput);
	if(hf2DelayedOutput.output){panelOutput.ch.hf2=1;};
	
	
	//hfmanual control
	if(flag.ch.hfManualControl){
		
		panelOutput.ch.hf1=hfKomutlar.ch._2;
		panelOutput.ch.hf2=hfKomutlar.ch._3;
	
	}
	
	
	// part added for delay between switching
	high2lowTransition(panelOutput.ch.hf1,&hf1off);
	high2lowTransition(panelOutput.ch.hf2,&hf2off);
	
	off_delay(hf1off.output,&hf1Enable);
	off_delay(hf2off.output,&hf2Enable);
	
	if(hf1Enable.output==1){panelOutput.ch.hf1=0;}
	if(hf2Enable.output==1){panelOutput.ch.hf2=0;}

}