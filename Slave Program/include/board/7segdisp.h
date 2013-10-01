
#ifndef __7SEG_DISP__
#define __7SEG_DISP__
//structure related to seven segment display

typedef struct
{
	UC DispLookUpTable[20];
	UC Disp[2];
}TagSegDisp;

//Functions related to seven segment display

void DispInit();
void SegDisp1(UC);
void SegDisp2(UC);
void SegDispClear();

#endif /* __7SEG_DISP__ */