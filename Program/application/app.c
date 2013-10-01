#include "global.h" 
//#chk pend: Final Release

/*...........----------------------------............
  #chk pend list	 
   2. 7 Seg Display implementation
	Requirement: There should always be a floor that should be numbered floor no 1 
*///..........----------------------------............

/*
	Pendingwork	  
*/

void AppStart(void)
{ 
	AppInit(); 	 
	ResetSystem(); 	 
	StartRegistration();  //#chk check for maximum registration
	SYSTEM_START = TRUE;	 
	APP_START
	{
		KeypadCheck();  
		QuerySend();
		ResponseCheck();  
		Test();	   
	}
}

void AppInit()
{								    
	System.QueryStruct.ucmQueryData = 0xFF;	 
}

void ResetSystem()
{
	Delay(1000);		  //#chk test the timing due to heavy delay
	System.Serial.ucmQueryAddress 	= BROADCAST_ADDR;
	System.QueryStruct.ucmQueryType = RESET_QUERY; 
	SendQuery();
	while(System.Serial.enTxComplete NEQ COMPLETE);
	Delay(100);			  //#chk test the timing
}

//Registration of the floor
//-------------------------


//............................
//#chk pend:	Consider the delay of this routine
//#chk pend:	Validate the received response	
//............................
void StartRegistration()
{
	UC ucmFloorNo = 0;
	UC ucmTestVal = FALSE;

	System.Serial.ucmQueryAddress = 0x00;
	System.QueryStruct.ucmQueryType = REGISTRATION_QUERY;
	System.QueryStruct.ucmQueryData = 0xFF;
	while(ucmFloorNo < MAX_FLOOR)
	{
		System.Serial.ucmQueryAddress++;
		SendQuery(); 	 
		while(System.Serial.enTxComplete NEQ COMPLETE); 	   
		ReceiveResponse();	    
		while(ucmTestVal NEQ TRUE)
		{
			if(System.Serial.enRxStatus EQ RX_COMPLETED)
			{
				//vallidate the received response  
				RegisterFloor(ucmFloorNo); 
				ucmTestVal = TRUE;	
			}
			else if(System.Serial.enRxStatus EQ RX_TIMEOUT)
			{
				ucmTestVal = TRUE;
			}
		} 
		ucmTestVal = FALSE; 
		ucmFloorNo++;
	}		
}

void RegisterFloor(UC ucmFloorNo)
{
	UC ucmFloorArrayIndex, ucmFloorBit; 
	ucmFloorArrayIndex = (ucmFloorNo / 8);
	ucmFloorBit = (ucmFloorNo % 8);
	System.AppStruct.ucmRegistration[ucmFloorArrayIndex] |= (1 << ucmFloorBit);
}

UC IsFloorRegistered(UC ucmFloorNo)
{
	UC ucmFloorArrayIndex, ucmFloorBit;
	if(ucmFloorNo LTE 0)
	{
		return FALSE;
	}
	ucmFloorNo--;
	ucmFloorArrayIndex = (ucmFloorNo / 8);
	ucmFloorBit = (ucmFloorNo % 8);
	if((System.AppStruct.ucmRegistration[ucmFloorArrayIndex]) & (1 << ucmFloorBit))
	{ 
		return TRUE;	
	}	
	else
	{
		return FALSE;
	}
}

/*
  There should always be a floor that should be numbered floor 1	
*/

UC NextRegisteredFloor(UC ucmFloorNo)
{ 
	ucmFloorNo++;
	while(ucmFloorNo LTE MAX_FLOOR)
	{
		if(IsFloorRegistered(ucmFloorNo))
		{
			return ucmFloorNo;
		}	
		ucmFloorNo++;
	}
	ucmFloorNo = 1; 
	return ucmFloorNo;
}

//------------------------------

/*
  Pending works
  #chk pend: 1. Clear all implementation 
*/

void KeypadCheck()
{
	TagenKeyType curKey = NOKEY;
	UC ucmRetVal;
	if(System.AppStruct.KeyStruct.bitNumLock EQ UNLOCKED)
	{
		curKey = KeyScan(); 	 
		if( ( (curKey GTE ONE) AND (curKey LTE NINE) ) OR (curKey EQ ZERO) )
		{ 
			System.AppStruct.KeyStruct.ucmKeyCounter++;		    
			if(System.AppStruct.KeyStruct.ucmKeyCounter GTE KEY_COUNTER_MAX)
			{
				System.AppStruct.KeyStruct.ucmKeyValue = 0;
				System.AppStruct.KeyStruct.ucmKeyCounter = 1;				
			}
			System.AppStruct.KeyStruct.ucmKeyValue *= 10;
			if(curKey NEQ ZERO)
			{
				System.AppStruct.KeyStruct.ucmKeyValue += (curKey + 1);
			}	   
		}
		else
		{ 
			if( curKey EQ ENTER )
			{
				if(System.AppStruct.KeyStruct.ucmKeyCounter LTE COUNTER_VALID_ADDR)
				{ 
					ucmRetVal = IsFloorRegistered(System.AppStruct.KeyStruct.ucmKeyValue);
					if(ucmRetVal EQ TRUE)
					{  
						System.QueryStruct.ucmQueryType 		= FIRE_QUERY;
						System.Serial.ucmQueryAddress 			= System.AppStruct.KeyStruct.ucmKeyValue; 
						UpdateSystem(FIRE_UPDATE);
						System.AppStruct.KeyStruct.bitNumLock   = LOCKED;
					} 
				} 
				System.AppStruct.KeyStruct.ucmKeyCounter = 0;
				System.AppStruct.KeyStruct.ucmKeyValue = 0; 
			}
			else if( curKey EQ CALLALL)
			{ 
				System.QueryStruct.ucmQueryType 			= CALL_ALL_QUERY;
				System.Serial.ucmQueryAddress 				= BROADCAST_ADDR;
				System.AppStruct.KeyStruct.bitNumLock	   	= LOCKED; 
				UpdateSystem(FIRE_UPDATE);
				System.AppStruct.KeyStruct.ucmKeyCounter 	= 0;
				System.AppStruct.KeyStruct.ucmKeyValue 		= 0;
			}
	
			else if(curKey EQ ACCEPT)
			{
				//#chk accept not to be done for broadcast addr 				
				System.QueryStruct.ucmQueryType 			= ACCEPT_QUERY; 
				System.Serial.ucmQueryAddress 				= System.AppStruct.KeyStruct.ucmKeyValue;				    
				System.AppStruct.KeyStruct.bitNumLock	   	= LOCKED; 
				UpdateSystem(ACCEPT_UPDATE);
				System.AppStruct.KeyStruct.ucmKeyCounter 	= 0;
				System.AppStruct.KeyStruct.ucmKeyValue 		= 0;
			} 
			//clear button
		}
	}
}

void UpdateKeyVar()
{ 
	System.AppStruct.KeyStruct.bitNumLock	  	= UNLOCKED;
}

 /*
 */
void QuerySend()
{
	if( System.Serial.enTxComplete EQ COMPLETE )
	{
		if(System.AppStruct.bitResponseSemaphore EQ UNLOCKED)
		{
			if( System.AppStruct.KeyStruct.bitNumLock EQ  LOCKED ) 
			{ 			   
				switch(System.QueryStruct.ucmQueryType)
				{ 
					case ACCEPT_QUERY:	 	  
						break;
				
					case CALL_ALL_QUERY:  
						break;
				
					case FIRE_QUERY:	   			   		 
						break; 
		
					default:
						break;
				}
				SendQuery();
				UpdateKeyVar();
				Delay(100); 
			} 	 
			else
			{	 
				System.QueryStruct.ucmQueryType 		=  FIRE_TEST_QUERY;
				System.AppStruct.ucmCurAddress 			= NextRegisteredFloor(System.AppStruct.ucmCurAddress);
				System.Serial.ucmQueryAddress 			= System.AppStruct.ucmCurAddress;
				System.AppStruct.bitResponseSemaphore 	= LOCKED;
				SendQuery();
				while (System.Serial.enTxComplete NEQ COMPLETE);
			    RecData(&System.ResponseStruct.ucmStartByte,sizeof(System.ResponseStruct),FIRE_QUERY_TIMEOUT);  
			} 
		}
	}
}



void ResponseCheck()
{
	if( ( System.AppStruct.bitResponseSemaphore EQ LOCKED )
		AND (System.Serial.enTxComplete EQ COMPLETE) )
	{
		if(System.Serial.enRxStatus EQ RX_COMPLETED)
		{		   
			System.AppStruct.bitResponseSemaphore = UNLOCKED;
			if(System.ResponseStruct.ucmQueryData EQ FIRE_RESPONSE)
			{   
				UpdateSystem(FIRE_UPDATE);
			}
		}
		else if( System.Serial.enRxStatus EQ RX_TIMEOUT)
		{
			System.AppStruct.bitResponseSemaphore = UNLOCKED;   
		}  	
	}
}


//........................................................
//........................................................ 
void UpdateSystem(UC ucmUpdateType)
{
	if(ucmUpdateType EQ FIRE_UPDATE)
	{
		FIRE_LED 	= TRUE;
		FIRE_RELAY	= TRUE;		
	}
	else if(ucmUpdateType EQ ACCEPT_UPDATE)
	{
		FIRE_LED 	= TRUE;		
		FIRE_RELAY	= FALSE;		 
	}
}


void Test()
{
 
}