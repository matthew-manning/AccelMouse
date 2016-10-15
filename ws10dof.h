#ifndef _WS10DOF_H_
#define _WS10DOF_H_

#include "i2c.h"

#define ACCEL_FIRST_REG 0x3b
#define ACCEL_ADDRESS 0x68
#define ACCEL_DIVISOR 8192
#define ACCEL_RANGE_REG 0x1c
#define GYRO_RANGE_REG 0x1b
#define GYRO_FIRST_REG 0x43
#define COMPASS_CON_REG 0x00
#define COMPASS_FIRST_REG 0x03
#define RANGE_CON_VAL 0x08 
#define GYRO_DRIFT_THRESHOLD 0.5

struct ws10dofhandle
{
	struct i2c_handle I2CHandle;
	/*acceleration in m/s/s
	 *not adjusted for constant gravity
	 */
	float AccX;
	float AccY;
	float AccZ;
	float AccDiv; //to m/s/s
	
	// deg/sec
	float VelPitch;//x
	float VelRoll;//y
	float VelYaw;//z
	float GyroDiv;//to deg/s
	
	float Pressure;
	
};
//typedef struct ws10dofhandle ws10dofhandle;//make better short type name 

struct ws10dofhandle ws10dof_start(int I2CBus, int Address, int AccRange, int GyroRange);

int ws10dof_range(struct ws10dofhandle * DevHandle, int AccRange, int GyroRange);

int ws10dof_update(struct ws10dofhandle * DevHandle);

#endif
