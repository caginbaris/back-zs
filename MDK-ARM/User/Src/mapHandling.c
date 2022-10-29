#include "mapHandling.h"
#include "ios.h"
#include "measurements.h"
#include "states.h"
#include "flagHandling.h"
#include "references.h"
#include "tim.h"
#include <math.h>

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
int8_t noise=0;

void mapDataTransfer(void){
	
float Isim=0;

noise=(htim2.Instance->CNT)%3 -1;	
	
//1000
konumlar.ch._1=panelInput.ch.cb1No;
konumlar.ch._2=panelInput.ch.cb2No;
konumlar.ch._3=panelInput.ch.hf1; 
konumlar.ch._4=panelInput.ch.hf2; 
konumlar.ch._5=panelInput.ch.prechargeCB1NO; 
konumlar.ch._6=panelInput.ch.prechargeCB2NO; 

//analog
	
if(flag.ch.coldRun==0){
	
if(ref.I>-124.0f && ref.I<124.0f){
	
analogData.ch.Qtotal=-Qstatcom*0.001f + Qhf*0.001f;
	
if(ref.I>0){Ihf=-Ihf;}	
	
analogData.ch.Iline=fabsf(tRMS[rms_Ia].out+Ihf);
analogData.ch.Vdcr=tRMS[rms_dcr].out;	

}else{

if(currentState==run){	
	
analogData.ch.Qtotal=0.001f*ref.I*400.0f+noise;

Isim=ref.I/(1.732f);
	
if(Isim<0){Isim=-Isim;}

if(ref.I<0){Ihf=-Ihf;}
	
analogData.ch.Iline=fabsf(Isim+noise-Ihf);
analogData.ch.Vdcr=3.0f+tRMS[rms_dcr].out-noise;

}	

}	

}else{
	
if(currentState==run){
	
analogData.ch.Qtotal=0.001f*ref.I*400.0f+noise+ Qhf*0.001f;

Isim=ref.I/(1.732f);
	
if(Isim<0){Isim=-Isim;}	
if(ref.I<0){Ihf=-Ihf;}

analogData.ch.Iline=fabsf(Isim+noise-Ihf);
analogData.ch.Vdcr=3.0f+tRMS[rms_dcr].out-noise;

}else{

analogData.ch.Qtotal=0;	
analogData.ch.Iline=0;
analogData.ch.Vdcr=0;	
	
}

}

analogData.ch.Vpp=tRMS[rms_Vab].out;
analogData.ch.temp=tRMS[rms_temp].out;
analogData.ch.Vdc=tRMS[rms_Vdc].out;



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
flagInfo.ch._4=flag.ch.local;
flagInfo.ch._5=flag.ch.remote;
flagInfo.ch._6=flag.ch.coldRun;
flagInfo.ch._7=flag.ch.hfManualControl;
}

void incomingDataParsing(void){

	flag.ch.start=komutlar.ch._1;
	flag.ch.stop=komutlar.ch._2;
	flag.ch.reset=komutlar.ch._3;
	
	flag.ch.hfManualControl=hfKomutlar.ch._1;
	//rest of flags handled in corresponding source files (referenceGeneration,run etc)
	
	if(currentState!=run){
	
	flag.ch.local= komutlar.ch._4;	
	flag.ch.remote= komutlar.ch._5;	
	flag.ch.coldRun= komutlar.ch._6;
		
	}
	
	QrefRemoteStatcom=(float)QrefRemoteIncStatcom*1000.0f;
	QrefLocalStatcom=(float)QrefLocalIncStatcom*1000.0f;

}

void prepData4TX(uint16_t data,uint16_t* rtu_modbusRegAdress,uint16_t address,unsigned char* rtu_txBuffer ,uint16_t* rtu_txBufferIndex,uint16_t endingAdress){

	  if (*rtu_modbusRegAdress == address)
  {
      rtu_txBuffer[*(rtu_txBufferIndex)] = (0x0000FF00 & (int32_t)(data)) >> 8;
			*rtu_txBufferIndex=*rtu_txBufferIndex+1;
		
      rtu_txBuffer[*(rtu_txBufferIndex)] = (0x000000FF & (int32_t)(data));
			*rtu_txBufferIndex=*rtu_txBufferIndex+1;
		
      *rtu_modbusRegAdress += 1;
      if (*rtu_modbusRegAdress == endingAdress) *rtu_modbusRegAdress = 0;
  }
	

} 