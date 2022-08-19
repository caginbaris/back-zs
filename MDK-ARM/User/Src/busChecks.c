#include "main.h"
#include "plib.h"
#include "ios.h"
#include "flagHandling.h"
#include "states.h"

static transition_parameters bus1t={0,0};
static transition_parameters bus2t={0,0};

static delay_parameters bus1d={0,samplingRate*0.022,0}; 	// if 22msec off period is detected bus is not energised
static delay_parameters bus2d={0,samplingRate*0.022,0};	// if 22msec off period is detected bus is not energised

void busChecks(void){
	

high2lowTransition((HAL_GPIO_ReadPin(Bus1_check_GPIO_Port,Bus1_check_Pin)),&bus1t);
high2lowTransition((HAL_GPIO_ReadPin(Bus1_check_GPIO_Port,Bus1_check_Pin)),&bus2t);	

off_delay(bus1t.output,&bus1d);
off_delay(bus2t.output,&bus1d);		

flag.ch.bus1energised =bus1d.output;
flag.ch.bus2energised =bus2d.output;
	
	
flag.ch.bus1energised =1;
flag.ch.bus2energised =0;	


}

