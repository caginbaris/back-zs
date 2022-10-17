#include "mapHandling.h"
#include "ios.h"
#include "measurements.h"
#include "states.h"
#include "flagHandling.h"

mapWord konumlar={0};
mapWord komutlar={0};
mapWord hfKomutlar={0};
mapWord stateInfo={0};
mapWord flagInfo={0};

mapWordFloat analogData={0};

int16_t QrefRemoteIncStatcom;
float QrefRemoteStatcom;

int16_t QrefLocalIncStatcom;
float QrefLocalStatcom;

void mapDataTransfer(void){

//1000
konumlar.ch._1=panelInput.ch.cb1No;
konumlar.ch._2=panelInput.ch.cb2No;
konumlar.ch._3=0; //cau TBD
konumlar.ch._4=0; //cau TBD
konumlar.ch._5=panelInput.ch.prechargeCB1NO; 
konumlar.ch._6=panelInput.ch.prechargeCB2NO; 

//analog

analogData.ch.Qtotal=Qstatcom*0.001f;
	
analogData.ch.Van=tRMS[rms_Van].out;
analogData.ch.Vbn=tRMS[rms_Vbn].out;	
analogData.ch.Vcn=tRMS[rms_Vcn].out;	

analogData.ch.Vpos=tRMS[rms_V1].out;
analogData.ch.Vneg=tRMS[rms_V2].out*100.0f;


analogData.ch.Ia=tRMS[rms_Ia].out;
analogData.ch.Ib=tRMS[rms_Ib].out;	
analogData.ch.Ic=tRMS[rms_Ic].out;	

analogData.ch.Ipos=tRMS[rms_I1].out;
analogData.ch.Ineg=tRMS[rms_I2].out*100.0f;	

analogData.ch.Vdc=tRMS[rms_Vdc].out;
analogData.ch.Vdcr=tRMS[rms_dcr].out*100.0f;

analogData.ch.temp=tRMS[rms_temp].out;

// states
stateInfo.ch._1=currentState==startup?1:0;
stateInfo.ch._2=currentState==ready?1:0;
stateInfo.ch._3=currentState==charged?1:0;
stateInfo.ch._4=currentState==idle?1:0;
stateInfo.ch._5=currentState==run?1:0;
stateInfo.ch._6=currentState==stopped?1:0;
stateInfo.ch._7=currentState==fault?1:0;

//flags
flagInfo.ch._1=flag.ch.bus1energised;
flagInfo.ch._2=flag.ch.bus2energised;
flagInfo.ch._3=flag.ch.switchingStarted;
flagInfo.ch._4=1;//cau TBD
flagInfo.ch._5=1;//cau TBD
flagInfo.ch._6=1;//cau TBD
flagInfo.ch._7=1;//cau TBD
}

void incomingDataParsing(void){

	flag.ch.start=komutlar.ch._1;
	flag.ch.stop=komutlar.ch._2;
	flag.ch.reset=komutlar.ch._3;
	//rest of flags handled in corresponding source files (referenceGeneration,run etc)
	
	if(currentState!=run){
	
	flag.ch.local= komutlar.ch._4;	
	flag.ch.remote= komutlar.ch._5;	
	flag.ch.coldRun= komutlar.ch._6;
		
	}
	
	QrefRemoteStatcom=(float)QrefRemoteIncStatcom*1000.0f;
	QrefLocalStatcom=(float)QrefLocalIncStatcom*1000.0f;

}