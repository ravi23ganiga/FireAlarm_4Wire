#include "global.h"

void InterruptInit()
{
	//Basic interrupt configuration 
	IE 		= 0x00;
	//Timer interrupt configuration
	TMOD 	= 0x21;
	//Timer0 as 1msec configuration
	TR0 	= FALSE;
	TH0 	= 0xFC;
	TL0 	= 0x66;
	//Timer 1 as 9600 baud rate generator
	TR1 	= FALSE;
	TH1 	= 0xFD;
	TL1 	= 0xFD;
	IT0 = 1;
	IT1 = 1; 
	IP = 0x05;
	IE = 0x97;		   
} 

void msecInterruptStart()
{
	TR0 = TRUE;
}
void msecInterruptStop()
{
	TR0 = FALSE;
}

void SerialInterrupt() interrupt 4
{
	UC ucmData;
	msecInterruptStart();
	if(TI EQ TRUE)
	{
		//Transmission Interrupt 
		if(System.Serial.ucmTxLength NEQ 0)
		{
			ucmData = VALUE_AT_ADDRESS(System.Serial.ucpDataPtr);
			System.Serial.ucpDataPtr++;
			System.Serial.ucmTxLength--;
			SBUF = ucmData; 
		}
		else
		{
			System.Serial.enTxComplete = COMPLETE;
			//if(System.Serial.fnTxFunc NEQ NULL)
			//{
			//	System.Serial.fnTxFunc(System.Serial.vTxData);
			//}
		}
		TI = FALSE;
	}
	else
	{
		//Receiver Interrupt   
		if(System.Serial.enRxStatus EQ RX_ADDRESS)
		{ 
			ucmData = SBUF; 
			if((ucmData EQ  System.AppStruct.ucmSysAddr) OR (ucmData EQ	 BROADCAST_ADDR))
			{
				SM2 = FALSE;
				System.Serial.ucmRxNdx = 0;
			//	System.AppStruct.bitPowerDown = FALSE;
				System.Serial.enRxStatus = RX_MONITORING;
			}
		}
		else if( ( System.Serial.enRxStatus EQ RX_MONITORING ) OR ( System.Serial.enRxStatus EQ RX_STARTED ) )
		{ 
			System.Serial.usmRxTimeout = RECEPTION_TIMEOUT;//100msec
			System.Serial.enRxStatus = RX_STARTED;
			
			if(System.Serial.ucmRxNdx NEQ (System.Serial.ucmRxLength - 1))
			{
				System.Serial.ucpRxBuff[System.Serial.ucmRxNdx] = SBUF;	   
				System.Serial.ucmRxNdx++;
			}
		}
		RI = FALSE;
	}
}

//1 msec interrupt 
void TimerInterrupt() interrupt 1
{
	TR0 = FALSE;
	//1msec timer interrupt
	//----------------------
	if(System.AppStruct.usmDelay GT 0)
	{
		System.AppStruct.usmDelay--;
	}
	 //Serial Reception Status
	 if(System.Serial.enRxStatus EQ RX_STARTED)
	 {
		   if(System.Serial.usmRxTimeout NEQ 0)
		   {
		   		System.Serial.usmRxTimeout--;
				if(System.Serial.usmRxTimeout EQ 0)
				{ 
					System.Serial.enRxStatus = RX_COMPLETED;
					SM2 = TRUE;
					REN = FALSE; 
				}
		   }
	  }

/*	  if(System.Serial.enRxStatus EQ RX_MONITORING)
	  {
	  	if(System.Serial.usmRxWaitTimeout NEQ 0)
		{
			System.Serial.usmRxWaitTimeout--;
			if(System.Serial.usmRxWaitTimeout EQ 0)
			{
				System.Serial.enRxStatus = RX_TIMEOUT;
				REN = FALSE; 
			}
		}
	  }*/
	 //-----------------------
	//-----------------------
	TH0 = 0xFC;
	TL0 = 0x66;
	TR0 = TRUE;
}

//Fire switch interrupt
//make power down bit false
void ExternalInterrupt0() interrupt 0
{
	Delay(100);
	if(FIRE_SWITCH EQ FALSE)
	{
		FireUpdateSystem();
	}
}


//Fire Sensor  interrupt
//make power down bit false
void ExternalInterrupt1() interrupt 2
{
	Delay(100);
	if(FIRE_SENSOR EQ FALSE)
	{
		FireUpdateSystem();
	}
}