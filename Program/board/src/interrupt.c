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
	IP = 0x1A;
	IE = 0x92;		   
} 

void msecInterruptStart()
{
	TR0 = TRUE;
}

void SerialInterrupt() interrupt 4
{
	UC ucmData;
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
		if( ( System.Serial.enRxStatus EQ RX_MONITORING ) OR ( System.Serial.enRxStatus EQ RX_STARTED ) )
		{
			System.Serial.usmRxTimeout = RECEPTION_TIMEOUT;
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
 
	if(System.AppStruct.usmDelay GT 0)
	{
		System.AppStruct.usmDelay--;
	}
	//----------------------
	 //Serial Reception Status
	 if(System.Serial.enRxStatus EQ RX_STARTED)
	 {
		   if(System.Serial.usmRxTimeout NEQ 0)
		   {
		   		System.Serial.usmRxTimeout--;
				if(System.Serial.usmRxTimeout EQ 0)
				{
					System.Serial.enRxStatus = RX_COMPLETED;
					REN = FALSE;
					//call routine
			//		if(System.Serial.fnRxFunc NEQ NULL)
			//		{
			//			System.Serial.fnRxFunc(System.Serial.vRxData,RX_COMPLETED);
			//		}
//					if(System.Serial.bitRxContinuous EQ TRUE)
//					{
			//			REN = TRUE;
//					}
				}
		   }
	  }

	  if(System.Serial.enRxStatus EQ RX_MONITORING)
	  {
	  	if(System.Serial.usmRxWaitTimeout NEQ 0)
		{
			System.Serial.usmRxWaitTimeout--;
			if(System.Serial.usmRxWaitTimeout EQ 0)
			{
				System.Serial.enRxStatus = RX_TIMEOUT;
				REN = FALSE;
				//if(System.Serial.fnRxFunc NEQ NULL)
				//{
				//	System.Serial.fnRxFunc(System.Serial.vRxData,RX_TIMEOUT);
				//}
//				if(System.Serial.bitRxContinuous EQ TRUE)
//				{
//					REN = TRUE;
//				}
			}
		}
	  }
	 //-----------------------
	//-----------------------
	TH0 = 0xFC;
	TL0 = 0x66;
	TR0 = TRUE;
}