#include "mapHandling.h"
#include "ios.h"
#include "measurements.h"

mapWord konumlar={0};
mapWord komutlar={0};
mapWord hfKomutlar={0};

mapWordFloat analogData={0};

int16_t QrefIncStatcom;
float QrefStatcom;

void mapDataTransfer(void){

//1000
konumlar.ch._1=panelInput.ch.cb1No;
konumlar.ch._2=panelInput.ch.cb2No;
konumlar.ch._3=0; // TBD
konumlar.ch._4=0; // TBD
konumlar.ch._5=panelInput.ch.prechargeCB1NO; 
konumlar.ch._6=panelInput.ch.prechargeCB2NO; 

//analog

analogData.ch.Qtotal=Qstatcom;
	
analogData.ch.Van=tRMS[rms_Van].out;
analogData.ch.Van=tRMS[rms_Vbn].out;	
analogData.ch.Van=tRMS[rms_Vcn].out;	

analogData.ch.Vpos=tRMS[rms_V1].out;
analogData.ch.Vneg=tRMS[rms_V2].out;


analogData.ch.Van=tRMS[rms_Ia].out;
analogData.ch.Van=tRMS[rms_Ib].out;	
analogData.ch.Van=tRMS[rms_Ic].out;	

analogData.ch.Vpos=tRMS[rms_I1].out;
analogData.ch.Vneg=tRMS[rms_I2].out;	

analogData.ch.Vdc=tRMS[rms_Vdc].out;
analogData.ch.Vdcr=tRMS[rms_dcr].out;

analogData.ch.Vdc=tRMS[rms_temp].out;


}

