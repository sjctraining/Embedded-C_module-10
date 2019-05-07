#include<reg51.h>

void uart_msg(unsigned char*c); // Function to Transmit String from 8051 to virtual terminal
void uart_tx(unsigned char);    // Function to Transmit Data from 8051 to virtual terminal

sbit led1 = P1^0;               // LED 1 connected to pin 0 of Port 1
sbit led2 = P1^1;               // LED 2 connected to pin 1 of Port 1
sbit led3 = P1^2;               // LED 3 connected to pin 2 of Port 1
sbit led4 = P1^3;               // LED 4 connected to pin 3 of Port 1

void main()
{
    P1   = 0x00;                // Output Port used for LED's
    P3   = 0x03;                // Port 3 is used  for Serial Communication
    TMOD = 0x20;                // Timer 1 in Mode 2 Auto Reload 
    SCON = 0x50;                // Serial Mode 1, 8-Data Bit, REN Enabled
    TH1  = 0xFD;                // Load Baud Rate 9600 To Timer Register
    TR1  = 1;                   // Start Timer 1
	
  	uart_msg("Initialize serial communication\r");
    uart_msg("1,2,3,4 key can on leds and a,b,c,d can off them respectively...\r");
    uart_msg("Press the key for particular LED\r");
	
	  EA   = 1;                   // Enable Global Interrupt
	  ES   = 1;	                  // Enable Serial Interrupt
  	
		while(1);
}

void uart_msg(unsigned char *c)
{
    while(*c)                   // Iterate thru the String until it Reaches End of String ('\0')
		{
			  uart_tx(*c++);
		}
}

void uart_tx(unsigned char serialdata)
{
    SBUF = serialdata;          // Load Data to Serial Buffer Register
    while(!TI);                 // Wait Until Transmission To Complete
    TI   = 0;                   // Clear Transmission Interrupt Flag
}

void serial_ISR() interrupt 4   // Serial Interrupt in Mode 4
{
    char chr;
    if(!RI)
		{
			  return; 
		}
		
		chr = SBUF;
        
    switch(chr)
    {
        case '1':  led1 = 1; uart_msg("1st on\r"); break;
        case '2':  led2 = 1; uart_msg("2nd on\r"); break;
        case '3':  led3 = 1; uart_msg("3rd on\r"); break;
        case '4':  led4 = 1; uart_msg("4th on\r"); break;
        case 'a':  led1 = 0; uart_msg("1st off\r"); break;
        case 'b':  led2 = 0; uart_msg("2nd off\r"); break;
        case 'c':  led3 = 0; uart_msg("3rd off\r"); break;
        case 'd':  led4 = 0; uart_msg("4th off\r"); break;
		    default: uart_msg("key not supported...\r");	
    }
    RI = 0;
}