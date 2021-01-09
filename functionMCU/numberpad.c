#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "numberpad.h"



char numberpressed()
{
	PORTA = 0b10000000;
	if(PINA & (1<<PA0))
	{
		return 'a';
	}
	if(PINA & (1<<PA1))
	{
		return '3';
	}
	if(PINA & (1<<PA2))
	{
		return '2';
	}
	if(PINA & (1<<PA3))
	{
		return '1';
	}
	
	PORTA = 0b01000000;
	if(PINA & (1<<PA0))
	{
		return 'b';
	}
	if(PINA & (1<<PA1))
	{
		return '6';
	}
	if(PINA & (1<<PA2))
	{
		return '5';
	}
	if(PINA & (1<<PA3))
	{
		return '4';
	}
	PORTA = 0b00100000;
	if(PINA & (1<<PA0))
	{
		return 'c';
	}
	if(PINA & (1<<PA1))
	{
		return '9';
	}
	if(PINA & (1<<PA2))
	{
		return '8';
	}
	if(PINA & (1<<PA3))
	{
		return '7';
	}
	PORTA = 0b00010000;
	if(PINA & (1<<PA0))
	{
		return 'd';
	}
	if(PINA & (1<<PA1))
	{
		return '#';
	}
	if(PINA & (1<<PA2))
	{
		return '0';
	}
	if(PINA & (1<<PA3))
	{
		return '*';
	}
	
	return 'N';
}
