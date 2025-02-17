/**
  ******************************************************************************
  * @file    Modbus_RTU_Slave.c
  * @author  Serbay Ozkan
  * @version V1.0.0
  * @date    15-November-2016
  * @brief   Modbus RTU Slave Application Layer File
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdio.h>
#include "Modbus_RTU_Slave.h"
#include "main.h"
#include "mapHandling.h"
#include "ios.h"
#include "faultHandling.h"
#include "flagHandling.h"


void rtu_transmitEnable_receiveDisable(void);
void rtu_transmitDisable_receiveEnable(void);

/* User Variables ------------------------------------------------------------*/
uint16_t rtu_modbusRxFrameLen;
extern uint16_t rtu_ModbusRxIndex;
uint16_t crcRecieved, crcCalculated;
extern unsigned char rtu_modbusRxBuffer[RX_BUFFER_LIMIT];
unsigned char rtu_modbusTxBuffer[TX_BUFFER_LIMIT];
int32_t rtu_modbusWriteBuffer[WRITE_MULTIPLE_BUFFER_LIMIT];
int32_t rtu_modbusSingleWriteBuffer[WRITE_SINGLE_BUFFER_LIMIT];
uint16_t rtu_modbusRegAdress, rtu_modbusDataLen, rtu_modbusTxLen;
uint16_t rtu_selectedSlaveID;
uint16_t rtu_txBufferIndex;
uint32_t rtu_modbusStartingAdress, rtu_modbusEndingAdress;
uint32_t rtu_deviceSlaveID[10];
uint8_t rtu_sendFlag;
uint8_t rtu_softwareReset = 0;
uint32_t RELAY_LATCH_TIMEOUT;
uint32_t  LATCH_TYPE;
uint8_t flashSaveAll = 0;
uint8_t rtuMasterSlaveID = 0;
uint8_t masterModeOp = 0;
extern uint32_t fckcnt;
extern uint8_t comErrorFlag;
extern uint16_t transmitComp;
extern HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
extern UART_HandleTypeDef huart4;
/* Typedefs ------------------------------------------------------------------*/
Typedef_rtuCRC rtuCRC;
Typedef_dummyTestData dummyTestData;

uint8_t dataSentFlag=0;
uint16_t dm1=1,dm2=3;
uint16_t recdm1=0,recdm2=0;


/**
  * @brief  This function performs Modbus CRC16 generation.  
  * @param  crcBuf:Input buffer that contains related registers to be calculated
  * @param  crcLength: CRC16 length
  * @retval None
  */

void rtu_crcCalculation(unsigned char *crcBuf, uint16_t crcLength)
{
   uint16_t crcTemp, crcRes;
   uint16_t i, j;
   crcRes = 0xFFFF;

    for (i = 0; i < crcLength; i++)
    {
      crcRes = crcRes ^ crcBuf[i];
      for ( j = 0; j < 8; j++)
      {
        crcTemp = crcRes & 0x0001;
        crcRes = crcRes >> 1;
        if (crcTemp)
        {
            crcRes = crcRes ^ 0xa001;
        }
      }
    }
    rtuCRC.calculated = crcRes;
    rtuCRC.calculated_L = (crcRes & 0XFF00) >> 8 ;
    rtuCRC.calculated_H = (crcRes & 0X00FF);
}

/**
  * @brief  This function performs incoming RTU data frame processing and
  			extracts all modbus master requests and returns from function when
  			unexpected frame is received.
  * @note   After debug operation, DEBUG flag should be reset in header file 
  			not to add additional delay to real-time process.
  * @param  none
  * @retval None
  */

void rtu_ModbusFrameProcessing(void)
{
      if ((rtu_modbusRxBuffer[SLAVE_ID] == rtu_deviceSlaveID[0]) || rtu_modbusRxBuffer[SLAVE_ID] == DI1000_UI_SLAVE_ID)
      {
        rtu_selectedSlaveID = rtu_deviceSlaveID[0];
        #if DEBUG
        printf("Selected device is me \n");
        printf("Request device id is %d \n", rtu_selectedSlaveID);
        #endif
      }

      else
      {
        #if DEBUG
        printf("Selected device is not me \n");
        #endif
				rtu_transmitDisable_receiveEnable();
        return;
      }
    

    rtu_modbusRegAdress = (rtu_modbusRxBuffer[REG_ADRESS_HIGH] << 8) | rtu_modbusRxBuffer[REG_ADRESS_LOW];
	
    if (rtu_modbusRegAdress >= MODBUS_LOWER_LIMIT_ADRESS && rtu_modbusRegAdress <= MODBUS_UPPER_LIMIT_ADRESS)
    {
      #if DEBUG
      printf("Modbus RTU starting adress is in the range \n");
      printf("Modbus RTU starting adress is %d \n", rtu_modbusRegAdress);
      #endif
    }
		
    else
    {
      #if DEBUG
      printf("Modbus RTU starting adress is out of range of device \n");
      #endif
			rtu_transmitDisable_receiveEnable();
      return;
    }
		
    rtu_modbusDataLen = (rtu_modbusRxBuffer[DATA_LEN_HIGH] << 8) | rtu_modbusRxBuffer[DATA_LEN_LOW];

    if(rtu_modbusDataLen <= MODBUS_MAX_DATA_LEN)
    {
      #if DEBUG
      printf("Modbus RTU requested data length is in the range \n");
      printf("Modbus RTU requested data length is %d \n", rtu_modbusDataLen);
      #endif
    }

    else
    {
      #if DEBUG
      printf("Modbus RTU requested data length is out of the range \n");
      #endif
			rtu_transmitDisable_receiveEnable();
      return;
    }

    rtuCRC.received_H = rtu_modbusRxBuffer[rtu_ModbusRxIndex - 2];
    rtuCRC.received_L = rtu_modbusRxBuffer[rtu_ModbusRxIndex - 1];
    rtu_modbusRxFrameLen = rtu_ModbusRxIndex - 2;
    rtu_crcCalculation(rtu_modbusRxBuffer, rtu_modbusRxFrameLen);

    if ((rtuCRC.received_L == rtuCRC.calculated_L) && (rtuCRC.received_H == rtuCRC.calculated_H))
    {
      #if DEBUG
      printf("CRC Check is OK \n");
      #endif
    }

    else
    {
      #if DEBUG
      printf("CRC Check is not OK \n");
      #endif
			rtu_transmitDisable_receiveEnable();
      return;
    }

    rtu_modbusStartingAdress = rtu_modbusRegAdress;
    rtu_modbusEndingAdress = rtu_modbusStartingAdress + rtu_modbusDataLen;

	
		rtu_transmitEnable_receiveDisable();
		
			
    switch(rtu_modbusRxBuffer[FUNCODE])
    {
      case READ_HOLDING_REGISTER:   
			{
				if(rtu_modbusEndingAdress > READ_HOLDING_REGISTER_ADRESS_LIMIT )
				{
					#if DEBUG
					printf("Requested data adress and length is not satisfied \n");
					#endif
					rtu_transmitDisable_receiveEnable();			
					return;
				}
				rtu_readHoldingRegister(); 
				break;
			}
			
			case WRITE_SINGLE_REGISTER:
			{
				#if DEBUG
        printf("I am in Single Write function \n");
        printf("rtu_modbusRegAdress is %d \n",rtu_modbusRegAdress);
        printf("rtu_modbusStartingAdress is %d \n",rtu_modbusStartingAdress);
        printf("rtu_modbusEndingAdress is %d \n",rtu_modbusEndingAdress);
        printf("rtu_modbusDataLen is %d \n",rtu_modbusDataLen);
        printf("Selected ID is %d \n",rtu_selectedSlaveID);
				#endif
				//rtu_writeSingleRegister();
				break;
			}
				
      case WRITE_MULTIPLE_REGISTER: 
      {
				if(rtu_modbusEndingAdress > WRITE_MULTIPLE_REGISTER_ADRESS_LIMIT)
				{
					#if DEBUG
					printf("Requested data adress and length is not satisfied \n");
					#endif
					rtu_transmitDisable_receiveEnable();			
					return;
				}
				
				#if DEBUG
        printf("I am in Multiple Write function \n");
        printf("rtu_modbusRegAdress is %d \n",rtu_modbusRegAdress);
        printf("rtu_modbusStartingAdress is %d \n",rtu_modbusStartingAdress);
        printf("rtu_modbusEndingAdress is %d \n",rtu_modbusEndingAdress);
        printf("rtu_modbusDataLen is %d \n",rtu_modbusDataLen);
        printf("Selected ID is %d \n",rtu_selectedSlaveID);
				#endif
				
        rtu_writeMultipleRegisters();
        break;
      }
			
			case UNIQUE_FUNCTION_REGISTER:
			{
				#if DEBUG
				printf("I am in Unique Read function \n");
        printf("rtu_modbusRegAdress is %d \n",rtu_modbusRegAdress);
        printf("rtu_modbusStartingAdress is %d \n",rtu_modbusStartingAdress);
        printf("rtu_modbusEndingAdress is %d \n",rtu_modbusEndingAdress);
        printf("rtu_modbusDataLen is %d \n",rtu_modbusDataLen);
        printf("Selected ID is %d \n",rtu_selectedSlaveID);
				#endif
				//rtu_readUniqueRegisters();
				break;
			}
			
      default: 
      {
        #if DEBUG
        printf("Modbus rtu function code is wrong !\n");
        #endif
				rtu_transmitDisable_receiveEnable();
        break;
      } 
    }
		
		
		


}

void rtu_readUniqueRegisters(void)
{
	  #if 0 
	  rtu_txBufferIndex = 3;
    rtu_modbusTxBuffer[SLAVE_ID] = rtu_modbusRxBuffer[SLAVE_ID];
    rtu_modbusTxBuffer[FUNCODE] = rtu_modbusRxBuffer[FUNCODE];
    rtu_modbusTxBuffer[RES_BYTE_COUNT] = 2 * rtu_modbusDataLen;

  if (rtu_modbusRegAdress == READ_IN_CH1)
  {
      rtu_modbusTxBuffer[rtu_txBufferIndex++] = (0x0000FF00 & (uint32_t)(rtu_deviceSlaveID[0])) >> 8;
      rtu_modbusTxBuffer[rtu_txBufferIndex++] = (0x000000FF & (uint32_t)(rtu_deviceSlaveID[0]));
      rtu_modbusRegAdress += 1;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
  }
	
	rtu_transmitData_readHoldingRegister();
	#endif
}
/**
  * @brief  This function includes Modbus RTU Holding Register function 
            implementation.
  * @note   This function is written for multiple slave devices in one
            device. Making this function for only one slave ID makes this
            function generic for other platforms.
  * @param  none
  * @retval None
  */

void rtu_readHoldingRegister(void)
{
    rtu_txBufferIndex = 3;
    rtu_modbusTxBuffer[SLAVE_ID] = rtu_modbusRxBuffer[SLAVE_ID];
    rtu_modbusTxBuffer[FUNCODE] = rtu_modbusRxBuffer[FUNCODE];
    rtu_modbusTxBuffer[RES_BYTE_COUNT] = 2 * rtu_modbusDataLen;

    if(rtu_selectedSlaveID == rtu_deviceSlaveID[0]) rtu_Feeder1DataPrep();
}

/**
  * @brief  This function includes Modbus RTU Holding Register function 
            implementation.
  * @note   This function is written for multiple slave devices in one
            device. Making this function for only one slave ID makes this
            function generic for other platforms.
  * @param  none
  * @retval None
  */

void rtu_writeMultipleRegisters(void)
{
    if(rtu_selectedSlaveID == rtu_deviceSlaveID[0]) rtu_getFeeder1_writeMultipleRegisters();
}


/**
  * @brief  This function includes Modbus RTU Holding Register function 
            implementation.
  * @note   This function is written for multiple slave devices in one
            device. Making this function for only one slave ID makes this
            function generic for other platforms.
  * @param  none
  * @retval None
  */
void rtu_getFeeder1_writeMultipleRegisters(void)
{
    rtu_ModbusRxIndex = 7;
	  
    if (rtu_modbusRegAdress == 1000)
    {
      komutlar.all = (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]) << 8;
      komutlar.all  |= (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]);
      rtu_modbusRegAdress += 1;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
    }
	
		if (rtu_modbusRegAdress == 1001)
    {
      hfKomutlar.all = (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]) << 8;
      hfKomutlar.all |= (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]);
      rtu_modbusRegAdress += 1;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
			
			
    }
		
		
			if (rtu_modbusRegAdress == 1002)
    {
      QrefRemoteIncStatcom = (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]) << 8;
      QrefRemoteIncStatcom |= (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]);
      rtu_modbusRegAdress += 1;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
			
			
    }
		
		
			if (rtu_modbusRegAdress == 1003)
    {
      QrefLocalIncStatcom = (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]) << 8;
      QrefLocalIncStatcom |= (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]);
      rtu_modbusRegAdress += 1;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
			
			
    }
		
		incomingDataParsing();
		
		


		
		#if 0
		
		if (rtu_modbusRegAdress == 1004)
    {
      dummyTestData.CH5 = (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]) << 8;
      dummyTestData.CH5 |= (uint32_t)(rtu_modbusRxBuffer[rtu_ModbusRxIndex++]);
      rtu_modbusRegAdress += 1;
      if (rtu_modbusRegAdress == rtu_modbusEndingAdress) rtu_modbusRegAdress = 0;
    }
		
		#endif
		
    rtu_transmitData_writeMultipleRegisters();
}




/**
  * @brief  This function performs modbus RTU response to Modbus Master's request
        according to appropriate slave ID, function code, data adress and 
        data length.
  * @note   DMA function is platform specific function. It should be changed 
            in other platforms.
  * @param  none
  * @retval None
  */
void rtu_transmitData_writeMultipleRegisters(void)
{
    rtu_modbusTxBuffer[0] = rtu_modbusRxBuffer[0];
    rtu_modbusTxBuffer[1] = rtu_modbusRxBuffer[1];
    rtu_modbusTxBuffer[2] = rtu_modbusRxBuffer[2];
    rtu_modbusTxBuffer[3] = rtu_modbusRxBuffer[3];
    rtu_modbusTxBuffer[4] = rtu_modbusRxBuffer[4];
    rtu_modbusTxBuffer[5] = rtu_modbusRxBuffer[5];
    rtu_crcCalculation(rtu_modbusRxBuffer, 6);
    rtu_modbusTxBuffer[6] = rtuCRC.calculated_H;
    rtu_modbusTxBuffer[7] = rtuCRC.calculated_L;
    HAL_UART_Transmit_IT(&huart4, rtu_modbusTxBuffer, 8);
		dataSentFlag=1;
}

/**
  * @brief  This function performs modbus RTU response to Modbus Master's request
        according to appropriate slave ID, function code, data adress and 
        data length.
  * @note   DMA function is platform specific function. It should be changed 
            in other platforms.
  * @param  none
  * @retval None
  */
void rtu_transmitData_writeSingleRegister(void)
{
    rtu_modbusTxBuffer[0] = rtu_modbusRxBuffer[0];
    rtu_modbusTxBuffer[1] = rtu_modbusRxBuffer[1];
    rtu_modbusTxBuffer[2] = rtu_modbusRxBuffer[2];
    rtu_modbusTxBuffer[3] = rtu_modbusRxBuffer[3];
    rtu_modbusTxBuffer[4] = rtu_modbusRxBuffer[4];
    rtu_modbusTxBuffer[5] = rtu_modbusRxBuffer[5];
    rtu_crcCalculation(rtu_modbusRxBuffer, 6);
    rtu_modbusTxBuffer[6] = rtuCRC.calculated_H;
    rtu_modbusTxBuffer[7] = rtuCRC.calculated_L;
    HAL_UART_Transmit_IT(&huart4, rtu_modbusTxBuffer, 8);
}


/**
  * @brief  This function performs modbus RTU response to Modbus Master's request
  			    according to appropriate slave ID, function code, data adress and 
  			    data length.
  * @note   DMA function is platform specific function. It should be changed 
            in other platforms.
  * @param  none
  * @retval None
  */

void rtu_transmitData_readHoldingRegister(void)
{		
    rtu_crcCalculation(rtu_modbusTxBuffer, rtu_txBufferIndex);
    rtu_modbusTxBuffer[rtu_txBufferIndex++] = rtuCRC.calculated_H;
    rtu_modbusTxBuffer[rtu_txBufferIndex++] = rtuCRC.calculated_L;
    rtu_modbusTxLen = rtu_txBufferIndex;
    HAL_UART_Transmit_IT(&huart4, rtu_modbusTxBuffer, rtu_txBufferIndex);
}



/**
  * @brief  This function prepares all calculated data in device for modbus
  			    response.
  * @note   All data is prepared when the data send over RTU. 
            Be careful that when 32 bit data is sent, rtu_modbusRegAdress is 
            increased by two, when 16 bit data is sent, rtu_modbusRegAdress is 
            increased by one.
  * @param  none
  * @retval None
  */

void rtu_Feeder1DataPrep(void)
{
	uint8_t i=0;
	
	mapDataTransfer();
	
	prepData4TX(konumlar.all,&rtu_modbusRegAdress,							READ_IN_CH1,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(panelInput.halfWord[0],&rtu_modbusRegAdress,		READ_IN_CH2,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(panelOutput.halfWord[0],&rtu_modbusRegAdress,		READ_IN_CH3,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(faultWord.halfWord[0],&rtu_modbusRegAdress,			READ_IN_CH4,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(faultWord.halfWord[1],&rtu_modbusRegAdress,			READ_IN_CH5,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(faultWord.halfWord[2],&rtu_modbusRegAdress,			READ_IN_CH6,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(stateInfo.all,&rtu_modbusRegAdress,							READ_IN_CH7,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(stateFault.halfWord[0],&rtu_modbusRegAdress,		READ_IN_CH8,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(flagInfo.all,&rtu_modbusRegAdress,							READ_IN_CH9,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(13,&rtu_modbusRegAdress,												READ_IN_CH10,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	
	prepData4TX(analogData.ch.Qtotal,&rtu_modbusRegAdress,			READ_IN_CH11,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(analogData.ch.Vpp,&rtu_modbusRegAdress,					READ_IN_CH12,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(analogData.ch.Iline,&rtu_modbusRegAdress,				READ_IN_CH13,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(analogData.ch.Vdc,&rtu_modbusRegAdress,					READ_IN_CH14,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(analogData.ch.Vdcr,&rtu_modbusRegAdress,				READ_IN_CH15,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX(analogData.ch.temp,&rtu_modbusRegAdress,				READ_IN_CH16,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX((int16_t)(QrefLocalStatcom*0.001f),&rtu_modbusRegAdress,		READ_IN_CH17,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);
	prepData4TX((int16_t)(QrefRemoteStatcom*0.001f),&rtu_modbusRegAdress,	READ_IN_CH18,rtu_modbusTxBuffer,&rtu_txBufferIndex,rtu_modbusEndingAdress);


	
  rtu_transmitData_readHoldingRegister();
  
}

/*void rtu_getFeeder1_writeSingleRegister(void)
{
	  #if 0
    if (rtu_modbusRegAdress == WRITE_OUT_CH1)
    {
      outputStatus.CH1 = (uint32_t)(rtu_modbusRxBuffer[4]) << 8;
      outputStatus.CH1 |= (uint32_t)(rtu_modbusRxBuffer[5]);
    }
		#endif
	
		rtu_transmitData_writeSingleRegister();
}

void rtu_writeSingleRegister(void)
{
	  if(rtu_selectedSlaveID == rtu_deviceSlaveID[0]) rtu_getFeeder1_writeSingleRegister();
}*/

void rtu_transmitEnable_receiveDisable(void)
{
	HAL_GPIO_WritePin(UART_DE_GPIO_Port,UART_DE_Pin,GPIO_PIN_SET);
	#if DEBUG
  printf("Transmit Enabled, Receive Disabled for RTU Comm \n");
	#endif
}

void rtu_transmitDisable_receiveEnable(void)
{
	HAL_GPIO_WritePin(UART_DE_GPIO_Port,UART_DE_Pin,GPIO_PIN_RESET);
	#if DEBUG
	printf("Receive Enabled, Transmit Disabled for RTU Comm \n");
	#endif
}
