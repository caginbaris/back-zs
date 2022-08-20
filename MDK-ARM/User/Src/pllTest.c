

#include "pllHandling.h"
#include "main.h"




void pllTest(void){

	
	if(pll.theta >0 && pll.theta<_pi){
	
		HAL_GPIO_WritePin(testOutput_GPIO_Port,testOutput_Pin,1);
	
	}else{
	
		HAL_GPIO_WritePin(testOutput_GPIO_Port,testOutput_Pin,0);
		
	}
	
	
	//HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);


}
