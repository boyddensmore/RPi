#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
 
#define  DevAddr  0x48  //device address
 
 
void adc_init(int fd)
{

	

}
 
int adc_read_0(int fd)
{
    int value;
 
    value = 0xff - wiringPiI2CReadReg8(fd, 0x32);
  
    return value;
}
 
int main(void)
{
    int fd;
    int currValue;
 
    fd = wiringPiI2CSetup(DevAddr);
     
    if(-1 == fd){
        printf("I2C device setup error\n");
    }
 
    while(1){
        currValue = adc_read_0(fd);
        printf("x: %05d\n", currValue);
        delay(1000);
    }
     
    return 0;
}
