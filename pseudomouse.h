#ifndef _PSEUDOMOUSE_H_
#define _PSEUDOMOUSE_H_


#include "ws10dof.h"

#define CYCLIC_PERIOD 20 // ms since speed last adjusted 
#define MOUSE_ACCEL_RANGE 4// +-4g

struct pseudomouse
{
	//actual velocity in m/s
	float VelX;
	float VelY;
	float VelZ;

	struct ws10dofhandle DevHandle;
};
//typedef 

struct pseudomouse startMouse();
int updateSpeeds(struct pseudomouse * Mouse);

#endif
