sfr P1 = 0x90;
sfr P2 = 0xA0;

sbit LCD_RS = P1^0;
sbit LCD_RW = P1^1;
sbit LCD_EN = P1^2;

sbit TR1  = 0x8E;
sfr TMOD = 0x89;
sfr TL1  = 0x8B;


void LCD_Cmd(unsigned char);
void LCD_Data(unsigned char);
void delay();

void main()
{   
			     
	  unsigned char ones, tens, counter;
	  
		P2 = 0x00;
		TR1 = 1;
		TMOD = 0x60;
		TL1 = 0x00;
	  counter = 0x00;
	
	  LCD_Cmd(0x38);  // set as dot matrix 5x7
	  LCD_Cmd(0x3C);
	  LCD_Cmd(0x01);  // clear screen
		LCD_Cmd(0x0F);  // Display on cursor blinking

		while(1)
		{
			   if ( counter == TL1 )
				 {
             continue;
				 }
				 
				 counter = TL1;
		     tens = counter / 10;
				 ones = counter % 10;
			
			   LCD_Cmd(0x01);  // clear screen
		     LCD_Data('0' + tens);
			   LCD_Data('0' + ones);
         				 
    }
}

void LCD_Cmd(unsigned char val)
{
    P2 = val;
	  LCD_RS = 0;
	  LCD_RW = 0;
	  LCD_EN = 1;
	  delay();
	  LCD_EN = 0;
}
void LCD_Data(unsigned char val)
{
	  P2 = val;
	  LCD_RS = 1;
	  LCD_RW = 0;
	  LCD_EN = 1;
	  delay();
	  LCD_EN = 0;
}

void delay()
{
	  unsigned int i;
	  for(i = 0; i <2000; i++);
}






