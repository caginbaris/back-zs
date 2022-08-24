#include "adcHandling.h"
#include <stdint.h>


typedef struct channelOffsets{

float Van;
float Vbn;
float Vcn;

float Ia;
float Ib;
float Ic;	
	
float Vdc;
float temp;	
	

}channelOffsets;


channelOffsets value;
channelOffsets sum;
extern uint32_t adcReading[9];

void channelOffsetCalculation(void){
	
static uint32_t counter=0;	

sum.Van+=adcReading[seq_Van];
sum.Vbn+=adcReading[seq_Vbn];
sum.Vcn+=adcReading[seq_Vcn];
	
sum.Ia+=adcReading[seq_Ic];
sum.Ib+=adcReading[seq_Ib];
sum.Ic+=adcReading[seq_Ia];

sum.Vdc+=adcReading[seq_Vdc];
	
	
counter++;

if(counter==10000){

value.Van=sum.Van*0.0001f;
value.Vbn=sum.Vbn*0.0001f;
value.Vcn=sum.Vcn*0.0001f;
	
value.Ia=sum.Ia*0.0001f;
value.Ib=sum.Ib*0.0001f;
value.Ic=sum.Ic*0.0001f;	

value.Vdc=sum.Vdc*0.0001f;

sum.Van=0;
sum.Vbn=0;
sum.Vcn=0;
	
sum.Ia=0;
sum.Ib=0;
sum.Ic=0;
sum.Vdc=0;

counter=0;	

}	
	
	
}