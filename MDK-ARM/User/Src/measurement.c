#include "measurements.h"

uint16_t calculationCounter=0;

void measurements(void){

if(++calculationCounter==200){calculationCounter=0;}	

frequencyMeasurement();
rmsMeasurement();
csMeasurement();
dcMeasurement();

}

