#include "mlib.h"
#include "plib.h"
#include "adcHandling.h"
#include "main.h"
#include "faultHandling.h"
#include "states.h"

float fundamentalFrequency=0;
static delay_parameters p={0,100,0};
static delay_parameters freqCheck={0,4000,0};
static transition_parameters t={0,0};





void frequencyDetect(float input,float *output){

		static uint32_t pulseCount=0;
 
    on_off_delay(input>0,&p);
	
		low2highTransition(p.output, &t);
		
	
		if(t.output || pulseCount>20000){

			if(pulseCount!=0){
				
				*output=samplingFrequency/((float)(pulseCount));
				
				}
			
				pulseCount=0;
			}	
			
		pulseCount++;
 
}


void frequencyMeasurement(void){

	frequencyDetect(adc.ch.Van,&fundamentalFrequency);
	
	on_delay((fundamentalFrequency<48.0f || fundamentalFrequency>52.0f) && (currentState==idle || currentState==run),&freqCheck);
	
	if(freqCheck.output){faultWord.bit.gridFrequency=1;}
	

}

