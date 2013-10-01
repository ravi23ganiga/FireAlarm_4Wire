#ifndef __APP__
#define __APP__

#define APP_START while(1)
#define SYSTEM_HANG	while(1) 
#define MAX_FLOOR		32
#define MAX_FLOOR_REG	(MAX_FLOOR/8)
#define REGISTERED		1
#define NOT_REGISTERED	0
#define ERROR_MAX		3 


extern UC ucmTest;

typedef struct
{
 	UC 		ucmSysAddr;
	UC		ucmQueryState;
	US		usmDelay; 	  
	UC		bitPowerDown:1;
	UC 		bitSysUpdate:1;
	UC		bitFire:1;
}TagAppStruct;

void AppStart();
void AppInit();
void PowerDownSystem();
void PrepareAndSendResponse();
void QuerySelect();
void QuerySend();
void ResponseCheck();
void SystemDecision();
void UpdateSystem();
void ResetSystem();
void StartRegistration();
void RegisterFloor(UC ucmFloorNo);
void FireUpdateSystem();
#endif