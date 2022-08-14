

#include "pllHandling.h"
#include "main.h"
#include "LEDs.h"

#define _pi 3.14159f

void pllTest(void){

	
	if(pll.theta_comp >0 && pll.theta_comp<_pi){
	
		LED.out._3=1;
	
	}else{
	
		LED.out._3=0;
		
	}
	
	
	//HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);


}