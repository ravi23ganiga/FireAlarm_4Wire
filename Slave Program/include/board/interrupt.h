#ifndef __INTERRUPT__
#define __INTERRUPT__

void InterruptInit();
void msecInterruptStart();
void msecInterruptStop();
void SerialInterrupt();
void TimerInterrupt();
void ExternalInterrupt0();
void ExternalInterrupt1();

#endif /* __INTERRUPT__ */