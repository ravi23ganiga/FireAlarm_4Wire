#ifndef __FIRE_SERIAL__
#define __FIRE_SERIAL__

#define RECEPTION_TIMEOUT	100
#define RESPONSE_TIMEOUT	1000
#define FIRE_QUERY_TIMEOUT	1000
#define QUERY_BUFF_SIZE		50
#define QUERY_LENGTH		1

#define TRANSMIT			1
#define RECEIVE				0

//Different Queries	MAX 255 QUERIES

#define REGISTRATION_QUERY		0xF1
#define RESET_QUERY				0xF2
#define ACCEPT_SIMULCAST_QUERY	3
#define ACCEPT_QUERY			0xF3					
#define CALL_ALL_QUERY			0xF4
#define	FIRE_QUERY				6
#define FIRE_TEST_QUERY			0xF5
#define NO_QUERY				8
#define ACCEPT_RESPONSE			9
#define CALL_ALL_RESPONSE		10
#define FIRE_QUERY_RESPONSE		11
#define FIRE_TEST_RESPONSE		12

//Different ResponsE
#define RESPONSE_CONFIG		0
#define RESPONSE_CHECK		1
//Address for Query

#define BROADCAST_ADDR			0x00

typedef enum  {SENDING , COMPLETE}TagenTxComplete;
typedef enum { TRUE , FALSE } TagenRxComplete;
typedef enum {RX_NOT_STARTED, RX_MONITORING, RX_STARTED, RX_COMPLETED, RX_TIMEOUT}TagenRxStatus; 

typedef struct
{
	UC 				ucmTxLength;
	UC 				ucmRxLength;
	US				usmRxTimeout;
	US				usmRxWaitTimeout;
	UC				ucmRxNdx;
	UCP 			ucpDataPtr;
	UCP				ucpRxBuff;
	TagenTxComplete enTxComplete; 
	TagenRxStatus	enRxStatus; 
	UC				ucmQueryAddress; 
}TagSerial;

//Query Structure for MultiProcessor Communication
typedef struct
{
	UC		ucmStartByte;
	//UC		ucmAddress;
	UC 		ucmQueryType;  
	UC		ucmQueryData; 
	UC 		ucmEndByte;
}TagQueryStruct;

void SerialInit(); 
void SendData(UC *ucpData, UC ucmDataLength);//, TagFnTxFunc fnTxFunc, void* vTxData); 
void RecData(UC *ucpData, UC ucmDataLength,UC ucmTimeout);//, TagFnRxFunc fnRxFunc, void* vRxData , UC ucmRxContinuous);
void SendAddress();
void SendQuery();
void ReceiveResponse();
 
#endif /* __FIRE_SERIAL__ */