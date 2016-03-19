#include <wiringPi.h>
#include <stdio.h>


#define uchar unsigned char
  
#define HookPin	 	29
#define DialPin	 	25
#define DialingPin	24


int main(void)
{
	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("Setup wiringPi failed!");
		return 1;
	}

	int dropCount = 0;

	pinMode(DialPin, INPUT);
	pinMode(DialingPin, INPUT);
	pinMode(HookPin, INPUT);
	
	pullUpDnControl(DialPin, PUD_UP);
	pullUpDnControl(DialingPin, PUD_UP);
	pullUpDnControl(HookPin, PUD_UP);
	
	while(1){
		while(digitalRead(HookPin) == 0){
			printf("Off Hook\n");
			while (digitalRead(DialingPin) == 0) {
				printf("Dialing\n");
				while (digitalRead(DialPin) == 1 && digitalRead(HookPin) == 0) {
					delay(1);
				}
				while (digitalRead(DialPin) == 0 && digitalRead(HookPin) == 0) {
					delay(1);
				}
				dropCount ++;
			}
			printf("dropCount: %d\n", dropCount);
		}
		printf("On Hook\n");
		dropCount = 0;
		
		//~ printf("DR DialingPin: %d\n", digitalRead(DialingPin));
	}
	

	return 0;
}
