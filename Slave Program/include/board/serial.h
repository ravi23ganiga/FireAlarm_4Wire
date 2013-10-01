#ifndef __FIRE_SERIAL__
#define __FIRE_SERIAL__

#define RECEPTION_TIMEOUT	100
#define RESPONSE_TIMEOUT	100
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
#define PENDING					0
#define NO_RESPONSE				1
#define FIRE_RESPONSE			0xFF

//Address for Query

#define BROADCAST_ADDR			0x00

typedef enum  {SENDING , COMPLETE}TagenTxComplete;
typedef enum { TRUE , FALSE } TagenRxComplete;
typedef enum {RX_ADDRESS, RX_MONITORING, RX_STARTED, RX_COMPLETED}TagenRxStatus;
typedef void (*TagFnTxFunc)(void* vData);
typedef void (*TagFnRxFunc)(void* vData, TagenRxStatus enRxStatus);

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
//	TagenRxComplete	enRxComplete;
	TagenRxStatus	enRxStatus;
//	TagFnTxFunc 	fnTxFunc;
//	void*			vTxData;
//	TagFnRxFunc		fnRxFunc;
//	void*			vRxData;
	UC				ucmQueryAddress;
//	UC				ucmQueryResponseStatus;
//	UC				bitRxContinuous:1;
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
//void SendAddress();
void SendResponse();
void ReceiveResponse();
//void QuerySendFinished(void* vData);
//void QueryReceiveFinished(void* vData, TagenRxStatus enRxStatus);

#endif /* __FIRE_SERIAL__ */