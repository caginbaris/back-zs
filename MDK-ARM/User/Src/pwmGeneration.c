#include "main.h"
#include "tim.h"
#include "pwmGeneration.h"
#include "plib.h"
#include "controlRoutines.h"
#include "references.h"
#include "adcHandling.h"
#include "measurements.h"


uint16_t sw_count_a=wscale*0.5;
uint16_t sw_count_b=wscale*0.5;
uint16_t sw_count_c=wscale*0.5;



void modulatorDisable(void){

	
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
	
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);


		
}


void modulatorEnable(void){

	
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
	HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
	

}


void modulator(void){
	
	float inv_Vdc;
	
	if(Vdcf>1.0f){
		
	inv_Vdc=1/Vdcf;	
		
	sw_count_a=wscale*(final.a+Vdcf*0.5f)*inv_Vdc;
	sw_count_b=wscale*(final.b+Vdcf*0.5f)*inv_Vdc;
	sw_count_c=wscale*(final.c+Vdcf*0.5f)*inv_Vdc;
	

	}
	

	
	ui_LIMITER(sw_count_a,0,wscale);
	ui_LIMITER(sw_count_b,0,wscale);
	ui_LIMITER(sw_count_c,0,wscale);
	
	
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1, sw_count_a);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2, sw_count_b);
	__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3, sw_count_c);	
	
	
}


