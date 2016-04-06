#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int helloSocket, newSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	/* ---- Create the socket. ---*/

	/* 1. Internet domain
	   2. Stream socket
	   3. Default protocol(TCP)
	*/


	helloSocket = socket(PF_INET, SOCK_STREAM, 0);
	
	/*--Configure setting of the server address struct--*/
	/*--Address family = Internet--*/
	serverAddr.sin_family = AF_INET;

	/*Port Number*/
	serverAddr.sin_port = htons(7891);
	
	/*IP Address*/
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	/*Padding field to 0*/
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*Bind address to the socket*/
	bind(helloSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*Listen on the socket*/
	if(listen(helloSocket, 5) == 0)
		printf("Listen Socket\n");
	else
		printf("Failed to listen\n");

	/*Accept call, create a new socket for a new connection*/
	addr_size = sizeof serverStorage;
	newSocket = accept(helloSocket, (struct sockaddr *) &serverStorage, &addr_size);

	/*Send Message to the socket for incoming connection*/
	strcpy(buffer, "Hello, World\n");
	send(newSocket, buffer, 13, 0);
	
	return 0;
}
