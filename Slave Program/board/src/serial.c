#include "global.h"

void SerialInit()
{
	TR1 	= TRUE;  
	SCON 	= 0xD0; 
	REN 	= TRUE;
	SM2		= TRUE;
	MAX485_TX 	= RECEIVE;
	System.Serial.ucpRxBuff = &System.QueryStruct.ucmStartByte;
	System.Serial.ucmRxLength = sizeof(System.QueryStruct); 
	System.Serial.enRxStatus = RX_ADDRESS;
}

void SendData(UC *ucpData, UC ucmLength)//, TagFnTxFunc fnTxFunc, void* vTxData)
{
	UC ucmData;
	System.Serial.enTxComplete 	= SENDING;
	//System.Serial.fnTxFunc 		= fnTxFunc;
	//System.Serial.vTxData 		= vTxData;
	System.Serial.ucpDataPtr 	= ucpData;
	System.Serial.ucmTxLength 	= ucmLength - 1;
	ucmData = *(System.Serial.ucpDataPtr); 
	System.Serial.ucpDataPtr++;
	if(TI EQ TRUE)
	{
		TI = FALSE;
	}
	SBUF = ucmData; 
} 
/*
void RecData(UC *ucpData, UC ucmDataLength, UC ucmTimeout)//, TagFnRxFunc fnRxFunc, void* vRxData , UC ucmRxContinuous)
{
	System.Serial.ucpRxBuff 	= ucpData;
	System.Serial.ucmRxLength 	= ucmDataLength;
	System.Serial.ucmRxNdx		= 0;	
	//System.Serial.fnRxFunc 		= fnRxFunc;
	//System.Serial.vRxData 		= vRxData;
	System.Serial.usmRxWaitTimeout = ucmTimeout;// * 1000;
	if(RI EQ TRUE)
	{
		RI = FALSE;
	}
//	System.Serial.bitRxContinuous = ucmRxContinuous;
	System.Serial.enRxStatus = RX_MONITORING;
	REN = TRUE;
}
*/
/*
void SendAddress()
{
	TB8 = TRUE; 
	SendData(&System.Serial.ucmQueryAddress,sizeof(UC));//,0, 0);
}
*/
void SendResponse()
{ 
//	Delay(100);
	TB8 = FALSE;
	System.QueryStruct.ucmStartByte = 0xA5;
	System.QueryStruct.ucmEndByte   = 0x5A;
	SendData(&System.QueryStruct.ucmStartByte,sizeof(System.QueryStruct));//, 0, 0);
}
/*
void ReceiveResponse()
{
	RecData(&System.QueryStruct.ucmStartByte,sizeof(System.QueryStruct), RESPONSE_TIMEOUT);
}
*/
/*
void QuerySendFinished(void* vData)
{ 
	return;
}

void QueryReceiveFinished(void* vData, TagenRxStatus enRxStatus)
{
	return;
}
  */