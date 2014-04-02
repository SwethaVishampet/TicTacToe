#include<REG51.h>


sbit enable= P0^0;
sbit write=  P0^1;
sbit rs= P0^2;

void delay()
{
int i=0;
for( i=0;i<20000;i++);
}

void lcd_command(unsigned char command)
{
    write=0;
	rs=0;
	P1 = command;
	enable=1;
	delay();
	enable=0;
}

void lcd_display(unsigned char command)
{
	write=0;
	rs=1;
	delay();
	P1=command;
	enable=1;
	delay();
	enable=0;
}


void main()
{
	lcd_command(0x38);
	delay();
	delay();
	delay();
	lcd_command(0x08);
	delay();
	delay();
	delay();
	lcd_command(0x01);
	delay();
	delay();
	delay();
	lcd_command(0x06);
	delay();
	delay();
	delay();
	lcd_command(0x0F);
	delay();
	delay();
	delay();

	lcd_display('A');
	lcd_display('I');
	lcd_display('S');
	lcd_display('H');
	lcd_display('!');

}


