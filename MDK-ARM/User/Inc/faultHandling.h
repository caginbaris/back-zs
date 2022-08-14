#ifndef __faultHandling_H__
#define __faultHandling_H__

#include <stdint.h>

typedef union faultInputs{
	
	struct{
	
		
		uint32_t oc_rms_L1:1;
		uint32_t oc_rms_L2:1; 
		uint32_t oc_rms_L3:1;

		uint32_t oc_cs_L1:1;
		uint32_t oc_cs_L2:1; 
		uint32_t oc_cs_L3:1;
		
		uint32_t oc_peak_L1:1;
		uint32_t oc_peak_L2:1; 
		uint32_t oc_peak_L3:1;
		
		uint32_t meanIa:1;
		uint32_t meanIb:1; 
		uint32_t meanIc:1;
		
		uint32_t analogWatchDogFired:1;
		
		uint32_t ov_dc:1;
		uint32_t ov_ac:1; 

		uint32_t uv_dc:1;
		uint32_t uv_ac:1; 
		
		uint32_t ipmTemperature:1;
		
		uint32_t dcRippleOverLimit:1;
		
		uint32_t phaseSequence:1;
		uint32_t voltageUnbalance:1;
		uint32_t currentUnbalance:1;
		uint32_t voltageZeroSequence:1;
		uint32_t currentZeroSequence:1;
		
		uint32_t charged_state_error:1;
		uint32_t idle_state_error:1;
		uint32_t run_state_error:1;
		
		uint32_t overCurrentProtectionInit:1;
		uint32_t voltageProtectionInit:1;

		uint32_t synchronization:1;
		uint32_t gridFrequency:1;


			

	}bit;
	
	uint32_t all;
	
}faultInputs; 

extern faultInputs faultWord;

void faultHandling(void);


#endif
