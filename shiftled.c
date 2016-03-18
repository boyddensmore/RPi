#include <wiringPi.h>
#include <stdio.h>

#define SDI		0 //Serial data input
#define RCLK	1 //Memory clock input (STCP)
#define SRCLK	2 //Shift register clock input

#define ButtonPin	25
#define BeepPin		22

#define ShiftReg()	pulse(SRCLK)
#define CommitReg()	pulse(RCLK)

unsigned char LED[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void pulse(int pin)
{
	digitalWrite(pin, 0);
	digitalWrite(pin, 1);
}

void SIPO(unsigned char byte)
{
	int i;
	
	for (i=0; i<8; i++){
		digitalWrite(SDI, ((byte & (0x80 >> i)) > 0));
		pulse(SRCLK);
	}
}

void BlinkFirst(void)
{
	int i;
	
	for (i=0; i<7; i++){
		digitalWrite(SDI, 0);
		pulse(SRCLK);
	}
	digitalWrite(SDI, 1);
	pulse(SRCLK);
	//~ digitalWrite(BeepPin, LOW);
	
	pulse(RCLK);
	
	delay(150);
	
	for (i=0; i<8; i++){
		digitalWrite(SDI, 0);
		pulse(SRCLK);
	}
	
	//~ digitalWrite(BeepPin, HIGH);
	pulse(RCLK);
	
}

void init(void)
{
	pinMode(SDI, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(SRCLK, OUTPUT);
	pinMode(ButtonPin, INPUT);
	//~ pinMode(BeepPin, OUTPUT);
	
	//~ digitalWrite(BeepPin, HIGH);
	pullUpDnControl(ButtonPin, PUD_UP);
	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

int main(void)
{
	int i;
	
	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("Setup wiringPi failed!");
		return 1;
	}
	
	init();
	
	printf("Running... ");
	
	while (1){
		
		if (digitalRead(ButtonPin))
		{
			BlinkFirst();
			delay(150);
		}else
		{
			for (i=0; i<8; i++){
				SIPO(LED[i]);
				pulse(RCLK);
				delay(150);
				//~ printf("i: %d\n", i);
			}
			
			for (i=0; i<3; i++){
				SIPO(0xff);
				pulse(RCLK);
				delay(100);
				SIPO(0x00);
				pulse(RCLK);
				delay(100);
			}
			
			delay(500);
			
			for (i=0; i<8; i++){
				SIPO(LED[8-i-1]);
				pulse(RCLK);
				delay(150);
			}
			
			delay(500);
			
			for (i=0; i<3; i++){
				SIPO(0xff);
				pulse(RCLK);
				delay(100);
				SIPO(0x00);
				pulse(RCLK);
				delay(100);
			}
			
			delay(500);
		}
	}
	
	return 0;
}
