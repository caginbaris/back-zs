#include "main.h"
#include "Modbus_RTU_Slave.h"
#include "Modbus_Map.h"
#include "usart.h"
#include "ios.h"
//comm side entries---start--main

uint8_t ReceiveData, ReceiveData2 , RX_Index = 0;
unsigned char rtu_modbusRxBuffer[RX_BUFFER_LIMIT];
extern uint8_t recComp;

uint16_t rtu_ModbusRxIndex = 0;

uint16_t recTimeOut=0, recFlag, transmitComp=0,success = 0;


uint8_t rtuWriteTimerFlag = 0;
extern uint32_t rtuWriteTimerCnt;
extern uint32_t rtu_deviceSlaveID[10];

extern uint8_t rtuMasterSlaveID;
extern uint32_t comErrorCounter;
uint32_t fckcnt = 0;
uint8_t comErrorFlag = 0;
extern uint32_t commErrorTimeOut;

//comm side start sysTick

extern uint16_t recTimeOut;
uint8_t recComp;
extern uint16_t recFlag;

extern uint8_t rtuWriteTimerFlag;
uint32_t rtuWriteTimerCnt = 0;
uint32_t commErrorTimeOut = 0;
extern uint8_t comErrorFlag;
extern volatile uint8_t conversion_complete;


void enableDisableTransmit(uint8_t en){
	
	if(en){

	HAL_GPIO_WritePin(UART_DE_GPIO_Port,UART_DE_Pin,1);
	
	}else{
	
	HAL_GPIO_WritePin(UART_DE_GPIO_Port,UART_DE_Pin,0);
		
	}

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	

		
	  if (huart->Instance == UART4)	
		{
		HAL_UART_Receive_IT(&huart4,&ReceiveData, 1);	
		rtu_modbusRxBuffer[rtu_ModbusRxIndex++] = ReceiveData;
    recTimeOut = 0;
    recFlag = 1;
	  transmitComp = 0;
			
		}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

		
    if (huart->Instance == UART4)  
    {

			transmitComp = 1;
			enableDisableTransmit(0);
    }
}


void mainLoopCommPart(void){

		//comm side start
		
		if(recComp == 1 && recFlag == 1) 
		{
    rtu_ModbusFrameProcessing();
    rtu_ModbusRxIndex = 0;
    recComp = 0;
    recFlag = 0;
		}
		
		
		
		
		if(comErrorFlag == 1) fckcnt++;
		if(commErrorTimeOut >= 200) fckcnt++;
		
		//comm side end


}


void sysTickCommPart(void){

		recTimeOut++;
	if(recFlag == 1 && recTimeOut == 10) 
	{
		recComp = 1;
		recTimeOut = 0;
	}
	
	if(recTimeOut == 30000) 
	{
		recTimeOut = 0;
	}
	

	
	if(rtuWriteTimerFlag == 1)
	{
		rtuWriteTimerCnt++;
	}
	
	commErrorTimeOut++;
	if(commErrorTimeOut == 3 * 100) comErrorFlag = 1;
	if(commErrorTimeOut == 0XFFFF) commErrorTimeOut = 0;


}

void initComm(void){

	HAL_UART_Receive_IT(&huart4,&ReceiveData, 1);	//activate UART receive interrupt every time
	rtu_deviceSlaveID[0] = 1; //cau
	enableDisableTransmit(0);


}



