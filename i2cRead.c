/*program for the sbc to read and display 
 *acceleration values from accelorometer
*/

#include <stdio.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>//open function
#include <sys/ioctl.h>//ioctl function 
#include <unistd.h>//read function
#include <stdint.h>

#define ACCEL_ADDR 0x68 //i2c addr for accelrometer 

#define ACCEL_DIVSOR 8192 //for +- 4g
#define ACCEL_CONFIG 0x08
#define ACCEL_CON_REG 0x1c

#define X_ACCEL_REG1 0x3b//reg for bits 15-8 of x acceleration
#define X_ACCEL_REG2 0x3c//^ bits 7-0, think not needed for this

int DevHandle; 
int NumRead;//debug value	
uint8_t Reg16b[3];//array for reading/writing 16 bits (2 registers)
float XAccel; // m/s/s value stored
float AccScale = ACCEL_DIVSOR/9.80665; 

int main(void)
{
	//open i2c 
	DevHandle = open("/dev/i2c-1", O_RDWR);
	
	if(DevHandle < 0)//check handle is okay
	{
		printf("failed to open i2c handle\n");
		return -1;
	}
	
	//setting i2c address 
	if(ioctl(DevHandle, I2C_SLAVE, ACCEL_ADDR) <0)
	{
		printf("failed to set device address\n");
		return -1;
	}

	//write config registers
	
	while(1)
	{
		//read registers
		Reg16b[0] = X_ACCEL_REG1; //setting address
		
		NumRead = read(DevHandle, Reg16b, 2);//debug line
		
		if( NumRead !=2)//read(Reg16b, 2) != 2)//return Num reg read should be same as requsted Num
		{
			printf("number of regs read is: %d; Reg16b[1] is: %x, REg16b[2] is: %x\n", NumRead, Reg16b[1], Reg16b[2]);
			printf("could not read reg %x\n", X_ACCEL_REG1);
			return -1;
		}
		
		
		
		//get sensible values and print
		XAccel = (( (Reg16b[1] << 8) | Reg16b[0]) / AccScale);/*Unkowns
															  **negitive values' minus sign properly interpreted?
															  *
															  **is the 15-8 bits stored in Reg16b[1] and not Reg16b[2]?
															  */
		printf("acceleration measured is %0.2f ms^-2\n", XAccel);
		
		usleep(250000);//250 ms
	}
	
	return 0;
}  
