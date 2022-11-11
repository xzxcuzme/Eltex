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

void term_del(char *arg)
{
	int len = strlen(arg);
	if (arg[len-1] == '\n') arg[len-1] = 0;
}

void send_msg(char *arg)
{
	do
	{
		printf("write a message: ");
		fgets(arg, MSG_LEN, stdin);
		if (strlen(arg) >= MSG_LEN) printf("message too long, try again\n");
	} while (strlen(arg) >= MSG_LEN);
}

int _connect() 
{
	pid_t ppid = getpid();
	int newport;
	char *pid = (char*)&ppid;
	char *data = (char*)&newport;

	sockconfig serv_connect = init(AF_INET, inet_addr("127.0.0.1"), htons(PORT));
	socklen_t serv_connect_size = sizeof(serv_connect);

	int list_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (list_sock == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	send_to(list_sock, pid, sizeof(pid), serv_connect);
	//r3cv_from(list_sock, data, sizeof(data), 0, (struct sockaddr *) &serv_connect, &serv_connect_size);
	recv_from(list_sock, data, sizeof(data), serv_connect);

	close(list_sock);
	newport = *((int32_t*)data);
	return newport;
}

void _handler(int arg) 
{
	int newport = arg;

	char text[MSG_LEN];
	char nickname[NAME_LEN];
	char ext[] = "/exit";

	datagram message;
	datagram *pointer_datagram;
	pointer_datagram = &message;

	printf("name: ");
	
	fgets(nickname, sizeof(nickname), stdin);
	strncpy(pointer_datagram -> nickname, nickname, sizeof(&nickname));
	term_del(message.nickname);

	sockconfig serv = init(AF_INET, inet_addr("127.0.0.1"), htons(newport));

	int handler_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (handler_sock == -1)
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	printf("write '/exit' to exit\n");

	while(1)
	{
		send_msg(text);

		if (strncmp(text, ext, strlen(ext)) == 0)
		{
			strncpy(pointer_datagram -> text, ext, strlen(ext));

			send_to(handler_sock, &message, sizeof(message), serv); 

			printf("exit\n");
			exit(EXIT_SUCCESS);
		}

		strncpy(pointer_datagram -> text, text, sizeof(&text));
		term_del(message.text);

		send_to(handler_sock, &message, sizeof(message), serv);

		{
			printf("%s: ", message.nickname);
			printf("%s\n", message.text);
		}
	}

	close(handler_sock);
}

int main()
{
	int newport = _connect();
	_handler(newport);
	exit(EXIT_SUCCESS);
}