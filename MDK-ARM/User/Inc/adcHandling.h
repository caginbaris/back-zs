#ifndef __adcHandling_H
#define __adcHandling_H

#include <stdint.h>

typedef enum adcSeq_Type {  seq_Van=0,
                            seq_Vbn=1,
                            seq_Vcn=2,  
                            
                            seq_Ia=3,  
                            seq_Ib=4,
                            seq_Ic=5,
	
														seq_Vdc=7,
														seq_Temp=6,
                     
}adcSeq_Type;




typedef union adcData_Type{

	struct{
		
		float Van;
		float Vbn;
		float Vcn;
		
		float Ia;
		float Ib;
		float Ic;
		
		float Vdc;
		float Temp;

	}ch;
	
	
	float all[8];

}adcData_Type;


extern adcData_Type adc;

#endif


void initAdc(void);


extern uint8_t adc_completed;