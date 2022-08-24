#include "faultHandling.h"
#include "adcHandling.h"
#include "ios.h"
#include "protections.h"
#include "flagHandling.h"

faultInputs faultWord={0};
stateFaults stateFault={0};


void faultHandling(void){
	
	
	if(flag.ch.reset==1){
	
	faultWord.all=0;
	stateFault.all=0;

	//cau break latched faults
	
	}
	
	faultWord.bit.oc_rms_L1=overCurrentRMS_L1.trip_latch;
	faultWord.bit.oc_rms_L2=overCurrentRMS_L2.trip_latch;
	faultWord.bit.oc_rms_L3=overCurrentRMS_L3.trip_latch;

	faultWord.bit.oc_cs_L1=overCurrentCS_L1.trip_latch;
	faultWord.bit.oc_cs_L2=overCurrentCS_L2.trip_latch;
	faultWord.bit.oc_cs_L3=overCurrentCS_L3.trip_latch;
		
	faultWord.bit.oc_peak_L1=overCurrentPeak_L1.trip_latch;
	faultWord.bit.oc_peak_L2=overCurrentPeak_L2.trip_latch;
	faultWord.bit.oc_peak_L3=overCurrentPeak_L3.trip_latch;
	
	//mean faults processed into related funcs +3
	//analog watchdog processed in adchandling -- //cau not yet
	
	faultWord.bit.ov_dc=overVoltageDC.trip_latch;
	faultWord.bit.ov_ac=overVoltageAC.trip_latch;
	
	faultWord.bit.uv_dc=underVoltageDC.trip_latch;
	faultWord.bit.uv_ac=underVoltageAC.trip_latch;
	
	//temperature processed in adchandling -- 
	//dc ripple processed in misc --
	//voltage unb. in misc
	//current unb. in misc
	//voltage zeo. in misc
	//current zeo. in misc
	
	//init errors are in same source files +2
		
	//sync in pll
	//grid freq in freq. measurement
	// halt signal in it's source file
	
	//cau faultWord.bit.inverterFanSupplyFault=panelInput.ch.inverterFanSupplyFault;
	faultWord.bit.reactorThermoFault=panelInput.ch.reactorThermoFault;
	faultWord.bit.semiconductorFault=panelInput.ch.semiconductorFault;
		
	faultWord.bit.cb1Trip=panelInput.ch.cb1Trip && panelInput.ch.cb1No; 
	faultWord.bit.cb2Trip=panelInput.ch.cb2Trip && panelInput.ch.cb2No; 
		
	faultWord.bit.panelSupplyFault=panelInput.ch.panelSupplyFault;
	faultWord.bit.panelUpsFault=panelInput.ch.panelUpsFault;
}
