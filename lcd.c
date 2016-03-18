#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <lcd.h>

const unsigned char Buf[] = " I LOVE YOU LEAH";
const unsigned char MyBuf[] = "   -From Boyd.  ";

#define ButtonPin	 25

int main(void)
{
	int fd;
	int i;
	
	if (wiringPiSetup() == -1){
		exit(1);
	}
	
	fd = lcdInit(2,16,4, 15,16, 0,1,2,3,4,5,6,7); //see /usr/local/include/lcd.h
	if (fd == -1){
		printf("lcdInit 1 failed\n");
		return 1;
	}
	
	pinMode(ButtonPin, INPUT);
	pullUpDnControl(ButtonPin, PUD_UP);
	
	delay(1000);
	
	lcdClear(fd);
	lcdPosition(fd, 0, 0);
	lcdPuts(fd, "Hello Boyd");
	
	lcdPosition(fd, 0, 1);
	lcdPuts(fd, "Some Pi?");
	
	delay(1000);
	
	lcdClear(fd);
	
	while(1){
		if(digitalRead(ButtonPin) == 0){
			for (i=1; i<sizeof(Buf)-1; i++){
				lcdPosition(fd, i, 0);
				lcdPutchar(fd, *(Buf+i));
				delay(200);
			}
			lcdPosition(fd, 0, 1);
			delay(500);
			
			for (i=0; i<sizeof(MyBuf)-1; i++){
				lcdPosition(fd, i, 1);
				lcdPutchar(fd, *(MyBuf+i));
				delay(100);
			}
			
			delay(500);
			lcdClear(fd);
		}
	}
	
	return 0;
}
