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
	ws10dof_update(& Mouse->DevHandle);

	//calling periodically handles to x time between calculations	
	Mouse->VelX += (Mouse->DevHandle.AccX * CYCLIC_PERIOD)/1000;
	Mouse->VelY += (Mouse->DevHandle.AccY * CYCLIC_PERIOD)/1000;
	Mouse->VelZ += (Mouse->DevHandle.AccZ * CYCLIC_PERIOD)/1000;	
	
	return 0;
}
