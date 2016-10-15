#include "ws10dof.h"
#include "pseudomouse.h"
#include <math.h>

struct pseudomouse startMouse(int Range)
{
	struct pseudomouse Mouse;
	//assume at rest and level, add code to determine 
	//oritentation and gravity value
	Mouse.VelX = 0;
	Mouse.VelY = 0;
	Mouse.VelZ = 0;
	
	Mouse.TiltPitch = 0;
	Mouse.TiltRoll = 0;
	Mouse.TiltYaw = 0;
	
	Mouse.ScrubGravity = 9.806;

	//start accelorometer
	Mouse.DevHandle = ws10dof_start(1, 0x68, Range);

	return Mouse;
}

/*
 *only use one of the two update speed functions
 *one will put accel realtive velocities into struct 
 *other will put extrenal x, y and z velocities into struct
 */


int updateSpeeds(struct pseudomouse * Mouse)
{
	
	ws10dof_update(& Mouse->DevHandle);

	//calling periodically handles to x time between calculations	
	Mouse->VelX += (Mouse->DevHandle.AccX * CYCLIC_PERIOD)/1000;
	Mouse->VelY += (Mouse->DevHandle.AccY * CYCLIC_PERIOD)/1000;
	Mouse->VelZ += (Mouse->DevHandle.AccZ * CYCLIC_PERIOD)/1000;	
	
	//
	
	return 0;
}

int updateSpeeds_LS(struct pseudomouse * Mouse)
/*leveled accerations realitive to real, not accel, x y and z
 *with gravity scrubbed
 */
{
	
	ws10dof_update(& Mouse->DevHandle);
	
	Mouse.TiltPitch += (Mouse->DevHandle.VelPitch * CYCLIC_PERIOD)/1000;
	Mouse.TiltRoll += (Mouse->DevHandle.VelRoll * CYCLIC_PERIOD)/1000;
	Mouse.TiltYaw += (Mouse->DevHandle.VelYaw * CYCLIC_PERIOD)/1000;

	float CY = cosf(Mouse.TiltYaw*(180/M_PI));//needs converting to radians
	float CR = cosf(Mouse.TiltRoll*(180/M_PI));
	float CP = cosf(Mouse.TiltPitch*(180/M_PI));
	float SY = sinf(Mouse.TiltYaw*(180/M_PI));
	float SR = sinf(Mouse.TiltRoll*(180/M_PI));
	float SP = sinf(Mouse.TiltPitch*(180/M_PI));

	//adjusted accelerations
	float AccXAccel = (Mouse->DevHandle.AccX*CR*CY)+(Mouse->DevHandle.AccY*SY)+(Mouse->DevHandle.AccZ*SR);
	float AccYAccel = (Mouse->DevHandle.AccX*SY)+(Mouse->DevHandle.AccY*CP*CY)+(Mouse->DevHandle.AccZ*SP);
	float AccZAccel = (Mouse->DevHandle.AccX*SR)+(Mouse->DevHandle.AccY*SP)+(Mouse->DevHandle.AccZ*CR*CP) - Mouse.ScrubGravity;	
	
	printf("adjusted accels, x: %0.2f, y: %0.2f, z: %0.2f\n", AccXAccel, AccYAccel, AccZAccel);//debug print of adjusted accelerartions
	
	
	//calling periodically handles to x time between calculations, these values external realtive and scrubbed
	Mouse->VelX += (AccXAccel * CYCLIC_PERIOD)/1000;
	Mouse->VelY += (AccYAccel * CYCLIC_PERIOD)/1000;
	Mouse->VelZ += (AccZAccel * CYCLIC_PERIOD)/1000;	
	
	
	return 0;
}
