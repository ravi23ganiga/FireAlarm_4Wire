#ifndef __FIRE_ARCH__
#define __FIRE_ARCH__
//All Port and hardware related declaration
 
//Relay pin
sbit FIRE_RELAY = P3^7; 

//Fire Led
sbit FIRE_LED = P1^7;

//Fire Pin
sbit FIRE_SWITCH = P3^2;

//Fire Sensor
sbit FIRE_SENSOR = P3^3;

//Max485 pins

sbit MAX485_TX = P3^4;  

//No switch port
sfr NO_SWITCH = 0x90;

#endif /* __FIRE_ARCH__ */