/*make into library with:
 *start()
 *update()
 *range()	
 *functions working with ws10dof structure if accread.h 
 */

#include "i2c.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define X_ACCEL_REG 0x3b//move to header 
#define ACCEL_ADDRESS 0x68
#define ACCEL_DIVISOR 8192
#define RANGE_CON_REG 0x1c
#define RANGE_CON_VAL 0x08

int i;
struct i2c_handle * DevHandle;
uint8_t Buf16b[2];
uint16_t U16val;
int16_t  S16val;
float Accel;
float Divisor;

int main(void)
{
	Divisor = ACCEL_DIVISOR / 9.806; 

	//open i2c device
	DevHandle = i2c_init(1, ACCEL_ADDRESS, 0);
	
	//write range config register 
	Buf16b[0] = RANGE_CON_VAL;
	i2c_write_to_reg(DevHandle, RANGE_CON_REG, Buf16b, 1);
	
	
	for(i = 0; i < 100 ;i++)
	{	
		//read x acceleration
		i2c_read_from_reg(DevHandle, X_ACCEL_REG, Buf16b, 2);
		
		//sensible value
		U16val = ((uint16_t)Buf16b[0] << 8) | ((uint16_t)Buf16b[1]);
		S16val = (int16_t)U16val;
		
		Accel = S16val / Divisor;
		
		printf("acceleration is %0.3f m/s/s\n", Accel);
		
		//actual reg values
		printf("actual reg values are: %x and %x\n", Buf16b[0], Buf16b[1]);
		usleep(100000);//100 ms
			
	}
	
return 0;
}
