#ifndef __ios_H
#define __ios_H

#include <stdint.h>


//mcu inputs
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


//mcu inputs
typedef union panelInputs{
	
	struct{
	

		uint32_t inverterFanSupplyFault:1; // low when faulty
		uint32_t start:1;
		uint32_t stop:1;	
		uint32_t reset:1;	
		
		uint32_t reactorThermoFault:1; //low when fault
		uint32_t semiconductorFault:1; //low when fault
		
		uint32_t cb1Trip:1;
		uint32_t cb2Trip:1;
		uint32_t cb1No:1;
		uint32_t cb2No:1;
		
		uint32_t prechargeCB1NO:1;
		uint32_t prechargeCB2NO:1;
		uint32_t panelSupplyFault:1;	
		uint32_t panelUpsFault:1;	
		uint32_t _15:1;
		uint32_t _16:1;
		uint32_t _17:1;
		uint32_t _18:1;
		uint32_t _19:1;
		
		uint32_t _20:1;

	}ch;
	
	uint32_t all;
	
}panelInputs; 

//mcu outputs
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

//panel outputs

typedef union panelOutputs{
	
	struct{
	

		uint32_t closePrechargeCB1:1;
		uint32_t closeCB1:1;
		uint32_t closeCB2:1;	
		uint32_t statcomRunning:1;	
		uint32_t statcomTrip:1;
		uint32_t openCB1:1;
		uint32_t openCB2:1;
		uint32_t statcomReady:1;
		uint32_t closePrechargeCB2:1;
		uint32_t spare:1;
		
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
	
}panelOutputs; 


extern digitalOutputs output;
extern digitalInputs input;
extern panelInputs panelInput;
extern panelOutputs panelOutput;
#endif
