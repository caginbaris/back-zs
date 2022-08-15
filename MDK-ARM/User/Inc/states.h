#ifndef __states_h
#define __states_h

#include <stdint.h>

#define samplingRate 50000

typedef enum stateID{

startup=0,
fault,
ready,
charged,
idle,
run,
stopped,

	
	
}stateID;

extern stateID currentState;
extern stateID previousState;


stateID startup_state(void);
stateID fault_state(void);
stateID ready_state(void);
stateID charged_state(void);
stateID idle_state(void);
stateID run_state(void);
stateID stopped_state(void);



void state_chart(void);




#endif





