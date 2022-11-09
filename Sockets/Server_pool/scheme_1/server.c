#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9006
#define RANDPORT 7000+rand()%2001
#define NAME_LEN 30
#define MSG_LEN 100

typedef struct sockaddr_in sockaddr;

sockaddr init(short a, uint b, ushort c)
{
	sockaddr serv;
	serv.sin_family = a;
	serv.sin_addr.s_addr = b; 
	serv.sin_port = c;
	return serv;
}

void send_to(int s, const void *msg, size_t len, int flags, const struct sockaddr *to, socklen_t tolen)
{
	if (sendto(s, msg, len, flags, to, tolen) == -1) 
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}
}

void recv_from(int s, void *buf, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
	if (recvfrom(s, buf, len, flags, from, fromlen) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}
}

void* _client(void *arg) 
{
	int newport = *(int*)arg;

	typedef struct msg {
		char text[MSG_LEN];
		char nickname[NAME_LEN];
	} msg;

	msg message;

	sockaddr serv_cl = init(AF_INET, inet_addr("127.0.0.1"), htons(newport));

	struct sockaddr_in client_cl;
	socklen_t cl_size = sizeof(client_cl);

	int handler_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (handler_sock == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}
	
	if (bind(handler_sock, (struct sockaddr *) &serv_cl, sizeof(serv_cl)) == -1) 
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	while(1) 
	{
		recv_from(handler_sock, &message, sizeof(message), 0, (struct sockaddr *) &client_cl, &cl_size);
		
		if (strncmp(message.text, "/exit", sizeof(int)) == 0)
		{
			printf("%s disconnected\n", message.nickname);
			break;
		}

		printf("%s: ", message.nickname);
		printf("%s\n", message.text);
	}

	close(handler_sock);
	return 0;
}

int client_handler()
{
	pthread_t thread;
	int status;

	pid_t name = getpid();
	char *pid = (char*)&name;
	int32_t newport;
	newport = PORT;

	sockaddr serv = init(AF_INET, inet_addr("127.0.0.1"), htons(PORT));

	struct sockaddr_in client;
	socklen_t cl_size = sizeof(client);

	while(1) 
	{
		int list_sock = socket(AF_INET, SOCK_DGRAM, 0);

		if (list_sock == -1) 
		{
			perror("socket create error");
			exit(EXIT_FAILURE);
		}

		if (bind(list_sock, (struct sockaddr *) &serv, sizeof(serv)) == -1) 
		{
			perror("bind error");
			exit(EXIT_FAILURE);
		}

		recv_from(list_sock, pid, sizeof(pid), 0, (struct sockaddr *) &client, &cl_size);

		newport = RANDPORT;
		char *data = (char*)&newport;

		send_to(list_sock, data, sizeof(data), 0, (struct sockaddr *) &client, cl_size);

		printf("Client %d connected with address %s:%d\n", *(pid_t*)pid, inet_ntoa(serv.sin_addr), newport);
		
		status = pthread_create(&thread, NULL, _client, &newport);
		if (status != 0) 
		{
			perror("pthread_create error");
			exit(EXIT_FAILURE);
		}

		close(list_sock);
	}
}

int main()
{
	client_handler();
	exit(EXIT_SUCCESS);
}