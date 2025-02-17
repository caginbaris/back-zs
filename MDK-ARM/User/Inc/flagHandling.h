#ifndef __flagHandling_H
#define __flagHandling_H

#include <stdint.h>

typedef union flags{
	
	struct{
	
		uint32_t start:1;
		uint32_t stop:1;
		uint32_t fault:1;
		uint32_t reset:1;
		
		uint32_t bus1energised:1;
		uint32_t bus2energised:1;
		
		uint32_t closeCBsent:1;
		
		uint32_t switchingStarted:1;
		
		uint32_t local:1;
		uint32_t remote:1;
		uint32_t coldRun:1;
		uint32_t hfManualControl:1;

	}ch;
	
	uint32_t all;
	uint16_t halfWord[2];
	
}flags; 





extern flags flag;
void flagHandling(void);


#endif






