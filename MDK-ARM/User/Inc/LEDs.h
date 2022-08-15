#ifndef __LEDs_H__
#define __LEDs_H__

#include <stdint.h>


typedef union LEDoutputs{
	
	struct{
	

		uint8_t _1:1;
		uint8_t _2:1;
		uint8_t _3:1;	
		uint32_t rem:5;

	}out;
	
	uint8_t all;
	
}LEDoutputs; 

extern LEDoutputs LED;
void LEDs(void);



#endif





