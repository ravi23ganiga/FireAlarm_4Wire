#include "global.h"

void DispInit()
{
	DISP = 0x00;
	System.SegDisp.DispLookUpTable[0] = 0x00;
	System.SegDisp.DispLookUpTable[1] = 0x80;
	System.SegDisp.DispLookUpTable[2] = 0x10;
	System.SegDisp.DispLookUpTable[3] = 0x90;
	System.SegDisp.DispLookUpTable[4] = 0x20;
	System.SegDisp.DispLookUpTable[5] = 0xA0;
	System.SegDisp.DispLookUpTable[6] = 0x30;
	System.SegDisp.DispLookUpTable[7] = 0xB0;
	System.SegDisp.DispLookUpTable[8] = 0x40;
	System.SegDisp.DispLookUpTable[9] = 0xC0;

	System.SegDisp.DispLookUpTable[10] = 0x00;
	System.SegDisp.DispLookUpTable[11] = 0x08;
	System.SegDisp.DispLookUpTable[12] = 0x01;
	System.SegDisp.DispLookUpTable[13] = 0x09;
	System.SegDisp.DispLookUpTable[14] = 0x02;
	System.SegDisp.DispLookUpTable[15] = 0x0A;
	System.SegDisp.DispLookUpTable[16] = 0x03;
	System.SegDisp.DispLookUpTable[17] = 0x0B;
	System.SegDisp.DispLookUpTable[18] = 0x04;
	System.SegDisp.DispLookUpTable[19] = 0x0C;

	System.SegDisp.Disp[0] = 0;
	System.SegDisp.Disp[1] = 0;
	SegDisp1(0);
	SegDisp2(0);
}

void SegDisp1(UC ucmDispChar)
{
	System.SegDisp.Disp[0] = ucmDispChar;
	DISP = 	(System.SegDisp.DispLookUpTable[System.SegDisp.Disp[0]] | System.SegDisp.DispLookUpTable[System.SegDisp.Disp[1]]);
}

void SegDisp2(UC ucmDispChar)
{
	System.SegDisp.Disp[1] = 10 + ucmDispChar;
	DISP = 	(System.SegDisp.DispLookUpTable[System.SegDisp.Disp[0]] | System.SegDisp.DispLookUpTable[System.SegDisp.Disp[1]]);
}

void SegDispClear()
{
	SegDisp1(0);
	SegDisp2(0);
}