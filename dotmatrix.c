#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define SDI		0 //Serial data input
#define RCLK	1 //Memory clock input (STCP)
#define SRCLK	2 //Shift register clock input (Latch)

//~ #define RSDI	0 //Serial data input
//~ #define RRCLK	1 //Memory clock input (STCP)
//~ #define RSRCLK	2 //Shift register clock input (Latch)

//~ #define CSDI	23 //Serial data input
//~ #define CRCLK	24 //Memory clock input (STCP)
//~ #define CSRCLK	25 //Shift register clock input (Latch)

#define TouchPin	3

//~ #define RShiftReg()		pulse(RSRCLK)
//~ #define RCommitReg() 	pulse(RRCLK)
//~ #define CShiftReg()		pulse(CSRCLK)
//~ #define CCommitReg() 	pulse(CRCLK)

int CascPattern[16][16]= {{	0,1,1,1,1,1,1,1,
							1,0,0,0,0,0,0,0},
						//~ 1
						{	1,0,1,1,1,1,1,1,
							0,1,0,0,0,0,0,0},
						//~ 2
						{	1,1,0,1,1,1,1,1,
							0,0,1,0,0,0,0,0},
						//~ 3
						{	1,1,1,0,1,1,1,1,
							0,0,0,1,0,0,0,0},
						//~ 4
						{	1,1,1,1,0,1,1,1,
							0,0,0,0,1,0,0,0},
						//~ 5
						{	1,1,1,1,1,0,1,1,
							0,0,0,0,0,1,0,0},
						//~ 6
						{	1,1,1,1,1,1,0,1,
							0,0,0,0,0,0,1,0},
						//~ 7
						{	1,1,1,1,1,1,1,0,
							0,0,0,0,0,0,0,1},
						//~ 7
						{	1,1,1,1,1,1,1,0,
							0,0,0,0,0,0,0,1},
						//~ 6
						{	1,1,1,1,1,1,0,1,
							0,0,0,0,0,0,1,0},
						//~ 5
						{	1,1,1,1,1,0,1,1,
							0,0,0,0,0,1,0,0},
						//~ 4
						{	1,1,1,1,0,1,1,1,
							0,0,0,0,1,0,0,0},
						//~ 3
						{	1,1,1,0,1,1,1,1,
							0,0,0,1,0,0,0,0},
						//~ 2
						{	1,1,0,1,1,1,1,1,
							0,0,1,0,0,0,0,0},
						//~ 1
						{	1,0,1,1,1,1,1,1,
							0,1,0,0,0,0,0,0},
						//~ 0
						{	0,1,1,1,1,1,1,1,
							1,0,0,0,0,0,0,0}};
						//~ {	1,1,1,1,1,1,1,1,
							//~ 0,0,0,0,0,0,0,0}

char R = 1;
char C = 254;
unsigned char ShiftList[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char SegCode[6] = {0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d};
unsigned char flag = 0;

void pulse(int pin)
{
	digitalWrite(pin, 1);
	delay(1);
	digitalWrite(pin, 0);
}

void init(void)
{
	int i;
	
	pinMode(SDI, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(SRCLK, OUTPUT);
	
	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
	
	for (i=0; i<8; i++){
		digitalWrite(SDI, 1);
		pulse(SRCLK);
	}
	
	for (i=0; i<8; i++){
		digitalWrite(SDI, 0);
		pulse(SRCLK);
	}
	
	pulse(RCLK);
}

int main(void)
{
	int i;
	//~ int num;
	int n;
	//~ int c, r;
	
	if (wiringPiSetup() == -1){ //when initialize wiring failed, print message to screen
		printf("Setup wiringPi failed!");
		return 1;
	}
	
	init();

//~ Testing cascading 595s, multidimensional arrays

	while (1){
		for (n=0; n<16; n++){
			for (i=0; i<16; i++){
				digitalWrite(SDI, CascPattern[n][i]);
				pulse(SRCLK);
			}
			pulse(RCLK);
			delay((n*n*n*n*n)/5500);
		}
	}
	

	for (n=0; n<8; n++){
		printf("N:   %d\n", n);
		printf("N**: %d\n", (n*(n*n)));
		printf("\n");
	}

	//~ init();
	
	return 0;
}
