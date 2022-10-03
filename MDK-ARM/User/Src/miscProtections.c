#include "plib.h"
#include "adcHandling.h"
#include "measurements.h"
#include "ios.h"
#include "faultHandling.h"
#include "states.h"

#define averagingPeriod (samplingFrequency/50.0f)
#define averagingFactor (1.0f/averagingPeriod)

#define meanCurrentThreshold 10.0f
#define dcRippleThreshold 15.0f

#define temp1threshold 75.0f
#define temp2threshold 80.0f



float meanValueIa=0;
float meanValueIb=0;
float meanValueIc=0;

static delay_parameters mIaDelay={0,samplingFrequency*0.1,0};
static delay_parameters mIbDelay={0,samplingFrequency*0.1,0};
static delay_parameters mIcDelay={0,samplingFrequency*0.1,0};

void meanCurrentCheck(void){
	
	static uint32_t meanValueCounter=0;
	
	static float meanValueSumIa=0;
	static float meanValueSumIb=0;
	static float meanValueSumIc=0;
	
	meanValueSumIa+=adc.ch.Ia;
	meanValueSumIb+=adc.ch.Ib;
	meanValueSumIc+=adc.ch.Ic;
	
	meanValueCounter++;
	
	if(meanValueCounter==averagingPeriod){
	
	meanValueCounter=0;
		
	meanValueIa=meanValueSumIa*averagingFactor;	
	meanValueIb=meanValueSumIb*averagingFactor;
	meanValueIc=meanValueSumIc*averagingFactor;
		
	meanValueSumIa=0;	
	meanValueSumIb=0;
	meanValueSumIc=0;	
		
		
	}
	
	on_delay(meanValueIa>meanCurrentThreshold,&mIaDelay);
	on_delay(meanValueIb>meanCurrentThreshold,&mIbDelay);
	on_delay(meanValueIc>meanCurrentThreshold,&mIcDelay);
	
	
	if(mIaDelay.output){faultWord.bit.meanIa=1;}
	if(mIbDelay.output){faultWord.bit.meanIb=1;}
	if(mIcDelay.output){faultWord.bit.meanIc=1;}

	
}


void dcRippleCheck(void){
	
	static delay_parameters dcRippleDelay={0,samplingFrequency*10,0};
	
	on_delay(tRMS[rms_dcr].out>dcRippleThreshold,&dcRippleDelay); 
	
	if(dcRippleDelay.output){faultWord.bit.dcRippleOverLimit=1;}
	

}


void phaseSeqCheck(void){

	
	
	static delay_parameters phaseSeqDelay={0,samplingFrequency*3,0};
	
	on_delay((tRMS[rms_V2].out>tRMS[rms_V1].out*0.25f) && (currentState==idle || currentState==run) ,&phaseSeqDelay);
	
	if(phaseSeqDelay.output){faultWord.bit.phaseSequence=1;}
	

}





void unbalanceCheck(void){
	
	float maxV,maxI;

	static delay_parameters unbalanceV={0,samplingFrequency*0.1,0};
	static delay_parameters unbalanceI={0,samplingFrequency*0.1,0};
	
	maxV=max3p(tRMS[rms_Van].out,tRMS[rms_Vbn].out,tRMS[rms_Vcn].out);
	maxI=max3p(tRMS[rms_Ia].out,tRMS[rms_Ib].out,tRMS[rms_Ic].out);
	
	
	
	on_delay((tRMS[rms_V2].out>tRMS[rms_V1].out*0.1f) && maxV>10.0f && (currentState==idle || currentState==run),&unbalanceV);
	on_delay((tRMS[rms_I2].out>tRMS[rms_I1].out*0.2f) && maxI>20.0f && (currentState==idle || currentState==run),&unbalanceI);
	
	if(unbalanceV.output){faultWord.bit.voltageUnbalance=1;}
	if(unbalanceI.output){faultWord.bit.currentUnbalance=1;}

}

void zeroSequenceCheck(void){
	
	float maxV,maxI;

	static delay_parameters zeroV={0,samplingFrequency*0.04,0};
	static delay_parameters zeroI={0,samplingFrequency*0.08,0};
	
	maxV=max3p(tRMS[rms_Van].out,tRMS[rms_Vbn].out,tRMS[rms_Vcn].out);
	maxI=max3p(tRMS[rms_Ia].out,tRMS[rms_Ib].out,tRMS[rms_Ic].out);
	
	on_delay((tRMS[rms_V0].out>tRMS[rms_V1].out*0.1f)&& maxV>10.0f && (currentState==idle || currentState==run),&zeroV);
	on_delay((tRMS[rms_I0].out>tRMS[rms_I1].out*0.2f)&& maxI>20.0f && (currentState==idle || currentState==run),&zeroI);
	
	if(zeroV.output){faultWord.bit.voltageZeroSequence=1;}
	if(zeroI.output){faultWord.bit.currentZeroSequence=1;}

}

void tempCheck(void){
	
static delay_parameters temp1={0,samplingFrequency,0};
static delay_parameters temp2={0,samplingFrequency*0.1,0};

on_delay(tRMS[rms_temp].out>temp1threshold,&temp1);
on_delay(tRMS[rms_temp].out>temp2threshold,&temp2);


if(temp1.output || temp2.output){faultWord.bit.ipmTemperature=1;}

}

void miscProtections(){

	meanCurrentCheck();
	dcRippleCheck();
	unbalanceCheck();
	zeroSequenceCheck();
	tempCheck();
	
	if(currentState!=run){phaseSeqCheck();}
	

}
