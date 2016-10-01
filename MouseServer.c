/*Matthew Manning
 *02-10-2016
 *
 *creates a listening server which sends velocity data to a host computer
 */

#include "transferLib.h"
#include "pseudomouse.h"

#include <time.h>
#include <sys/types.h>


#define MOUSE_PORT 4000

struct pseudomouse ServMouse;
int i;
int HostConnection;
struct timespec TimeStamp;
double RefTime;//timestamp for 10 ms cycle
double CurTime;//times in ms


int main(void)
{
	ServMouse = startMouse();
	HostConnection = waitForHost(MOUSE_PORT);
	RefTime = 0;
	CurTime = 0;
	
	while(1)
	{
		
		//get ref time
		clock_gettime(CLOCK_MONOTONIC, &TimeStamp);
		RefTime = (TimeStamp.tv_sec*1000)+(TimeStamp.tv_nsec / 1000000);
		
		//get and send speeds	
		updateSpeeds( &ServMouse);
		sendMouseData(HostConnection, ServMouse, CYCLIC_PERIOD);
		
		
		//burn time till CYCLIC_PERIOD has passed
		while(CurTime < RefTime + CYCLIC_PERIOD)//burn till 10 ms later
		{
			clock_gettime(CLOCK_MONOTONIC, &TimeStamp);
			CurTime = (TimeStamp.tv_sec*1000)+(TimeStamp.tv_nsec / 1000000);

		} 
		
		
		
	}
		
	return 0;
}
