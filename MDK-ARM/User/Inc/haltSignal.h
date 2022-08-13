#ifndef __haltSignal_H
#define __haltSignal_H

#include <stdint.h>

typedef union haltSignalHandling{
	
	struct{
	

		uint32_t input:1;
		uint32_t output:1;


	}ch;
	
	uint32_t all;
	
}haltSignalHandling; 





extern haltSignalHandling halt;

#endif
