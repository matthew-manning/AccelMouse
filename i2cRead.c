/*program for the sbc to read and display 
 *acceleration values from accelorometer
*/

#include <stdio.h>
#define ACCEL_DIVSOR 8192 //for +- 4g
#define ACCEL_CONFIG 0x08
#define ACCEL_CON_REG 0x1c

#define X_ACCEL_REG1 0x3b//reg for bits 15-8 of x acceleration
#define X_ACCEL_REG2 0x3c//^ bits 7-0

int main(void)
{
	//open i2c 


	//write config registers
	
	while(1)
	{
		//read registers
		
		//get sensible values and print
		
	}
	
	return 0;
}  
