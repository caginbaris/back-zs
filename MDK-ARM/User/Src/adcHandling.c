#include "main.h"
#include "tim.h"
#include "adc.h"
#include "adcHandling.h"
#include "testBenches.h"

#define scale4IPM (30.0f/6.8f)*(3.3f/4095.0f)
#define scale4Vdc (100.0f) //10mV/V
#define scale4Current (1000.0f/24) // 24mV/A
#define scale4VAC (1320.0f/6.2f)*(3.3f/4095.0f)
#define scale4Temp (10.0f)

void mainFlow(void);

uint32_t adcReading[9];
adcData_Type adc={0};

uint8_t adc_completed=0;


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
	
/*
adc.ch.Van=-(adcReading[seq_Van]-valueF.Van)*scale4VAC;
adc.ch.Vbn=-(adcReading[seq_Vbn]-valueF.Vbn)*scale4VAC;
adc.ch.Vcn=-(adcReading[seq_Vcn]-valueF.Vcn)*scale4VAC;
	
adc.ch.Ic=(adcReading[seq_Ia]-valueF.Ic)*scale4IPM*scale4Current;//hb3 connected to hb1 on PCB
adc.ch.Ib=(adcReading[seq_Ib]-valueF.Ib)*scale4IPM*scale4Current;
adc.ch.Ia=-(adcReading[seq_Ic]-valueF.Ia)*scale4IPM*scale4Current;//hb1 connected to hb3 on PCB	and reverted
*/

adc.ch.Van=-(adcReading[seq_Van]-2046.4364f)*scale4VAC;
adc.ch.Vbn=-(adcReading[seq_Vbn]-2047.66077f)*scale4VAC;
adc.ch.Vcn=-(adcReading[seq_Vcn]-2046.19116f)*scale4VAC;
	
adc.ch.Ic=(adcReading[seq_Ia]-2042.04358f)*scale4IPM*scale4Current;//hb3 connected to hb1 on PCB
adc.ch.Ib=(adcReading[seq_Ib]-2058.06201f)*scale4IPM*scale4Current;
adc.ch.Ia=-(adcReading[seq_Ic]-2067.51025f)*scale4IPM*scale4Current;//hb1 connected to hb3 on PCB	and reverted
	
	
adc.ch.Vdc=adcReading[seq_Vdc]*scale4IPM*scale4Vdc; // 10mv/v	
adc.ch.Temp=adcReading[seq_Temp]*scale4IPM*scale4Temp;
	
	
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	
	adc_completed=0;
	
	read_ADC();
	mainFlow();
	
	adc_completed=1;
	
}
