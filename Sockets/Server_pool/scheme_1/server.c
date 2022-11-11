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
#include "socklib.c"

#define RANDPORT 7000+rand()%2001


void* _client(void *arg) 
{
	int newport = *(int*)arg;
	char ext[] = "/exit";

	datagram message;

	sockconfig serv_cl = init(AF_INET, inet_addr("127.0.0.1"), htons(newport));
	sockconfig client_cl = serv_cl;

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
		recv_from(handler_sock, &message, sizeof(message), client_cl);
		//r3cv_from(handler_sock, &message, sizeof(message), 0, (struct sockaddr *) &client_cl, &cl_size);
		if (strncmp(message.text, ext, strlen(ext)) == 0)
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

	sockconfig serv = init(AF_INET, inet_addr("127.0.0.1"), htons(PORT));
	sockconfig client = serv;

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

		//recv_from(list_sock, pid, sizeof(pid), client);
		r3cv_from(list_sock, pid, sizeof(pid), 0, (struct sockaddr *) &client, &cl_size);
		newport = RANDPORT;
		char *data = (char*)&newport;

		send_to(list_sock, data, sizeof(data), client);

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