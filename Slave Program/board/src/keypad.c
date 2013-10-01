#include "global.h"

//----------------------------------------------------
//4 x 3 Keypad
//------------------------------------------------------

TagenKeyType ucmKeyPad[4][3] = {
								 ///   P1.3   // P1.2 // P1.1 //////// 
								///     ||   //  ||  //  ||  ////////	
								/////////////////////////////////////
					/* P1.4 */	/**/    ONE   ,  TWO  , THREE , /**/
					/* P1.5 */	/**/	FOUR  , FIVE  , SIX   ,	/**/
					/* P1.6 */	/**/	SEVEN , EIGHT , NINE  ,	/**/
					/* P1.7 */	/**/	ENTER , ZERO  , CALLALL /**/
								////////////////////////////////////
				 			};
//-----------------------------------------------
void KeypadInit()
{
	KEYPAD = 0xFF;
	System.KeyStruct.ucmRowNo = 0;
}

TagenKeyType KeyScan()
{
	TagenKeyType enCurrKey;	
	switch(System.KeyStruct.ucmRowNo)
	{
		case 0:
			ROW1 = 0; 
			break;

		case 1:
			ROW2 = 0;
			break;

		case 2:
			ROW3= 0;
			break;

		case 3:
			ROW4 = 0;
			break;

		default:
			return NOKEY;
			break;
	}		
	if(COL1 EQ KEY_PRESS)
	{
		enCurrKey =  ucmKeyPad[System.KeyStruct.ucmRowNo][0];
	}
	else if(COL2 EQ KEY_PRESS)
	{
		enCurrKey =  ucmKeyPad[System.KeyStruct.ucmRowNo][1];
	}
	else if(COL3 EQ KEY_PRESS)
	{
		enCurrKey =  ucmKeyPad[System.KeyStruct.ucmRowNo][2];
	}
	else
	{
		enCurrKey =  NOKEY;
	}
	KEYPAD = 0xFF;
	System.KeyStruct.ucmRowNo++;
	if(System.KeyStruct.ucmRowNo >= ROW_MAX)
	{
		System.KeyStruct.ucmRowNo = 0;
	}
	return enCurrKey;
}
