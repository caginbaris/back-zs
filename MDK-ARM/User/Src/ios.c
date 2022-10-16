#include "main.h"
#include "ios.h"

digitalInputs input={0};
digitalOutputs output={0};
panelInputs panelInput={0};
panelOutputs panelOutput={0};
/*notes-beg

DOR relay no contact is at the left side, mid is com
REL1 on board REL4 on Software 



notes-end*/

void ios(void){
	
	//inputs @ mcu
	input.ch._1=HAL_GPIO_ReadPin(DI1_GPIO_Port,DI1_Pin);
	input.ch._2=HAL_GPIO_ReadPin(DI2_GPIO_Port,DI2_Pin);
	input.ch._3=HAL_GPIO_ReadPin(DI3_GPIO_Port,DI3_Pin);
	input.ch._4=HAL_GPIO_ReadPin(DI4_GPIO_Port,DI4_Pin);
	input.ch._5=HAL_GPIO_ReadPin(DI5_GPIO_Port,DI5_Pin);
	input.ch._6=HAL_GPIO_ReadPin(DI6_GPIO_Port,DI6_Pin);
	input.ch._7=HAL_GPIO_ReadPin(DI7_GPIO_Port,DI7_Pin);
	input.ch._8=HAL_GPIO_ReadPin(DI8_GPIO_Port,DI8_Pin);
	input.ch._9=HAL_GPIO_ReadPin(DI9_GPIO_Port,DI9_Pin);
	
	input.ch._10=HAL_GPIO_ReadPin(DI10_GPIO_Port,DI10_Pin);
	input.ch._11=HAL_GPIO_ReadPin(DI11_GPIO_Port,DI11_Pin);
	input.ch._12=HAL_GPIO_ReadPin(DI12_GPIO_Port,DI12_Pin);
	input.ch._13=HAL_GPIO_ReadPin(DI13_GPIO_Port,DI13_Pin);
	input.ch._14=HAL_GPIO_ReadPin(DI14_GPIO_Port,DI14_Pin);
	input.ch._15=HAL_GPIO_ReadPin(DI15_GPIO_Port,DI15_Pin);
	input.ch._16=HAL_GPIO_ReadPin(DI16_GPIO_Port,DI16_Pin);
	input.ch._17=HAL_GPIO_ReadPin(DI17_GPIO_Port,DI17_Pin);
	input.ch._18=HAL_GPIO_ReadPin(DI18_GPIO_Port,DI18_Pin);
	input.ch._19=HAL_GPIO_ReadPin(DI19_GPIO_Port,DI19_Pin);
	input.ch._20=HAL_GPIO_ReadPin(DI20_GPIO_Port,DI20_Pin);
	
	
	
	//panel input assignment
	
	panelInput.ch.inverterFanSupplyFault=(input.ch._1==1)?(1):(0); //trig when panel=1
	panelInput.ch.start=(input.ch._2==1)?(0):(1); 
	panelInput.ch.stop=(input.ch._3==1)?(0):(1); 
	panelInput.ch.reset=(input.ch._4==1)?(0):(1); 
	
	panelInput.ch.reactorThermoFault=(input.ch._5==1)?(1):0;
	panelInput.ch.semiconductorFault=(input.ch._6==1)?(1):0;
	
	panelInput.ch.cb1Trip=(input.ch._7==0)?(1):0;
	panelInput.ch.cb2Trip=(input.ch._8==0)?(1):0;
	
	panelInput.ch.cb1No=(input.ch._9==0)?(1):0;
	panelInput.ch.cb2No=(input.ch._10==0)?(1):0;
	
	panelInput.ch.prechargeCB1NO=(input.ch._11==0)?(1):0;
	panelInput.ch.prechargeCB2NO=(input.ch._12==0)?(1):0;
	
	
	panelInput.ch.panelSupplyFault=(input.ch._14==1)?(1):0;
	panelInput.ch.panelUpsFault=(input.ch._15==1)?(0):1;
	
	panelInput.ch.hf1=(input.ch._16==0)?(1):(0);
	panelInput.ch.hf2=(input.ch._17==0)?(1):(0);
	panelInput.ch.hfTherm=(input.ch._18==0)?(0):(1);
	
	HAL_GPIO_WritePin(DO1_GPIO_Port,DO1_Pin,(GPIO_PinState)panelOutput.ch.closePrechargeCB1);
	HAL_GPIO_WritePin(DO2_GPIO_Port,DO2_Pin,(GPIO_PinState)panelOutput.ch.closeCB1);
	HAL_GPIO_WritePin(DO3_GPIO_Port,DO3_Pin,(GPIO_PinState)panelOutput.ch.closeCB2);
	HAL_GPIO_WritePin(DO4_GPIO_Port,DO4_Pin,(GPIO_PinState)panelOutput.ch.statcomRunning);
	HAL_GPIO_WritePin(DO5_GPIO_Port,DO5_Pin,(GPIO_PinState)panelOutput.ch.statcomTrip);
	HAL_GPIO_WritePin(DO6_GPIO_Port,DO6_Pin,(GPIO_PinState)panelOutput.ch.openCB1);
	HAL_GPIO_WritePin(DO7_GPIO_Port,DO7_Pin,(GPIO_PinState)panelOutput.ch.openCB2);
	HAL_GPIO_WritePin(DO8_GPIO_Port,DO8_Pin,(GPIO_PinState)panelOutput.ch.statcomReady);
	HAL_GPIO_WritePin(DO9_GPIO_Port,DO9_Pin,(GPIO_PinState)panelOutput.ch.closePrechargeCB2);
	HAL_GPIO_WritePin(DO10_GPIO_Port,DO10_Pin,(GPIO_PinState)panelOutput.ch.spare);
	
	HAL_GPIO_WritePin(DO11_GPIO_Port,DO11_Pin,(GPIO_PinState)panelOutput.ch.hf1);
	HAL_GPIO_WritePin(DO12_GPIO_Port,DO12_Pin,(GPIO_PinState)panelOutput.ch.hf2);
	HAL_GPIO_WritePin(DO13_GPIO_Port,DO13_Pin,(GPIO_PinState)output.ch._13);
	HAL_GPIO_WritePin(DO14_GPIO_Port,DO14_Pin,(GPIO_PinState)output.ch._14);
	HAL_GPIO_WritePin(DO15_GPIO_Port,DO15_Pin,(GPIO_PinState)output.ch._15);
	HAL_GPIO_WritePin(DO16_GPIO_Port,DO16_Pin,(GPIO_PinState)output.ch._16);
	
	HAL_GPIO_WritePin(DOR1_GPIO_Port,DOR1_Pin,(GPIO_PinState)output.ch._DOR1);
	HAL_GPIO_WritePin(DOR2_GPIO_Port,DOR2_Pin,(GPIO_PinState)output.ch._DOR2);
	HAL_GPIO_WritePin(DOR3_GPIO_Port,DOR3_Pin,(GPIO_PinState)output.ch._DOR3);
	HAL_GPIO_WritePin(DOR4_GPIO_Port,DOR4_Pin,(GPIO_PinState)output.ch._DOR4);
	


	
}

