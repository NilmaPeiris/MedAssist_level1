/*
 * Menu.c
 *
 * Created: 12/12/2019 9:54:04 AM
 *  Author: Johan Perera
 */ 

#include "menu.h"
#include "CPU_Init.h"
#include "numberpad.h"
#include "DS3231.h"
/*---------------DS3231-----------------*/
	char buffer[20];
	char* days[7]= {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
/*-----------------------------------*/
char phoneNumber[12] = "94770745678";
 
void Menu(){
	
	char c;
	
	
	Lcd4_Set_Cursor(2,3);
	Lcd4_Write_String("1.DOSE SCHEDULE");
	Lcd4_Set_Cursor(3,3);
	Lcd4_Write_String("2.DOSE SETTINGS");
	Lcd4_Set_Cursor(4,3);
	Lcd4_Write_String("3.SYSTEM SETTINGS");
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("SELECT OPTION");
	_delay_us(50);
	
	c = numberpressed();
	
	if(c=='1'){
		Lcd4_Clear();
		schedule();
	}else if(c=='2'){
		Lcd4_Clear();
		doseSet();
	}else if(c=='3'){
		Lcd4_Clear();
		sysSet();
	}else{
		Menu();
	}
}


void schedule(){
	
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("DOSE SCHEDULE");
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("T1  08:00");
	Lcd4_Set_Cursor(3,2);
	Lcd4_Write_String("T2  08:00");
	Lcd4_Set_Cursor(4,2);
	Lcd4_Write_String("T3  10:00");
	
	_delay_ms(10);
	char c = numberpressed();
	if(c=='*'){
		Lcd4_Clear();
		Menu();
		}else{
		schedule();
	}
	
	
}

void doseSet(){
	int count=0;
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("DOSE SETTINGS");
	
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("Drug Count - ");
	
	char c = numberpressed();
	_delay_ms(10);
	if(c=='*'){
		Lcd4_Clear();
		Menu();
		}else if(c!='N'){
		count = atoi(c);
		Lcd4_Set_Cursor(3,9);
		Lcd4_Write_Char(c);
		_delay_ms(1000);
		int i=0;
		while(i<count){
			Lcd4_Clear();
			doseTime(i);
			i++;
		}
		}else{
		doseSet();
	}
}

void doseTime(int i){
	char chInt;
	itoa(i,&chInt,10);
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Type -:");
	Lcd4_Write_String(chInt);
	Lcd4_Set_Cursor(3,2);
	Lcd4_Write_String("1.Day");
	Lcd4_Set_Cursor(4,2);
	Lcd4_Write_String("2.Hour");
	char c=numberpressed();
	if(c=='*'){
		doseSet(i);
		}else if(c=='1'){
		Lcd4_Clear();
		doseDay(i);
		}else if(c=='2'){
		Lcd4_Clear();
		doseHour(i);
		}else{
		doseTime(i);
	}
}

void doseDay(int i){
	int mrn,afr,ngt;
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Day Dose -:");
	Lcd4_Set_Cursor(3,2);
	Lcd4_Write_String("Morning  ");
	_delay_ms(10);
	char ch = numberpressed();
	if(ch=='*'){
		doseTime(i);			//under construction
		}else if(ch!='N'){
		mrn=atoi(&ch);
		_delay_ms(1000);
		while(1){
			_delay_ms(10);
			ch=numberpressed();
			if(ch!='N'){
				afr=atoi(&ch);
				_delay_ms(1000);
				while(1){
					_delay_ms(10);
					ch=numberpressed();
					if(ch!='N'){
						ngt=atoi(&ch);
						_delay_ms(1000);
						break;
					}
				}
				break;
			}
		}
		
		}else{
		doseDay(i);
	}
	
}

void doseHour(){
	
}

void sysSet(){
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("SYSTEM SETTINGS");
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("1.MESSAGE SETTINGS");
	Lcd4_Set_Cursor(3,2);
	Lcd4_Write_String("2.TIME AND DATE");
	char c= numberpressed();
	_delay_ms(10);
	if(c=='1'){
		Lcd4_Clear();
		msgSet();
		}else if(c=='2'){
		Lcd4_Clear();
		rtc();
		}else if(c=='*'){
		Lcd4_Clear();
		Menu();
		}else{
		sysSet();
	}
}



void rtc(){
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("DATE AND TIME");
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String("1.SET DATE");
	Lcd4_Set_Cursor(3,0);
	Lcd4_Write_String("2.SET TIME");
	char c = numberpressed();
	_delay_ms(10);
	if(c=='*'){
		Lcd4_Clear();
		sysSet();
		}else if(c=='1'){
		Lcd4_Clear();
		setDate();
		}else if(c=='2'){
		Lcd4_Clear();
		setTime();
		}else{
		rtc();
	}
}



void setDate(){
	
}




void msgSet(){
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("MESSAGE SETTINGS");
	Lcd4_Set_Cursor(2,0);
	Lcd4_Write_String("1.EMERGENCY NUMBER");
	char c = numberpressed();
	if(c=='*'){
		Lcd4_Clear();
		Menu();
	}else if(c=='1'){
		Lcd4_Clear();
		emergNum();
	}else{
		msgSet();
	}
}



void setTime(){
	int hr,mn,sc,start,c;
	char chr;
	char buffer[20];
	
	
	start = 2;
	Lcd4_Set_Cursor(1,3);
	Lcd4_Write_String("SET TIME -> ");
	Lcd4_Set_Cursor(3,start);
	
	sc=retSec();
	mn=retMin();
	hr=retHour();
	RTC_Read_Clock(0);
	sprintf(buffer, "%02x:%02x:%02x  ", hr, mn, sc);
	
	Lcd4_Write_String(buffer);
	
	int i=0;
	while(1){
		if(i>7){
			break;
		}
		if(i==2 || i==5){
			i++;
			continue;
		}
		chr = numberpressed();
		_delay_ms(10);		
		if(chr!='N'){
			c = atoi(&chr);
			Lcd4_Set_Cursor(3,start+i);
			Lcd4_Write_Char(chr);
			_delay_ms(500);
			if(i==0){
				hr=16*c;
			}else if(i==1){
				hr+=c;
			}else if(i==3){
				mn=16*c;
			}else if(i==4){
				mn+=c;
			}else if(i==6){
				sc=16*c;
			}else if(i==7){
				sc+=c;
			}
			i++;
		}
	}
	RTC_Clock_Write(hr,mn,sc,hour_24);
	_delay_ms(3000);
}




void emergNum(){
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("Enter the Mobile Number ->");
	Lcd4_Set_Cursor(3,1);
	Lcd4_Write_Char('+');
	Lcd4_Write_String(phoneNumber);
	Lcd4_Set_Cursor(3,2);
	char c;
	int i=0;
	char number[12];
	number[1] = '+';
	while(i<11){
		c= numberpressed();
		_delay_ms(30);
		if(c=='*'){
			msgSet();
		}
		if(c!='N'){
			Lcd4_Write_Char(c);
			number[i]=c;
			i++;
			_delay_ms(500);
		}
	}
	memcpy(phoneNumber,number, strlen(number)+1);
	msgSet();
	Lcd4_Clear();
}
