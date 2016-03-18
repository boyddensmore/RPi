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
#define ledDelay	50



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

	ledInit();
	
	while(1){
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
				ledColorSet(0x7d,0x00,0x00);   //red
				delay(ledDelay);
				ledColorSet(0x00,0x7d,0x00);   //green
				delay(ledDelay);
				ledColorSet(0x00,0x00,0x7d);   //blue
				delay(ledDelay);
				ledColorSet(0x7d,0x7d,0x00);   //yellow
				delay(ledDelay);
				ledColorSet(0xff,0x00,0xff);   //pink
				delay(ledDelay);
				ledColorSet(0xc0,0xff,0x3e);
				delay(ledDelay);
				ledColorSet(0x94,0x00,0xd3);
				delay(ledDelay);
				ledColorSet(0x00,0xc5,0xcd);
				delay(ledDelay);
			break;
		}
		
	}

	return 0;
}
