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


	}ch;
	
	uint32_t all;
	
}flags; 





extern flags flag;

#endif