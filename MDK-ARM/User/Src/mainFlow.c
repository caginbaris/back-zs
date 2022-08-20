#include "LEDs.h"
#include "ios.h"
#include "states.h"
#include "faultHandling.h"
#include "pllHandling.h"
#include "references.h"
#include "measurements.h"
#include "protections.h"
#include "ios.h"
#include "controlRoutines.h"
#include "flagHandling.h"
#include "testBenches.h"
#include "tim.h"

uint32_t mainFlowCounter=0,secCounter=0;
delay_parameters mainFlowSecondCounter={0,samplingFrequency,0};

int32_t cycleCount;
float cpuLoading;

void mainFlow(void){
	
		cycleCount=htim2.Instance->CNT; // get count of tim2

		measurements();
		//protection();
		pllHandling();
		//pllTest();
		ios();
		state_chart();
		flagHandling();
		//faultHandling();
		//references();
		//controlRoutines();
	
		if(++mainFlowCounter==samplingFrequency){secCounter++;mainFlowCounter=0;}

		cycleCount=htim2.Instance->CNT-cycleCount;
		cpuLoading=100.0*(float)(cycleCount)*0.000119061793070604; //reverse of tim2 period 

}
