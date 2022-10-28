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
	
		uint16_t Van;
		uint16_t Vbn;
		uint16_t Vcn;
		
		uint16_t Vpos;
		uint16_t Vneg;
		
		uint16_t Ia;
		uint16_t Ib;
		uint16_t Ic;
		
		uint16_t Ipos;
		uint16_t Ineg;
		
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

extern float Ihf;
#endif
