#ifndef __APP__
#define __APP__

#define APP_START while(1)
#define SYSTEM_HANG	while(1) 
#define MAX_FLOOR		32
#define MAX_FLOOR_REG	(MAX_FLOOR/8)
#define REGISTERED		1
#define NOT_REGISTERED	0
#define ERROR_MAX		3
#define FIRE_RESPONSE	0xFF

#define FIRE_UPDATE		0
#define ACCEPT_UPDATE	1

typedef struct
{
	TagAppKeyStruct KeyStruct; 
	UC				ucmRegistration[MAX_FLOOR_REG];
	US				usmDelay;
	UC				ucmCurAddress;
	//Query related variables
	//UC				ucmCurQuery;
	//UC				ucmErrorCounter;
//	UC				ucmResponse;
	//UC 				ucmResponseState;
//	UC				ucmQueryBuff[30];
	//--------------------------------

	//query related bit variables
	//UC				bitQuerySemaphore:1;
	UC				bitResponseSemaphore:1;
//	UC				bitResponseState:1;
	
}TagAppStruct;

void AppStart();
void AppInit();
void KeypadCheck();
void QuerySelect();
void QuerySend();
void ResponseCheck();
void SystemDecision();
void UpdateSystem(UC ucmUpdateType,UC ucmFloorNo);
void ResetSystem();
void StartRegistration();
void RegisterFloor(UC ucmFloorNo);
UC IsFloorRegistered(UC ucmFloorNo);
UC NextRegisteredFloor(UC ucmFloorNo);
void Test();
#endif