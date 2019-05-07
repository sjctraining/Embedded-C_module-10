#include<reg51.h>

void main()
{
    char str[] = "Comorin";
	  char *cp = str;

	  SCON = 0x40;      // UART Mode 1
    TMOD = 0x20;      // Timer 1 in mode 2
    TH1  = 0xFD;      // Baud Rate 9600
	
    TR1 = 1;
		
	  while(*cp)
		{
			  SBUF = *cp++;
			  while (!TI);  // Wait until TI becomes 1
			  TI = 0;
		}
		
    while(1);
}