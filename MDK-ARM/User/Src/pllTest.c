

#include "pllHandling.h"
#include "main.h"
#include "LEDs.h"



void pllTest(void){

	
	if(pll.theta >0 && pll.theta<_pi){
	
		LED.out._3=1;
	
	}else{
	
		LED.out._3=0;
		
	}
	
	
	//HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);


}
