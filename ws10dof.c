/*make into library with:
 *start()
 *update()
 *range()	
 *functions working with ws10dofhandle structure in ws10dof.h 
 */

#include "i2c.h"
#include "ws10dof.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

struct ws10dofhandle ws10dof_start(int I2CBus, int Address, int AccRange)
{
	uint8_t ConBuf[3];
	
	struct ws10dofhandle  DevHandle;
	DevHandle.I2CHandle = *i2c_init(I2CBus, Address, 0);
	
	//configure accelorometer
	ws10dof_range(&DevHandle, AccRange);
	
	//configure compass
	ConBuf[0] = 0x18;
	ConBuf[1] = 0x20;
	ConBuf[2] = 0x80;
	i2c_write_to_reg(&DevHandle.I2CHandle, COMPASS_CON_REG, (char *)ConBuf, 3);
	
	
	
	return DevHandle;
};

int ws10dof_range(struct ws10dofhandle * DevHandle, int AccRange)
{
	//uint8_t ConBuf[2];
	uint8_t ConVal;
	switch (AccRange)
	{	
		/*case 2: ConBuf[0] = 0x0; ConBuf[1] = 0x0; DevHandle->AccDiv = (16384/9.806) ; break;
		case 4: ConBuf[0] = 0x0; ConBuf[1] = 0x8; DevHandle->AccDiv = (8192/9.806)  ;break;
		case 8: ConBuf[0] = 0x1; ConBuf[1] = 0x0; DevHandle->AccDiv = (4096/9.806)  ;break;
		case 16: ConBuf[0] = 0x1; ConBuf[1] = 0x8;DevHandle->AccDiv = (2048/9.806)  ;break;
		default: printf("invalid range setting of +- %d g\n", AccRange); return -1;*/
		
		
		case 2: ConVal = 0x00; DevHandle->AccDiv = (16384/9.806) ; break;
		case 4: ConVal = 0x08; DevHandle->AccDiv = (16384/9.806) ; break;
		case 8: ConVal = 0x10; DevHandle->AccDiv = (16384/9.806) ; break;
		case 16: ConVal = 0x18; DevHandle->AccDiv = (16384/9.806) ; break;
	
		default: printf("invalid range setting of +- %d g\n", AccRange); return -1;
	
	}

	printf("Range set function set using [0x%x]", ConVal);//for debugging

	i2c_write_to_reg(&DevHandle->I2CHandle, ACCEL_RANGE_REG, (char *)(&ConVal), 1);

	/*
	printf("Range set function set using [%x,%x]", ConBuf[0], ConBuf[1]);//for debugging

	i2c_write_to_reg(&DevHandle->I2CHandle, ACCEL_RANGE_REG, (char *)ConBuf, 2);
	*/
	
	return 0;
}

int16_t BuffToI16(uint8_t *x)
{
	uint16_t u;
	u = ((uint16_t)(x[0])) << 8;
	u |= (uint16_t)x[1];
	
	return (int16_t) u;
}


int ws10dof_update(struct ws10dofhandle * DevHandle)
{
	//read acceloromter
	uint8_t Buf6Bytes[6];
	uint16_t U16val;
	int16_t S16val;
	
	i2c_read_from_reg(&DevHandle->I2CHandle, ACCEL_FIRST_REG, (char *)Buf6Bytes, 6);
	
	DevHandle->AccX = BuffToI16(&Buf6Bytes[0]) / DevHandle->AccDiv;
	DevHandle->AccY = BuffToI16(&Buf6Bytes[2]) / DevHandle->AccDiv;
	DevHandle->AccZ = BuffToI16(&Buf6Bytes[4]) / DevHandle->AccDiv;
	
	//x
	U16val = ((uint16_t)Buf6Bytes[0] << 8)|((uint16_t)Buf6Bytes[1]);
	S16val = (int16_t)U16val;
	DevHandle->AccX = (S16val / DevHandle->AccDiv); 
	//y
	U16val = ((uint16_t)Buf6Bytes[2] << 8)|((uint16_t)Buf6Bytes[3]);
	S16val = (int16_t)U16val;
	DevHandle->AccY = (S16val / DevHandle->AccDiv); 
	//z
	U16val = ((uint16_t)Buf6Bytes[4] << 8)|((uint16_t)Buf6Bytes[5]);
	S16val = (int16_t)U16val;
	DevHandle->AccZ = (S16val / DevHandle->AccDiv); 
	
	//read gyro
	//read compass
	i2c_read_from_reg(&DevHandle->I2CHandle, COMPASS_FIRST_REG, (char *)Buf6Bytes, 6);
	//x
	U16val = ((uint16_t)Buf6Bytes[0] << 8)|((uint16_t)Buf6Bytes[1]);
	S16val = (int16_t)U16val;
	DevHandle->CompX = (S16val / DevHandle->AccDiv); 
	//y
	U16val = ((uint16_t)Buf6Bytes[2] << 8)|((uint16_t)Buf6Bytes[3]);
	S16val = (int16_t)U16val;
	DevHandle->CompY = (S16val / DevHandle->AccDiv); 
	//z
	U16val = ((uint16_t)Buf6Bytes[4] << 8)|((uint16_t)Buf6Bytes[5]);
	S16val = (int16_t)U16val;
	DevHandle->CompZ = (S16val / DevHandle->AccDiv); 
	
	return 0;
}
