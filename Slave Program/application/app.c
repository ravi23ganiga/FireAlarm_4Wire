#include "global.h" 

UC ucmTest;
/*
	Pendingwork
	//Reset query
	//Delay
	//Registration from 0 to 60 consider the delay of this routine
*/

//......................
//Put Sensor Check
//.......................
void AppStart(void)
{ 		   
	AppInit();  

	APP_START
	{
		if(System.AppStruct.bitPowerDown EQ TRUE)
		{
	  		PowerDownSystem();
		}
		if(System.Serial.enRxStatus NEQ RX_ADDRESS)
		{
			while(System.Serial.enRxStatus 	NEQ RX_COMPLETED);//#chk may get in infinite ,loop due to timeout	
			System.Serial.enRxStatus = RX_ADDRESS; 
			PrepareAndSendResponse(); 
			REN = TRUE; 
		}
	}
}

void AppInit()
{
	System.AppStruct.ucmSysAddr = NO_SWITCH & 0x3F;
	System.AppStruct.bitPowerDown = TRUE;
}

void ResetSystem()
{
	FIRE_RELAY = 0;
	FIRE_LED = 0; 
	System.AppStruct.bitSysUpdate = FALSE;
	System.AppStruct.bitFire = FALSE;
	System.AppStruct.ucmSysAddr = NO_SWITCH & 0xCF;
}

void PowerDownSystem()
{
	msecInterruptStop();
	PCON = 0x01;
} 

void PrepareAndSendResponse() 
{
 	MAX485_TX  = TRANSMIT;
 	    
	switch(System.QueryStruct.ucmQueryType)
	{
		case REGISTRATION_QUERY:     
			SendResponse();
			while(System.Serial.enTxComplete NEQ COMPLETE);  
			break;

		case RESET_QUERY: 
			ResetSystem();
			break;

		case ACCEPT_QUERY:
			FIRE_RELAY = FALSE;
			break;

		case CALL_ALL_QUERY:
			FireUpdateSystem();
			break;

		case FIRE_QUERY:
			FireUpdateSystem();
			break;

		case FIRE_TEST_QUERY: 
			if(System.AppStruct.bitFire EQ TRUE)
			{
				System.QueryStruct.ucmQueryData	 = FIRE_RESPONSE;
			}
			else
			{
				System.QueryStruct.ucmQueryData = 0x00; 
			}
			SendResponse();
			while(System.Serial.enTxComplete NEQ COMPLETE);
			break;

		default:
			break;
	}
	MAX485_TX = RECEIVE;
}

void FireUpdateSystem()
{
	//if(System.AppStruct.bitFire NEQ TRUE)
	//{
	//	if(System.AppStruct.bitSysUpdate NEQ TRUE)
	//	{
			System.AppStruct.bitFire =  TRUE;
			System.AppStruct.bitSysUpdate = TRUE;
			FIRE_LED = TRUE;
			FIRE_RELAY = TRUE;	
	//	}
	//}
}