/*
 * DS3231.h
 *
 * Created: 12/18/2019 6:19:50 PM
 *  Author: Johan Perera
 */ 


#ifndef DS3231_H_
#define DS3231_H_

#include <stdbool.h>

#define Device_Write_address	0xD0			/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1			/* Make LSB bit high of slave address for read operation */
#define hour_12_AM				0x40
#define hour_12_PM				0x60
#define hour_24					0x00

#define Device_Write_address	0xD0				/* Define RTC DS1307 slave address for write operation */
#define Device_Read_address		0xD1				/* Make LSB bit high of slave address for read operation */
#define TimeFormat12			0x40				/* Define 12 hour format */
#define AMPM					0x20



void RTC_Clock_Write(char _hour, char _minute, char _second, char AMPMdef);
void RTC_Calendar_Write(char _day, char _date, char _month, char _year);
bool IsItPM(char hour_);
void RTC_Read_Clock(char read_clock_address);
void RTC_Read_Calendar(char read_calendar_address);
int retSec();
int retMin();
int retHour();

#endif /* DS3231_H_ */