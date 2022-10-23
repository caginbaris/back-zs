#include "adcHandling.h"
#include <stdint.h>
#include "testBenches.h"
#include "measurements.h"



channelOffsets value;
channelOffsets value_z={0};
channelOffsets valueF;
channelOffsets sum;
extern uint32_t adcReading[9];

static float fofCoefficents1e1[2]={

0.003131764229193,
-0.993736471541615
};

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

FOF(value.Van,value_z.Van,valueF.Van,fofCoefficents1e1);
FOF(value.Vbn,value_z.Vbn,valueF.Vbn,fofCoefficents1e1);
FOF(value.Vcn,value_z.Vcn,valueF.Vcn,fofCoefficents1e1);

FOF(value.Ia,value_z.Ia,valueF.Ia,fofCoefficents1e1);
FOF(value.Ib,value_z.Ib,valueF.Ib,fofCoefficents1e1);
FOF(value.Ic,value_z.Ic,valueF.Ic,fofCoefficents1e1);
	
}