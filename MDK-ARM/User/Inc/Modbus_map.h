#ifndef __Modbus_Map_H__
#define __Modbus_Map_H__



union modbusMappingReadData{
	
	
	struct {

	unsigned char* tRMS_Van;//1
	unsigned char* tRMS_Vbn;//2
	unsigned char* tRMS_Vcn;//3

	unsigned char* tRMS_Vab;//7
	unsigned char* tRMS_Vbc;//8
	unsigned char* tRMS_Vca;//9

	unsigned char* tRMS_Ia;//10
	unsigned char* tRMS_Ib;//11
	unsigned char* tRMS_Ic;//12
	
	unsigned char* Qa;//13
	unsigned char* Qb;//14		
	unsigned char* Qc;//15
		
	unsigned char* Qtotal;//16

	unsigned char* Vpn_1;//17
	unsigned char* Vpn_2;//18

	unsigned char* I_1;//19
	unsigned char* I_2;//20

	unsigned char* UNB_V;//21
	unsigned char* UNB_I;//22

	
	}data;
	
	unsigned char*   buffer[22];	

};


extern union modbusMappingReadData readHoldingMap;

void init_Map(void);

#endif
