#include "ws10dof"

#define CYCLIC_PERIOD 0.010 // seconds since speed last adjusted 
#define MOUSE_ACCEL_RANGE 4// +-4g

struct pseudomouse
{
	//actual velocity in m/s
	float VelX;
	float VelX;
	float VelX;

	struct ws10dofhandle DevHandle;
};
//typedef 

struct pseudomouse startMouse();
int updateSpeeds(struct pseudomouse * Mouse);
