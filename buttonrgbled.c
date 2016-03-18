#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

#define LedPin	6

#define uchar unsigned char
  
#define LedPinRed    27
#define LedPinGreen  28
#define LedPinBlue   29
#define ButtonPin	 25

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

	//~ pinMode(LedPin, OUTPUT);
	pinMode(ButtonPin, INPUT);
	
	pullUpDnControl(ButtonPin, PUD_UP);
	
	while(1){
		//~ digitalWrite(LedPin, HIGH);
		ledColorSet(0x00,0x00,0x00);   //off
		if(digitalRead(ButtonPin) == 0){
			ledColorSet(0x7d,0x00,0x00);   //red
			delay(ledDelay);
			
			ledColorSet(0x00,0x7d,0x00);   //green
			delay(ledDelay);
			
			ledColorSet(0x00,0x00,0x7d);   //blue
			delay(ledDelay);
			
			ledColorSet(0x7d,0x7d,0x00);   //yellow
			delay(ledDelay);
			
			ledColorSet(0xff,0x00,0xff);   //pick
			delay(ledDelay);
			
			ledColorSet(0xc0,0xff,0x3e);
			delay(ledDelay);
			
			ledColorSet(0x94,0x00,0xd3);
			delay(ledDelay);
			
			ledColorSet(0x00,0xc5,0xcd);
			delay(ledDelay);
		}
	}
	

	return 0;
}
