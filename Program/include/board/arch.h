#ifndef __FIRE_ARCH__
#define __FIRE_ARCH__
//All Port and hardware related declaration

//7 Segment Display related variables
sfr DISP 			= 0xA0;

//LED related variables

sbit FIRE_LED 		=  P3^2;

sbit FIRE_RELAY 	= P3^3;	
 
sbit SYSTEM_START 	= P3^4;

sbit MAX485_TX		= P3^5;

//All switch related variables


//Keypad related variable

sfr KEYPAD = 0x90;

sbit ROW1 = KEYPAD^0;
sbit ROW2 = KEYPAD^1;
sbit ROW3 = KEYPAD^2;
sbit ROW4 = KEYPAD^3;
sbit COL1 = KEYPAD^4;
sbit COL2 = KEYPAD^5;
sbit COL3 = KEYPAD^6;
sbit ACCEPT_SW = KEYPAD^7;

#endif /* __FIRE_ARCH__ */