#include "pseudomouse.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet.h>

#define MOUSE_ADDRESS 4000

struct pseudomouse TestMouse;
int i;
struct timespec TimeStamp;
double RefTime;//timestamp for 10 ms cycle
double CurTime;//times in ms

//server stuff
int SocketFD;
int ConnectionHandle;
struct sockaddr_in MouseAddr, ClientAddr;


int main(void)
{
	TestMouse = startMouse();
	RefTime = 0;
	CurTime = 0;
	
	SocketFD = socket(AF_INET, SOCK_STREAM, 0);//create file device
	if (SocketFD < 0)
	{
		printf("failed to create socket file device\n");
	}
	
	 //need some code here to set port and addresses
	 bzero((char*) &MouseAddr, sizeof(MouseAddr));
	 MouseAddr.sin_family = AF_INET;
	 MouseAddr.sin_addr.s_addr = INADDR_ANY;
	 MouseAddr.sin_port = htons(MOUSE_ADDRESS);
	 
	 
	bind(SocketFD, (struct sockaddr *)&MouseAddr, sizeof(MouseAddr));
	listen(SocketFD, 10);
	printf("waiting for connection\n");
	ConnectionHandle = accept(SocketFd, (struct sockaddr *) &ClientAddr, sizeof(ClientAddr));


	for(i =0; i < 20000; i++) //should be around 20 sec
	{
		//write to socket
		NumWritten = write(ConnectionHandle, "from RPI Mouse ", 15);
		if(NumWritten < 0)
		{
			printf("failed to write to socket\n");
		}
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
