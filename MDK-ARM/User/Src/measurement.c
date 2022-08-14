#include "measurements.h"

uint16_t calculationCounter=0;

void measureemnts(void){

if(++calculationCounter==10000){calculationCounter=0;}	

rmsMeasurement();
csMeasurement();

}

