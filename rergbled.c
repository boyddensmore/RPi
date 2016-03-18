#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define uchar unsigned char
#define LedPinRed   27
#define LedPinGreen 28
#define LedPinBlue  29
#define RoAPin		0
#define RoBPin		1
#define ledDelay	50

static volatile int globalCounter = 0;

unsigned char flag;
unsigned char Last_RoB_Status;
unsigned char Current_RoB_Status;

void rotaryDeal(void)
{
	Last_RoB_Status = digitalRead(RoBPin);
	
	while(!digitalRead(RoAPin)){
		Current_RoB_Status = digitalRead(RoBPin);
		flag = 1;
	}
	
	if(flag == 1) {
		flag = 0;
		if((Last_RoB_Status == 0) && (Current_RoB_Status == 1)){
			globalCounter ++;
		}
		if((Last_RoB_Status == 1) && (Current_RoB_Status == 0)){
			globalCounter --;
		}
	}
}

void ledInit(void)
{
	//~ printf("ledInit");
    softPwmCreate(LedPinRed,  0, 100);
    softPwmCreate(LedPinGreen,0, 100);
    softPwmCreate(LedPinBlue, 0, 100);
}
  
void ledColorSet(uchar r_val, uchar g_val, uchar b_val)
{
	//~ printf("ledColorSet");
    softPwmWrite(LedPinRed,   r_val);
    softPwmWrite(LedPinGreen, g_val);
    softPwmWrite(LedPinBlue,  b_val);
}

int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("Setup wiringPi failed!");
		return 1;
	}
	//~ printf("linker LedPin: GPIO %d(wiringPi pin)\n", LedPin); //Initialize wiring successful

	pinMode(RoAPin, INPUT);
	pinMode(RoBPin, INPUT);

	ledInit();
	
	while(1){
		rotaryDeal();
		//~ printf("globalCounter: %d\n", globalCounter);
		//~ printf("globalCounter: %d\n", abs(globalCounter));
		//~ printf("globalCounter: %d\n", abs(globalCounter)%9);
		
		
		
		switch(abs(globalCounter)%9){
			case 0: ledColorSet(0x00,0x00,0x00);   //off
				printf("Off\n");
			break;
			case 1: ledColorSet(0x7d,0x00,0x00);   //red
				printf("Red\n");
			break;
			case 2: ledColorSet(0x00,0x7d,0x00);   //green
				printf("Green\n");
			break;
			case 3: ledColorSet(0x00,0x00,0x7d);   //blue
				printf("Blue\n");
			break;
			case 4: ledColorSet(0x7d,0x7d,0x00);   //yellow
				printf("Yellow\n");
			break;
			case 5: ledColorSet(0xff,0x00,0xff);   //pink
				printf("Pink\n");
			break;
			case 6: ledColorSet(0xc0,0xff,0x3e);
				printf("Colour 6\n");
			break;
			case 7: ledColorSet(0x94,0x00,0xd3);
				printf("Colour 7\n");
			break;
			case 8: 
				printf("Rainbow Confetti!\n");
				ledColorSet(0x00,0x00,0x00);   //off
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0x7d,0x00,0x00);   //red
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0x00,0x7d,0x00);   //green
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0x00,0x00,0x7d);   //blue
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0x7d,0x7d,0x00);   //yellow
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0xff,0x00,0xff);   //pink
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0xc0,0xff,0x3e);
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0x94,0x00,0xd3);
				delay(ledDelay);
				rotaryDeal();
				ledColorSet(0x00,0xc5,0xcd);
				delay(ledDelay);
				rotaryDeal();
			break;
		}
		
		
		
	}
	

	return 0;
}
