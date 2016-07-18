#include "ws10dof.h"
#include "pseudomouse.h"

struct pseudomouse startMouse()
{
	struct pseudomouse Mouse;
	//assume at rest
	Mouse.VelX = 0;
	Mouse.VelY = 0;
	Mouse.VelZ = 0;

	//start accelorometer
	Mouse.DevHandle = ws10dof_start(1, 0x68, MOUSE_ACCEL_RANGE);

	return Mouse;
}

int updateSpeeds(struct pseudomouse * Mouse)
{
	/*need to modifiy code to adjust for constant gravity*/

	//calling periodically handles to x time between calculations	
	Mouse->VelX += Mouse->Devhandle.AccX * CYCLIC_RERIOD;
	Mouse->VelY += Mouse->Devhandle.AccY * CYCLIC_RERIOD;
	Mouse->VelZ += Mouse->Devhandle.AccZ * CYCLIC_RERIOD;	
	
	return 0;
}
