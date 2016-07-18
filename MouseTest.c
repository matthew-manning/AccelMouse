#include "pseudomouse.h"
#include <stdio.h>

struct pseudomouse TestMouse;
int i;
int WasteTime;



int main(void)
{
	TestMouse = startMouse();

	for(i =0; i < 20000; i++) //should be around 20 sec
	{
		//get time
		
		updateSpeeds( &TestMouse);
		
		printf("acceleration(m/s/s) x:%0.2f y:%0.2f z:%0.2f\nvelocity(m/s) x:%0.2f y:%0.2f z:%0.2f\n\n",
				TestMouse->DevHandle.AccX, TestMouse->DevHandle.AccY ,TestMouse->DevHandle.AccZ,
				TestMouse->VelX, TestMouse->VelY, TestMouse->VelZ);
				
		while()//burn till 10 ms later
		{
			WasteTime *= 6;
		}
		
	}
	return 0;
}
