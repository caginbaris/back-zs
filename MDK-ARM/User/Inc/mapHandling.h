#ifndef __mapHandling_H
#define __mapHandling_H

#include <stdint.h>

typedef union mapWord{
	
	struct{
	
		uint32_t _1:1;
		uint32_t _2:1;
		uint32_t _3:1;
		uint32_t _4:1;
		uint32_t _5:1;
		uint32_t _6:1;
		uint32_t _7:1;
		uint32_t _8:1;
		uint32_t _9:1;
		uint32_t _10:1;
		uint32_t _11:1;
		uint32_t _12:1;
		uint32_t _13:1;
		uint32_t _14:1;
		uint32_t _15:1;
		uint32_t _16:1;


	}ch;
	
	uint16_t all;
	
}mapWord; 


typedef union mapWordFloat{
	
	struct{
		
		int16_t Qtotal;
	
		uint16_t Vpp;

		uint16_t Iline;

		uint16_t Vdc;
		
		uint16_t Vdcr;
		
		uint16_t temp;


	}ch;
	
	uint16_t all;
	
}mapWordFloat; 

void mapDataTransfer(void);
void incomingDataParsing(void);


extern mapWord konumlar,komutlar,hfKomutlar;
extern mapWordFloat analogData;
extern mapWord stateInfo;
extern mapWord flagInfo;

extern float Qstatcom;

extern int16_t QrefRemoteIncStatcom;
extern float QrefRemoteStatcom;

extern int16_t QrefLocalIncStatcom;
extern float QrefLocalStatcom;

extern float Qhf;
extern float Ihf;

void prepData4TX(uint16_t data,uint16_t* rtu_modbusRegAdress,uint16_t address,unsigned char* rtu_txBuffer ,uint16_t* rtu_txBufferIndex,uint16_t endingAdress);

#endif
