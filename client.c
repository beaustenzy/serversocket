#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <unistd.h>
/* File:     client.c
 *
 * Purpose:  Allows communication between two lab machines
 *
 * Compile:  gcc client.c -o client
 *
 * Example:	 ./client server_name
 *
 */
int main(int argc, char *argv[]) {
	// host name provided via input
	struct hostent *server;
	server = gethostbyname(argv[1]);
	// creates a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// specify an address for the socket
	struct sockaddr_in server_address;
	bzero((char *) &server_address, sizeof(server_address));
	
	// uses address provided by input (copies h_addr into s_addr)
	bcopy((char *)server->h_addr, 
         (char *)&server_address.sin_addr.s_addr,
         server->h_length);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(39006);
	
	int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	// check for error with connection
	if (connection_status == -1) {
		printf("There was an error making a connection to the remote socket\n\n");
	}
	
	// receive data from the server
	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);
	
	// print server response
	printf("PING %s\n",server_response);
	// closes socket
	close(network_socket);
	
	return 0;
}