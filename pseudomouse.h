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
	
	float ScrubGravity;
	
	float TiltPitch;
	float TiltRoll;
	float TiltYaw; 

	struct ws10dofhandle DevHandle;
};
//typedef 

struct pseudomouse startMouse();
int updateSpeeds(struct pseudomouse * Mouse);
int updateSpeeds_LS(struct pseudomouse * Mouse);
int autoLevel(struct pseudomouse * Mouse);

#endif
