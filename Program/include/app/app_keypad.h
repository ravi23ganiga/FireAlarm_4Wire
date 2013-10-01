#ifndef __APP_KEYPAD__
#define __APP_KEYPAD__

#define KEY_COUNTER_MAX		3

typedef struct
{	
	UC				ucmKeyCounter;
	UC				ucmKeyValue;   
	UC 				bitNumLock:1;
}TagAppKeyStruct;

void KeypadCheck();
UC ValidateFloor(UC ucmFloorNo);

#endif