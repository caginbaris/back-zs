#include "main.h"
#include "haltSignal.h"

/*

from power stack if 0 taken mcu get high (fault state indicated with mcu high)
from mcu if high is sent to halt-do input pin also get high (stopped by mcu)

*/

haltSignalHandling halt={0};

void haltSignal(void){

halt.ch.input=HAL_GPIO_ReadPin(IPM_HALT_DI_GPIO_Port,IPM_HALT_DI_Pin);
	
HAL_GPIO_WritePin(IPM_HALT_DO_GPIO_Port,IPM_HALT_DO_Pin,halt.ch.output);
	
}