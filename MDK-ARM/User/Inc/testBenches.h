#ifndef __testBenches_H__
#define __testBenches_H__

void switchingTest(void);
void pllTest(void);
void channelOffsetCalculation(void);
void dqTransformSignalling(void);


extern float pllDiff;

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

extern channelOffsets value,valueF;
#endif
