sfr P1    = 0x90;                  // Seven Segment Display is connected to Port 1
sfr P2    = 0xA0;                  // Data lines connected to Port 2
sfr TMOD  = 0x89;                  // Address of TMOD on SFR
sfr TL1   = 0x8B;                  // Address of TL1 on SFR
sbit TR1  = 0x8E;                  // Address of TR1 on SFR
sbit com1 = P1^0;                  // Common Anode seven segment first Pin connected to P1.0
sbit com2 = P1^1;                  // Common Anode seven segment second Pin connected to P1.1

void main() 
{
    // Hexadecimal values for 0 to 9
	  unsigned char disp[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; 
	  unsigned char ones, tens;
		unsigned int i;
		com1 = com2 = 0;                // Initilaizing the common anode pins with 0
		P2   = 0x00;                    // Initializing the Port P2 Data lines with 0
		TMOD = 0x60;                    // Counter 1 Mode 2
		TL1  = 0x00;
		TR1  = 1;                       
		while(1)
		{
		     tens = TL1 / 10;           // Tens value of the Counter
				 ones = TL1 % 10 ;          // Ones value of the counter
				 com1 = 1; com2 = 0;        // Common Anode line 1 enabled and line 2 disabled
				 P2   = disp[tens];         // Displays the tens digit in Common Anode line 1
				 for (i = 0; i < 500; i++); // Delay
				 com1 = 0; com2 = 1;        // Common Anode line 1 disabled and line 2 enabled
				 P2   = disp[ones];         // Displays the ones digit in Common Anode line 2
				 for (i = 0; i < 500; i++); // Delay
				 com2 = 0;
    }
}	