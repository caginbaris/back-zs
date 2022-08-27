#include "plib.h"
#include "adcHandling.h"
#include "ios.h"
#include "measurements.h"
#include "states.h"
#include "faultHandling.h"
#include "flagHandling.h"


overLimit_inputParameters overVoltageDC_Config,overVoltageAC_Config;
overLimit_outputParameters overVoltageDC, overVoltageAC;

underLimit_inputParameters underVoltageDC_Config,underVoltageAC_Config;
underLimit_outputParameters underVoltageDC, underVoltageAC;



void voltageProtectionsInit(void){


overVoltageDC_Config.level=650;
overVoltageDC_Config.delay=0.01;
overVoltageDC_Config.dropout_ratio=0.99;
overVoltageDC_Config.dropout_time=0.001;
overVoltageDC_Config.comm_pick_on_delay=0.01;	
overVoltageDC_Config.comm_pick_off_delay=10;
overVoltageDC_Config.fs=samplingFrequency;

overLimitInitialization(overVoltageDC_Config,&overVoltageDC);

	
overVoltageAC_Config.level=245;
overVoltageAC_Config.delay=0.01;
overVoltageAC_Config.dropout_ratio=0.99;
overVoltageAC_Config.dropout_time=0.01;
overVoltageAC_Config.comm_pick_on_delay=0.01;	
overVoltageAC_Config.comm_pick_off_delay=10;
overVoltageAC_Config.fs=samplingFrequency;

overLimitInitialization(overVoltageAC_Config,&overVoltageAC);	


underVoltageDC_Config.level=400;
underVoltageDC_Config.delay=0.04;
underVoltageDC_Config.dropout_ratio=1.01;
underVoltageDC_Config.dropout_time=0.01;
underVoltageDC_Config.comm_pick_on_delay=0.01;	
underVoltageDC_Config.comm_pick_off_delay=10;
underVoltageDC_Config.fs=samplingFrequency;

underLimitInitialization(underVoltageDC_Config,&underVoltageDC);

	
underVoltageAC_Config.level=210;
underVoltageAC_Config.delay=0.04;
underVoltageAC_Config.dropout_ratio=1.01;
underVoltageAC_Config.dropout_time=0.01;
underVoltageAC_Config.comm_pick_on_delay=0.01;	
underVoltageAC_Config.comm_pick_off_delay=10;
underVoltageAC_Config.fs=samplingFrequency;

underLimitInitialization(underVoltageAC_Config,&underVoltageAC);


if(	overVoltageDC.initialized==0 ||
		overVoltageAC.initialized==0 ||
		underVoltageDC.initialized==0 ||
		underVoltageAC.initialized==0 ){
		
		
		faultWord.bit.voltageProtectionInit=1;
			
		
		}

	

}


void voltageProtections(void){
	
	uint8_t inhibitUV=0;

	inhibitUV=(currentState!=run);

	overLimit(adc.ch.Vdc,overVoltageDC_Config,&overVoltageDC,0,flag.ch.reset);
	overLimit(max3p(tRMS[rms_Van].out,tRMS[rms_Vbn].out,tRMS[rms_Vcn].out),overVoltageAC_Config,&overVoltageAC,0,flag.ch.reset);
	
	underLimit(adc.ch.Vdc,underVoltageDC_Config,&underVoltageDC,inhibitUV,flag.ch.reset); 
	underLimit(min3p(tRMS[rms_Van].out,tRMS[rms_Vbn].out,tRMS[rms_Vcn].out),underVoltageAC_Config,&underVoltageAC,inhibitUV,flag.ch.reset); 



}
