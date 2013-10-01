#include "global.h"

void IoInit()
{ 
	//Inputs
	FIRE_SENSOR = INPUT_PIN;
	FIRE_SWITCH	= INPUT_PIN;
	NO_SWITCH	= INPUT_PORT;
	
	//Outputs	
	FIRE_RELAY 	= OUTPUT_PIN;
	FIRE_LED	= OUTPUT_PIN;
	
	MAX485_TX  	= OUTPUT_PIN;   	 
}