#include "i2c.h"

#define ACCEL_FIRST_REG 0x3b
#define ACCEL_ADDRESS 0x68
#define ACCEL_DIVISOR 8192
#define ACCEL_RANGE_REG 0x1c
#define RANGE_CON_VAL 0x08 // +- 4g

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
	
	/*degrees /s/s ???
	 *
	 */
	float GyroX;
	float GyroY;
	float GyroZ;
	
	/*degrees from xxxx ??
	 *
	 */
	float CompX;
	float CompY;
	float CompZ;
	
	float Pressure;
	
};
typedef struct ws10dofhandle ws10dofhandle;//make better short type name 

struct ws10dofhandle ws10dof_start(int I2CBus, int Address, int AccRange);

int ws10dof_range(struct * ws10dofhandle, int AccRange);

int wsdof_update(struct ws10dofhandle * DevHandle)
