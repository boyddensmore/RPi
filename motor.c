#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
  
#define MotorPin1    0
#define MotorPin2    1
#define MotorEnable  2
  
int main(void)
{
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
        printf("setup wiringPi failed !");
        return 1;
    }
      
    //~ pinMode(MotorPin1, OUTPUT);
    //~ pinMode(MotorPin2, OUTPUT);
    pinMode(MotorEnable, OUTPUT);
    
    softPwmCreate(MotorPin1, 0, 100);
    softPwmCreate(MotorPin1, 0, 100);
  
    int i;
  
    //~ while(1){
        //~ printf("Motor High, P1 High, P2 Low\n");
        //~ digitalWrite(MotorEnable, HIGH);
        //~ digitalWrite(MotorPin1, HIGH);
        //~ digitalWrite(MotorPin2, LOW);
        //~ softPwmWrite(MotorPin1, 0);
        //~ softPwmWrite(MotorPin2, 100);
        
        //~ for(i=0;i<3;i++){
            //~ delay(1000);
        //~ }
		//~ 
		//~ printf("Motor Off\n");
        //~ digitalWrite(MotorEnable, LOW);
        //~ for(i=0;i<3;i++){
            //~ delay(1000);
        //~ }
  //~ 
		printf("Motor High, P1 Low, P2 High\n");
        digitalWrite(MotorEnable, HIGH);
        digitalWrite(MotorPin1, LOW);
        digitalWrite(MotorPin2, HIGH);
        //~ softPwmWrite(MotorPin1, 0);
        //~ softPwmWrite(MotorPin2, 100);
        //~ for(i=0;i<3;i++){
            //~ delay(1000);
        //~ }
    //~ }
  
    return 0;
}
