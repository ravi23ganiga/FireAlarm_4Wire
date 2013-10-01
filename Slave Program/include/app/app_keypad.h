#ifndef __APP_KEYPAD__
#define __APP_KEYPAD__

#define KEY_COUNTER_MAX		3

typedef struct
{	
	UC				ucmKeyCounter;
	UC				ucmKeyValue;
//	TagenKeyType	enCurKey;
	UC				bitEnterDone:1;
	UC 				bitCallAllDone:1;
	UC				bitAcceptDone:1;
	UC 				bitNumLock:1;
}TagAppKeyStruct;

void KeypadCheck();
UC ValidateFloor(UC ucmFloorNo);

#endif