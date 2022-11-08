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

void* _client(void *arg) 
{
	int newport = *(int*)arg;

	typedef struct msg {
		char text[MSG_LEN];
		char nickname[NAME_LEN];
	} msg;

	msg message;

	struct sockaddr_in serv_cl;
	struct sockaddr_in client_cl;
	serv_cl.sin_family = AF_INET;
	serv_cl.sin_addr.s_addr = inet_addr("127.0.0.1"); //INADDR_ANY; //inet_addr("127.0.0.1")
	serv_cl.sin_port = htons(newport);
	socklen_t cl_size = sizeof(client_cl);

	int hndlr_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (hndlr_sock == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}
	
	if (bind(hndlr_sock, (struct sockaddr *) &serv_cl, sizeof(serv_cl)) == -1) 
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	while(1) 
	{
		if (recvfrom(hndlr_sock, &message, sizeof(message), 0, (struct sockaddr *) &client_cl, &cl_size) == -1)
		{
			perror("recvfrom error");
			exit(EXIT_FAILURE);	
		}

		if (strncmp(message.text, "/exit", sizeof(6)) == 0)
		{
			printf("%s отключился\n", message.nickname);
			break;
		}

		printf("%s: ", message.nickname);
		printf("%s\n", message.text);
	}
	
	close(hndlr_sock);
	return 0;
}

int client_hndlr()
{
	pthread_t thread;
	int status;

	pid_t name = getpid();
	char *pid = (char*)&name;
	int32_t newport;
	newport = PORT;

	struct sockaddr_in serv;
	struct sockaddr_in client;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv.sin_port = htons(PORT);
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

		if (recvfrom(list_sock, pid, sizeof(pid), 0, (struct sockaddr *) &client, &cl_size) == -1)
		{
			perror("recvfrom error");
			exit(EXIT_FAILURE);	
		}

		newport = RANDPORT;
		char *data = (char*)&newport;

		if (sendto(list_sock, data, sizeof(data), 0, (struct sockaddr *) &client, cl_size) == -1)
		{
			perror("sendto from lister server error");
			exit(EXIT_FAILURE);	
		}

		printf("Клиент %d присоеденился c адресом %s:%d\n", *(pid_t*)pid, inet_ntoa(serv.sin_addr), newport);
		
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
	client_hndlr();
	exit(EXIT_SUCCESS);
}