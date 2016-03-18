#include <wiringPi.h>
#include <stdio.h>

#define LedPin	6

int main(void)
{
	//~ printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	if(wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("Setup wiringPi failed!");
		return 1;
	}
	printf("linker LedPin: GPIO %d(wiringPi pin)\n", LedPin); //Initialize wiring successful

	pinMode(LedPin, OUTPUT);

	while(1){
		digitalWrite(LedPin, LOW); //led on
		printf("led on... \n");
		delay(500);
		digitalWrite(LedPin, HIGH); //led off
		printf("... led off\n");
		delay(500);
	}

	return 0;
}
