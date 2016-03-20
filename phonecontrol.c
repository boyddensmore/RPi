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
	int dialedNumberLength = 11;
	int dialedNumber [dialedNumberLength];
	int dialNumberIndex = 0;
	int dialConfirmation = 0;
	int x = 0;

	pinMode(DialPin, INPUT);
	pinMode(DialingPin, INPUT);
	pinMode(HookPin, INPUT);
	
	pullUpDnControl(DialPin, PUD_UP);
	pullUpDnControl(DialingPin, PUD_UP);
	pullUpDnControl(HookPin, PUD_UP);
	
	while(1){
		while(digitalRead(HookPin) == 1){
		}
		
		//~ printf("HookPin: %d\n", digitalRead(HookPin));
		printf("Off Hook.\n");
	
		while(digitalRead(HookPin) == 0 && dialNumberIndex < dialedNumberLength){

			while (digitalRead(DialingPin) == 1 && digitalRead(HookPin) == 0) {
			}
			
			while (digitalRead(DialingPin) == 0) {
				//~ printf("DialingPin: %d\n", digitalRead(DialingPin));
				//~ printf("dropCount: %d\n", dropCount);
				while (digitalRead(DialPin) == 1 && digitalRead(HookPin) == 0 && digitalRead(DialingPin) == 0) {
					delay(1);
					dialConfirmation = 1;
				}
				while (digitalRead(DialPin) == 0 && digitalRead(HookPin) == 0 && digitalRead(DialingPin) == 0) {
					delay(1);
					dialConfirmation = 2;
				}
				dropCount ++;
			}
			
			if (dialConfirmation == 2) {
			
				dropCount = (dropCount - 1) % 10;
				
				//~ printf("dropCount: %d\n", dropCount);
				dialedNumber[dialNumberIndex] = dropCount;
				printf("Dialed Number: ");
				for (x = 0; x <= dialNumberIndex; x++) {
					printf("%d", dialedNumber[x]);
				}
				printf("\n");
				
				dialNumberIndex ++;
			}
			else {
				printf("----------Bad Dial----------\n");
			}

			dropCount = 0;
			dialConfirmation = 0;
		}
		
		if (dialNumberIndex >= dialedNumberLength) {
			printf("...Dialing ");
			for (x = 0; x < dialedNumberLength; x++) {
				printf("%d", dialedNumber[x]);
			}
			printf("...\n");
		}
		
		if (digitalRead(HookPin) == 1){
			printf("Hung Up.\n");
		}
		
		
		dropCount = 0;
		dialNumberIndex = 0;
		dialConfirmation = 0;
	}

	return 0;
}
