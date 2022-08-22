#include "plib.h"
#include "adcHandling.h"
#include "measurements.h"
#include "ios.h"
#include "faultHandling.h"
#include "states.h"

#define averagingPeriod (samplingFrequency/50.0f)


#define meanCurrentThreshold 5.0f
#define dcRippleThreshold 10.0f

#define temp1threshold 85.0f
#define temp2threshold 95.0f



float meanValueIa=0;
float meanValueIb=0;
float meanValueIc=0;


void meanCurrentCheck(void){
	
	static uint32_t meanValueCounter=0;
	
	static float meanValueSumIa=0;
	static float meanValueSumIb=0;
	static float meanValueSumIc=0;
	
	meanValueSumIa+=adc.ch.Ia;
	meanValueSumIb+=adc.ch.Ib;
	meanValueSumIc+=adc.ch.Ic;
	
	meanValueCounter++;
	
	if(meanValueCounter==samplingFrequency){
	
	meanValueCounter=0;
		
	meanValueIa=meanValueSumIa*averagingPeriod;	
	meanValueIb=meanValueSumIb*averagingPeriod;
	meanValueIc=meanValueSumIc*averagingPeriod;
		
	meanValueSumIa=0;	
	meanValueSumIb=0;
	meanValueSumIc=0;	
		
		
	}
	
	
	if(meanValueIa>meanCurrentThreshold){faultWord.bit.meanIa=1;}
	if(meanValueIb>meanCurrentThreshold){faultWord.bit.meanIb=1;}
	if(meanValueIc>meanCurrentThreshold){faultWord.bit.meanIc=1;}

	
}


void dcRippleCheck(void){
	
	static delay_parameters dcRippleDelay={0,samplingFrequency*10,0};
	
	on_delay(tRMS[rms_dcr].out>dcRippleThreshold,&dcRippleDelay); 
	
	if(dcRippleDelay.output){faultWord.bit.dcRippleOverLimit=1;}
	

}


void phaseSeqCheck(void){

	
	
	static delay_parameters phaseSeqDelay={0,samplingFrequency*3,0};
	
	on_delay(tRMS[rms_V2].out>tRMS[rms_V1].out*0.25f,&phaseSeqDelay);
	
	if(phaseSeqDelay.output){faultWord.bit.phaseSequence=1;}
	

}





void unbalanceCheck(void){

	static delay_parameters unbalanceV={0,samplingFrequency*0.04,0};
	static delay_parameters unbalanceI={0,samplingFrequency*0.1,0};
	
	on_delay(tRMS[rms_V2].out>tRMS[rms_V1].out*0.1f,&unbalanceV);
	on_delay(tRMS[rms_I2].out>tRMS[rms_I1].out*0.2f,&unbalanceI);
	
	if(unbalanceV.output){faultWord.bit.voltageUnbalance=1;}
	if(unbalanceI.output){faultWord.bit.currentUnbalance=1;}

}

void zeroSequenceCheck(void){

	static delay_parameters zeroV={0,samplingFrequency*0.04,0};
	static delay_parameters zeroI={0,samplingFrequency*0.08,0};
	
	on_delay(tRMS[rms_V0].out>tRMS[rms_V1].out*0.1f,&zeroV);
	on_delay(tRMS[rms_I0].out>tRMS[rms_I1].out*0.2f,&zeroI);
	
	if(zeroV.output){faultWord.bit.voltageZeroSequence=1;}
	if(zeroI.output){faultWord.bit.currentZeroSequence=1;}

}

void tempCheck(void){
	
static delay_parameters temp1={0,samplingFrequency,0};
static delay_parameters temp2={0,samplingFrequency*0.1,0};

on_delay(adc.ch.Temp>temp1threshold,&temp1);
on_delay(adc.ch.Temp>temp2threshold,&temp1);


if(temp1.output || temp2.output){faultWord.bit.ipmTemperature=1;}

}

void miscProtections(){

	meanCurrentCheck();
	dcRippleCheck();
	unbalanceCheck();
	zeroSequenceCheck();
	
	if(currentState!=run){phaseSeqCheck();}
	

}
