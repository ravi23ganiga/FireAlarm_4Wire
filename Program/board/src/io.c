#include "global.h"

void IoInit()
{
	FIRE_LED 		= OUTPUT_PIN;
	FIRE_RELAY 		= OUTPUT_PIN;
	SYSTEM_START 	= OUTPUT_PIN; 
	MAX485_TX		= OUTPUT_PIN; 

	KEYPAD 			= INPUT_PORT;
	ACCEPT_SW 		= INPUT_PIN;
}