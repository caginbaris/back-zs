#include "states.h"


stateID currentState=startup;
stateID previousState=startup;



stateID (*state[])(void)={

startup_state,
fault_state,
ready_state,
charged_state,
idle_state,
run_state,
stopped_state,


	
};


void init_state(void){
	
	
	currentState=startup;
	previousState=startup;


}



void state_chart(void){

stateID(* state_fun)(void);

state_fun=state[currentState];
state_fun();


}
