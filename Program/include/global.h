#ifndef __SYSTEM_GLOBAL__
#define __SYSTEM_GLOBAL__
//All required header files

#include <reg51.h>
#include "app/typedef.h"

#include "board/arch.h" 
//#include "board/7segdisp.h"
#include "board/serial.h"
#include "board/interrupt.h"
#include "board/io.h"
#include "board/keypad.h"

#include "app/app_keypad.h"
#include "app/app.h" 

//-------------------------------

//void MyFunc(UCP);

#define NULL				0
#define TRUE 				1
#define FALSE 				0
#define EQ					==
#define NEQ					!=
#define GTE					>=
#define LTE					<=
#define GT					>
#define LT					<
#define AND					&&
#define OR					||
#define VALUE_AT_ADDRESS	*
#define LOCKED				1
#define UNLOCKED			0

//Global System Structure
typedef struct
{
//	TagSegDisp 		SegDisp;
	TagSerial		Serial;
	TagQueryStruct	QueryStruct;
	TagQueryStruct	ResponseStruct;
	TagKeyStruct	KeyStruct;
	TagAppStruct 	AppStruct;
}TagSystem;

extern TagSystem System;

void SystemBoot();
void Delay(US usmDelay);

#endif/* __SYSTEM_GLOBAL__ */