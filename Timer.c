#include<reg51.h>
sbit red   = P3^6;        // Red LED is used to show the switch status
sbit green = P3^7;        // Green LED is made to blink every 50ms
sbit sw    = P3^0;        // Pin 0 of port 3 is connected to a switch

void timer0()interrupt 1  // Interrupt Handler for Timer 0
{
    green = !green;       // Switches between on and off
	  TH0   = 0x4C;         // High value for 50ms delay
	  TL0   = 0x00;         // Low value for 50ms delay
}

void main()
{
    TMOD = 0x01;          // Timer 0 in mode 1, 16-Bit timer
	  TH0  = 0x4C;          // High value for 50ms delay
	  TL0  = 0x00;          // Low value for 50ms delay
	  IE   = 0x82;          // Enable interrupts EA and ET0

	  TR0  = 1;             // Turn on Timer
	  
	  while(1)
		{
			  red = sw;         // Assign the switch status to RED LED
		}
}