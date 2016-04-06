/** CLIENT CODE **/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	
	/*--Create the socket--*/
	
	/*1.internet domain, stream socket, default protocol (TCP)*/
	
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	
	/*--Configure settings of server--*/

	serverAddr.sin_family = AF_INET;

	/*--Port Number--*/

	serverAddr.sin_port = htons(7891);

	/*--IP Address--*/

	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	/*--Set all bits of the padding field to 0--*/

	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
	
	/*Connect socket to the server*/

	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	
	/*Read message from the server into the buffer*/

	recv(clientSocket, buffer, 1024, 0);
	
	/*Print the received message*/

	printf("Data received: %s", buffer);
	
	return 0;
}
