/*
 * functionMCU.c
 *
 * Created: 12/11/2019 6:30:03 PM
 * Author : Johan Perera
 */ 

/*---------------LCD-----------------*/
#ifndef D4
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7
#endif
/*-----------------------------------*/
#include "CPU_Init.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "menu.h"
#include <avr/interrupt.h>
#include "I2C_Master_H_file.h"
#include "DS3231.h"
#include <stdio.h>



int main(void)
{
    /* Replace with your application code */
	DDRD = 0xF7;		//	0,1-GSM		3-Emerge Button		4,5,6,7-LCD
	DDRC = 0xFC;        //	6,7-LCD		0,1-RTC
	DDRA = 0xF0;		//	Numberpad
	
	PORTA = 0x00;
	
	Lcd4_Init();
	Lcd4_Clear();
	Lcd4_Set_Cursor(2,4);
	Lcd4_Write_String("Med Assist!");
	_delay_ms(1000);
	
	//----------------Interrupt for Emergency Button-----------------
	TCCR0 = 0x01;
	TIMSK=0x01;
	sei();
	//----------------RTC Module--------------------
	I2C_Init();
	
	//RTC_Clock_Write(0x23, 0x40, 0x00, hour_24);/* Write Hour Minute Second Format */
	//RTC_Calendar_Write(0x07, 0x31, 0x12, 0x16);	/* Write day date month and year */
	
		
    while (1) 
    {
		
		Lcd4_Clear();
		Menu();
			
    }
}

void sendMsg(){
	//GSM Code
	Lcd4_Clear();
	_delay_ms(1);
	Lcd4_Set_Cursor(2,3);
	Lcd4_Write_String("Sending");
	for(int i=0;i<5;i++){
		Lcd4_Set_Cursor(2,10);
		_delay_ms(300);
		Lcd4_Write_Char('.');
		_delay_ms(300);
		Lcd4_Write_Char('.');
		_delay_ms(300);
		Lcd4_Write_Char('.');
		Lcd4_Set_Cursor(2,10);
		Lcd4_Write_Char(0x08);
		Lcd4_Write_Char(0x08);
		Lcd4_Write_Char(0x08);	
	}
	Lcd4_Clear();
	Lcd4_Set_Cursor(2,3);
	Lcd4_Write_String("Done");
	_delay_ms(1000);
	main();
}

ISR(TIMER0_OVF_vect){
	if(PIND & (1<<PD3)){
		while (PIND & (1<<PD3))
		{
			continue;
		}
		sendMsg();
	}
}


