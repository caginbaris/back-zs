#include "main.h"
#include "Modbus_Map.h"



extern float bin_array[6][20];
extern float snap[6][20];

union modbusMappingReadData readHoldingMap;

uint8_t dummyData=13;

void init_Map(void){
	
		uint8_t i;
	
		readHoldingMap.data.tRMS_Van=(unsigned char*)&(dummyData);
		readHoldingMap.data.tRMS_Vbn=(unsigned char*)&(dummyData);	
		readHoldingMap.data.tRMS_Vcn=(unsigned char*)&(dummyData);
	
		readHoldingMap.data.tRMS_Vab=(unsigned char*)&(dummyData);
		readHoldingMap.data.tRMS_Vbc=(unsigned char*)&(dummyData);	
		readHoldingMap.data.tRMS_Vca=(unsigned char*)&(dummyData);
	
		readHoldingMap.data.tRMS_Ia=(unsigned char*)&(dummyData);
		readHoldingMap.data.tRMS_Ib=(unsigned char*)&(dummyData);	
		readHoldingMap.data.tRMS_Ic=(unsigned char*)&(dummyData);
	
		readHoldingMap.data.Qa=(unsigned char*)&(dummyData);
		readHoldingMap.data.Qb=(unsigned char*)&(dummyData);	
		readHoldingMap.data.Qc=(unsigned char*)&(dummyData);
		
		readHoldingMap.data.Qtotal=(unsigned char*)&(dummyData);	
	
		//cau init for remaining data

}