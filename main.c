#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif
#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTA0
#define D5 eS_PORTA1
#define D6 eS_PORTA2
#define D7 eS_PORTA3
#define RS eS_PORTA4
#define EN eS_PORTA5
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include "lcd.h"
unsigned char keypad();
int main(void)
{
	DDRL=0X0F;
	DDRA = 0xFF;
	Lcd4_Init();
	Lcd4_Clear();
	unsigned char c;
	while (1)
	{
		PORTL=0xF0;
		if(PINL!=0xF0 )
		{
			c=keypad();
			if (c !='=' && c!='-')
			{
				Lcd4_Write_Char(c);
			}
			if (c =='-')
			{
				Lcd4_Clear(); 
			}
			else if (c=='=')
			{
				Lcd4_Set_Cursor(2,0);
			}
			
			_delay_ms(250);
		}
	}
	return 0;
}
unsigned char keypad()
{
	PORTL=0b11111110;
	if ((PINL & (1<<4))==0)
	{
		_delay_ms(3); return '7';
	}
	else if ((PINL & (1<<5))==0)
	{
		_delay_ms(3); return '8';
	}
	else if ((PINL & (1<<6))==0)
	{
		_delay_ms(3); return '9';
	}
	PORTL=0b11111101;
	if ((PINL & (1<<4))==0)
	{
		_delay_ms(3); return '4';
	}
	else if ((PINL & (1<<5))==0)
	{
		_delay_ms(3); return '5';
	}
	else if ((PINL & (1<<6))==0)
	{
		_delay_ms(3); return '6';
	}
	PORTL=0b11111011;
	if ((PINL & (1<<4))==0)
	{
		_delay_ms(3); return '1';
	}
	else if ((PINL & (1<<5))==0)
	{
		_delay_ms(3); return '2';
	}
	else if ((PINL & (1<<6))==0)
	{
		_delay_ms(3); return '3';
	}
	PORTL=0b11110111;
	if ((PINL & (1<<5))==0)
	{
		_delay_ms(3); return '0';
	}
	else if ((PINL & (1<<6))==0)
	{
		_delay_ms(3); return '=';
	}
	else if ((PINL & (1<<4))==0)
	{
		_delay_ms(3); return '-';
	}
}
