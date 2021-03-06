#include "pseudomouse.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <transferLib.h>

int waitForHost(int Port)
{
//waits for the host to
//connect

	int SocketFD;
	int ConnectionHandle;	
	struct sockaddr_in MouseAddr;
	struct sockaddr_in ClientAddr;
	socklen_t ClientAddrSize;

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
	ClientAddrSize = sizeof(ClientAddr);
	printf("waiting for connection\n");
	ConnectionHandle = accept(SocketFD, (struct sockaddr *) &ClientAddr, &ClientAddrSize);
	
	
	return ConnectionHandle;
}

int sendMouseData(int ConHandle, struct pseudomouse Mouse)
{
	int RetCode;
	int NumWritten;
	
	char Packet[] = ("vel x: %0.3f, vel y: %0.3f, vel z: %0.3f\n", Mouse.VelX, Mouse.VelY, Mouse.VelZ);//Okay?
	
	NumWritten = write(ConnectionHandle, Packet, sizeof(Packet));
	if(NumWritten < 0)
	{
		printf("failed to write to socket\n");
		RetCode = -1;
	}
	
	return RetCode;
}

/*int main(void)
{
	RefTime = 0;
	CurTime = 0;
	
	
		clock_gettime(CLOCK_MONOTONIC, &TimeStamp);
		RefTime = (TimeStamp.tv_sec*1000)+(TimeStamp.tv_nsec / 1000000);
		
				
		while(CurTime < RefTime + CYCLIC_PERIOD)//burn till 10 ms later
		{
			clock_gettime(CLOCK_MONOTONIC, &TimeStamp);
			CurTime = (TimeStamp.tv_sec*1000)+(TimeStamp.tv_nsec / 1000000);

}*/
