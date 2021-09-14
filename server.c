#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
/* File:     server.c
 *
 * Purpose:  Allows communication between two lab machines using multithreading
 *
 * Compile:  gcc server.c -o server -pthread
 *
 * Example:	 ./server
 *
 */
void *pthread_function (void* p_client_socket) {
	char server_message[256] = "PONG.";
	int client_socket = *((int*)p_client_socket);
	free (p_client_socket);
	
	send(client_socket, server_message,sizeof(server_message), 0);
	return NULL;	
	}
int main() {
	// create server socket
	int network_socket, client_socket, address_size;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address for the socket
	struct sockaddr_in server_address, client_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(39006);
	// binds to default address of the machine
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	// bind socket to specified IP and port (tells us which IP we should use to look for connections)
	bind(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	
	// listens for client connections
	listen(network_socket, 5);
	
	while (true) {
		printf("Waiting for connections...\n");
		address_size = sizeof(client_address);
		client_socket = accept(network_socket, 
        (struct sockaddr *) &client_address, 
        &address_size);
		printf("Connected to client.\n");
		
		pthread_t t;
		int *pclient = malloc(sizeof(int));
		*pclient= client_socket;
		pthread_create(&t, NULL, pthread_function, pclient);
		
		
	}
	// closes socket
	close(network_socket);

	return 0;
	
}