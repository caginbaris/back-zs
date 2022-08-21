#ifndef __faultHandling_H__
#define __faultHandling_H__

#include <stdint.h>

typedef union faultInputs{
	
	struct{
	
		
		uint64_t oc_rms_L1:1;
		uint64_t oc_rms_L2:1; 
		uint64_t oc_rms_L3:1;

		uint64_t oc_cs_L1:1;
		uint64_t oc_cs_L2:1; 
		uint64_t oc_cs_L3:1;
		
		uint64_t oc_peak_L1:1;
		uint64_t oc_peak_L2:1; 
		uint64_t oc_peak_L3:1;
		
		uint64_t meanIa:1;
		uint64_t meanIb:1; 
		uint64_t meanIc:1;
		
		uint64_t analogWatchDogFired:1;
		
		uint64_t ov_dc:1;
		uint64_t ov_ac:1; 

		uint64_t uv_dc:1;
		uint64_t uv_ac:1; 
		
		uint64_t ipmTemperature:1;
		
		uint64_t dcRippleOverLimit:1;
		
		uint64_t phaseSequence:1;
		uint64_t voltageUnbalance:1;
		uint64_t currentUnbalance:1;
		uint64_t voltageZeroSequence:1;
		uint64_t currentZeroSequence:1;
		
		uint64_t overCurrentProtectionInit:1;
		uint64_t voltageProtectionInit:1;

		uint64_t synchronization:1;
		uint64_t gridFrequency:1;

		uint64_t haltSignal:1; //29
		
		uint64_t inverterFanSupplyFault:1;
		uint64_t reactorThermoFault:1;
		uint64_t semiconductorFault:1;
		uint64_t cb1Trip:1;
		uint64_t cb2Trip:1;
		uint64_t panelSupplyFault:1;
		uint64_t panelUpsFault:1;
		
		
	}bit;
	
	uint64_t all;
	
}faultInputs; 


typedef union stateFaults{

	struct {
		
		uint32_t charged_timeOut:1;
		uint32_t charged_chargeLevel:1;
		uint32_t charged_simulataneousContactors:1;
		uint32_t charged_cbClosing:1;
		uint32_t charged_noVoltageDetected:1;
		uint32_t charged_simulataneousCBs:1;

		uint32_t idle_timeOut:1;
		uint32_t idle_state_error:1;
		
		uint32_t run_timeOut:1;
		uint32_t run_state_error:1;
	
	}bit;
	
	
	uint32_t all;

}stateFaults;


extern faultInputs faultWord;
extern stateFaults stateFault;

void faultHandling(void);


#endif
