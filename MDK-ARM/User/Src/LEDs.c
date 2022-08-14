#include "main.h"
#include "ios.h"
#include "LEDs.h"

LEDoutputs LED={0};


void LEDs(void){
	

HAL_GPIO_WritePin(LD1_GPIO_Port,LD1_Pin,(GPIO_PinState)LED.out._1);

HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,(GPIO_PinState)LED.out._2);

HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,(GPIO_PinState)LED.out._3);
	

}


