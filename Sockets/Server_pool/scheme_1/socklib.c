#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9006
#define NAME_LEN 30
#define MSG_LEN 100

typedef struct sockaddr_in sockconfig;

typedef struct datagram {
	char text[MSG_LEN];
	char nickname[NAME_LEN];
} datagram;

sockconfig init(short sin_famil, uint sin_addr, ushort sin_port)
{
	sockconfig serv;
	serv.sin_family = sin_famil;
	serv.sin_addr.s_addr = sin_addr; 
	serv.sin_port = sin_port;
	return serv;
}

void send_to(int s, const void *send_message, size_t len, const struct sockaddr_in mysock)
{
	char *msg = (char*)send_message;
	//size_t len = sizeof(recv_message);
	int flags = 0;
	struct sockaddr *to = (struct sockaddr *) &mysock;
	socklen_t tolen = sizeof(mysock);
	if (sendto(s, msg, len, flags, to, tolen) == -1) 
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}
}

void recv_from(int s, const void *recv_message, size_t len, const struct sockaddr_in mysock)
{
	socklen_t mysock_size = sizeof(mysock);
	char *buf = (char*)recv_message;
	//size_t len = sizeof(recv_message);
	int flags = 0;
	struct sockaddr *from = (struct sockaddr *) &mysock;
	socklen_t *fromlen = &mysock_size;
	
	if (recvfrom(s, buf, len, flags, from, fromlen) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}
}

void r3cv_from(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
	if (recvfrom(s, buf, len, flags, from, fromlen) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}
}