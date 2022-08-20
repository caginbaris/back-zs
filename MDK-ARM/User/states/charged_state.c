#include "states.h"
#include "faultHandling.h"
#include "ios.h"
#include "plib.h"
#include "measurements.h"
#include "LEDs.h"
#include "flagHandling.h"

//cau call ios before states
//cau call fault after states

static delay_parameters chargedToggle={0,samplingRate*1,0};

static delay_parameters waiting4dcLevel={0,samplingRate*20,0};

static delay_parameters cbWait={0,samplingRate*5,0};
static delay_parameters cbClose={1,samplingRate*0.2,0};

static delay_parameters cbCheckPosition={1,samplingRate*1,0};

static delay_parameters timeout={0,samplingRate*30,0};


stateID charged_state(void){

fToggle(1,&chargedToggle);
	
// board indicators
LED.out._2=chargedToggle.output;
LED.out._3=0;
	
//panel indicators
panelOutput.ch.statcomTrip=0;		
panelOutput.ch.statcomReady=chargedToggle.output ;			
panelOutput.ch.statcomRunning=0;

//timeout for charged state
on_delay(1,&timeout);
if(timeout.output){
stateFault.bit.charged_timeOut=1;
}

//check bus energisation
if(flag.ch.bus1energised==0 && flag.ch.bus2energised==0){stateFault.bit.charged_noVoltageDetected=1;}

//dc level check
on_delay(1,&waiting4dcLevel);

if(waiting4dcLevel.output==0){
	
//handle precharge contactors
if(flag.ch.bus1energised==1 && panelOutput.ch.closePrechargeCB2==0 && panelInput.ch.prechargeCB2NO==0){panelOutput.ch.closePrechargeCB1=1;}
if(flag.ch.bus1energised==0 && flag.ch.bus2energised==1 && panelOutput.ch.closePrechargeCB1==0 && panelInput.ch.prechargeCB1NO==0){panelOutput.ch.closePrechargeCB2=1;}	

}
	
//check for simulataneous contactor
if(panelOutput.ch.closePrechargeCB1==1 && panelOutput.ch.closePrechargeCB2==1) {

panelOutput.ch.closePrechargeCB1=0;
panelOutput.ch.closePrechargeCB2=0;	
stateFault.bit.charged_simulataneousContactors=1;

}


if(waiting4dcLevel.output==1){
	
	//cau if(tRMS[rms_Vdc].out>tRMS[rms_Vab].out*1.1f){
	if(1){
	//open contactors 
	panelOutput.ch.closePrechargeCB1=0;			
	panelOutput.ch.closePrechargeCB2=0;	

	//cau wait for settling of positions 
	on_delay(1,&cbWait);

	//cau checking for contactor positions might be better

	if(panelInput.ch.prechargeCB1NO==0 && panelInput.ch.prechargeCB2NO==0){
	
			if(cbWait.output==1){

				off_delay(0,&cbClose);
				
				if(flag.ch.bus1energised==1 && panelInput.ch.cb2No==0 && panelInput.ch.cb1Trip==0){
				
						panelOutput.ch.closeCB1=cbClose.output;
						flag.ch.closeCBsent=1;
			
				}else{
					
						stateFault.bit.charged_closingCB1conditions=1;
				
				}
				
				
				if(flag.ch.bus1energised==0 && flag.ch.bus2energised==1 && panelInput.ch.cb1No==0  && panelInput.ch.cb2Trip==0){
				
						panelOutput.ch.closeCB2=cbClose.output;
						flag.ch.closeCBsent=1;
						
			
				}else{
					
						stateFault.bit.charged_closingCB2conditions=1;
				
				}
				
				//check for simulataneous CB
				if(panelOutput.ch.closeCB1==1 && panelOutput.ch.closeCB2==1){
				
				panelOutput.ch.closeCB1=0;
				panelOutput.ch.closeCB2=0;
				stateFault.bit.charged_simulataneousCBs=1;
					
				}
				
				
				if(panelInput.ch.cb1No || panelInput.ch.cb2No){
					
				panelOutput.ch.closeCB1=0;	
				panelOutput.ch.closeCB2=0;	
		
				currentState=idle;
			
				}
			}
		}
	}else{
		
	stateFault.bit.charged_chargeLevel=1;

}
}


on_delay(flag.ch.closeCBsent,&cbCheckPosition); //cau reset cbclosesent flag
	
if(cbCheckPosition.output==1 && (panelInput.ch.cb1No==0 && panelInput.ch.cb2No==0)){
		
		stateFault.bit.charged_cbClosing=1;
		
}
	

if(faultWord.all || stateFault.all){currentState=fault;}

if(currentState!=charged){
	
	
timeout.output=0;
timeout.count=0;	
	
waiting4dcLevel.output=0;
waiting4dcLevel.count=0;
	
cbWait.output=0;
cbWait.count=0;

cbClose.output=1; // for pulsing it's initialized as 1
cbClose.count=0;

cbCheckPosition.output=0;	
cbCheckPosition.count=0;	
	
panelOutput.ch.closePrechargeCB1=0;
panelOutput.ch.closePrechargeCB2=0;		
	
flag.ch.closeCBsent=0;	
	
previousState=charged;

	
}


return currentState;

}

