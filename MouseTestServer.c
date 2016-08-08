#include "pseudomouse.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>

struct pseudomouse TestMouse;
int i;
struct timespec TimeStamp;
double RefTime;//timestamp for 10 ms cycle
double CurTime;//times in ms


int main(void)
{
	TestMouse = startMouse();
	RefTime = 0;
	CurTime = 0;


	for(i =0; i < 20000; i++) //should be around 20 sec
	{
		//get time
		
		clock_gettime(CLOCK_MONOTONIC, &TimeStamp);
		RefTime = (TimeStamp.tv_sec*1000)+(TimeStamp.tv_nsec / 1000000);
		printf("RefTime is %0.2f ms\n", RefTime);
		
		updateSpeeds( &TestMouse);
		
		printf("acceleration(m/s/s) x:%0.2f y:%0.2f z:%0.2f\nvelocity(m/s) x:%0.2f y:%0.2f z:%0.2f\n\n",
				TestMouse.DevHandle.AccX, TestMouse.DevHandle.AccY ,TestMouse.DevHandle.AccZ,
				TestMouse.VelX, TestMouse.VelY, TestMouse.VelZ);
		printf("Compass(degrees) x:%0.2f y:%0.2f z:%0.2f\n", TestMouse.DevHandle.CompX, TestMouse.DevHandle.CompY, TestMouse.DevHandle.CompZ);
				
		while(CurTime < RefTime + CYCLIC_PERIOD)//burn till 10 ms later
		{
			clock_gettime(CLOCK_MONOTONIC, &TimeStamp);
			CurTime = (TimeStamp.tv_sec*1000)+(TimeStamp.tv_nsec / 1000000);

		} 


	}
	return 0;
}
