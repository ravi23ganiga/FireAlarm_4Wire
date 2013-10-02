#include "global.h"

void DispInit()
{
	DISP1 = 0x00;
	DISP2 = 0x00;
 
	System.SegDisp.DispLookUpTable[0] = 0xC0;
	System.SegDisp.DispLookUpTable[1] = 0xF9;
	System.SegDisp.DispLookUpTable[2] = 0xA4;
	System.SegDisp.DispLookUpTable[3] = 0xB0;
	System.SegDisp.DispLookUpTable[4] = 0x99;
	System.SegDisp.DispLookUpTable[5] = 0x92;
	System.SegDisp.DispLookUpTable[6] = 0x82;
	System.SegDisp.DispLookUpTable[7] = 0xF8;
	System.SegDisp.DispLookUpTable[8] = 0x80;


	SegDispClear();
}

void SegDisp1(UC ucmDispChar)
{
	DISP1 = System.SegDisp.DispLookUpTable[ucmDispChar];
}

void SegDisp2(UC ucmDispChar)
{
	DISP2 = System.SegDisp.DispLookUpTable[ucmDispChar];
}

void SegDispClear()
{
	SegDisp1(0);
	SegDisp2(0);
}