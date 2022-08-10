#include "main.h"
#include "tim.h"
#include "adc.h"
#include "adcHandling.h"

#define scale4IPM (30.0/6.8)*(3.3/4095.0)

uint32_t adcReading[9];

//calibration can be added


adcData_Type adc={0};


void init_ADC(void){
	
	
		  /*##-3- Enable Tim ########################################################*/
  if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }
	
	

  if(HAL_ADC_Start(&hadc3) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

  /*##-3- Enable ADC2 ########################################################*/
  if (HAL_ADC_Start(&hadc2) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }

	
	/* Start multimode conversion on regular group with transfer by DMA */
	
  if (HAL_ADCEx_MultiModeStart_DMA(&hadc1, (uint32_t *)adcReading, 9) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }	
	
	


}

void read_ADC(void){

adc.ch.Van=(adcReading[seq_Van]-2048.0);
adc.ch.Vbn=(adcReading[seq_Vbn]-2048.0);
adc.ch.Vcn=(adcReading[seq_Vcn]-2048.0);
	
adc.ch.Ia=(adcReading[seq_Ia]-2048.0)*scale4IPM;
adc.ch.Ib=(adcReading[seq_Ib]-2048.0)*scale4IPM;
adc.ch.Ic=(adcReading[seq_Ic]-2048.0)*scale4IPM;	

adc.ch.Vdc=adcReading[seq_Vdc]*scale4IPM;	
adc.ch.Temp=adcReading[seq_Temp]*scale4IPM;
	
	
	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	
	read_ADC();
	
}