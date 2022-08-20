
#include "adcHandling.h"
#include "mlib.h" 

float dcRipple=0, dcAverage=0, Vdcf=0;

static sos_parameters sos_pDC={0};
static float Vdcz=0;
static float Vdcrz=0;
 
//cau correct filters
//1e2 filter
float fofCoefficents1e2[2]={

0.030468747091254f,
-0.939062505817492f

};

float fofCoefficents1e0[2]={

0.000314060610640432f,
-0.999371878778719f

};



void dcMeasurement(void){
	
	
FOF(adc.ch.Vdc,Vdcz,Vdcf,fofCoefficents1e2);
FOF(adc.ch.Vdc,Vdcrz,dcAverage,fofCoefficents1e0); 	
dcRipple=adc.ch.Vdc-dcAverage; 



}
