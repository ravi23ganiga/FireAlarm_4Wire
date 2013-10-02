#include "global.h"

TagSystem System; 

void main()
{
	SystemBoot(); 
	AppStart();
	while(1);
}

void SystemBoot()
{
	InterruptInit();
	IoInit();
	SerialInit();
	DispInit();
	KeypadInit(); 
	msecInterruptStart();
}

void Delay(US usmDelay)
{ 
	System.AppStruct.usmDelay = usmDelay;
	while(System.AppStruct.usmDelay GT 0);
}

