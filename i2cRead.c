/*program for the sbc to read and display 
 *acceleration values from accelorometer
*/

#include <stdio.h>
#include <linux/i2c-dev.h>

#define ACCEL_ADDR 0x68 //i2c addr for accelrometer 

#define ACCEL_DIVSOR 8192 //for +- 4g
#define ACCEL_CONFIG 0x08
#define ACCEL_CON_REG 0x1c

#define X_ACCEL_REG1 0x3b//reg for bits 15-8 of x acceleration
#define X_ACCEL_REG2 0x3c//^ bits 7-0

int DevHandle; 


int main(void)
{
	//open i2c 
	DevHandle = open("/dev/i2c-1", 0_RDWR);
	
	if(DevHandle < 0)//check handle is okay
	{
		printf("failed to open i2c handle\n");
		return -1;
	}
	
	//setting i2c address 
	if(ioctl(DevHandle, I2C_SLAVE, ACELL_ADDR) <0)
	{
		printf("failed to set device address\n");
		return -1;
	}

	//write config registers
	
	while(1)
	{
		//read registers
		
		//get sensible values and print
		
	}
	
	return 0;
}  
