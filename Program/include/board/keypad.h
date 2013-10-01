#ifndef __KEYPAD__
#define __KEYPAD__

#define ROW_MAX		4
#define COL_MAX		3 
#define KEY_PRESS	0
#define COUNTER_VALID_ADDR 2

typedef enum 
{
		ONE   , TWO   , THREE   ,
		FOUR  , FIVE  , SIX     ,
		SEVEN , EIGHT , NINE    ,
		ENTER , ZERO  , CALLALL ,
		ACCEPT,	NOKEY
}TagenKeyType;

typedef struct
{
	UC ucmRowNo;
	  
}TagKeyStruct;

extern TagenKeyType ucmKeyPad[4][3];

void KeypadInit();
TagenKeyType KeyScan();

#endif /* __KEYPAD__ */