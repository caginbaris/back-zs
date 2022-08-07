#ifndef __ios_H
#define __ios_H

#include <stdint.h>

typedef union digitalInputs{
	
	struct{
	

		uint32_t _1:1;
		uint32_t _2:1;
		uint32_t _3:1;	
		uint32_t _4:1;	
		uint32_t _5:1;
		uint32_t _6:1;
		uint32_t _7:1;
		uint32_t _8:1;
		uint32_t _9:1;
		uint32_t _10:1;
		
		uint32_t _11:1;
		uint32_t _12:1;
		uint32_t _13:1;	
		uint32_t _14:1;	
		uint32_t _15:1;
		uint32_t _16:1;
		uint32_t _17:1;
		uint32_t _18:1;
		uint32_t _19:1;
		
		uint32_t _20:1;

	}ch;
	
	uint32_t all;
	
}digitalInputs; 


typedef union digitalOutputs{
	
	struct{
	

		uint32_t _1:1;
		uint32_t _2:1;
		uint32_t _3:1;	
		uint32_t _4:1;	
		uint32_t _5:1;
		uint32_t _6:1;
		uint32_t _7:1;
		uint32_t _8:1;
		uint32_t _9:1;
		uint32_t _10:1;
		
		uint32_t _11:1;
		uint32_t _12:1;
		uint32_t _13:1;	
		uint32_t _14:1;	
		uint32_t _15:1;
		uint32_t _16:1;
		
		uint32_t _DOR1:1;
		uint32_t _DOR2:1;
		uint32_t _DOR3:1;
		uint32_t _DOR4:1;

	}ch;
	
	uint32_t all;
	
}digitalOutputs; 



extern digitalOutputs output;


#endif
