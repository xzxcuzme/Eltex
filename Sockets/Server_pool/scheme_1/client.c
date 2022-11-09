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

typedef struct sockaddr_in sockaddr;

sockaddr init(short a, uint b, ushort c)
{
	sockaddr serv;
	serv.sin_family = a;
	serv.sin_addr.s_addr = b; 
	serv.sin_port = c;
	return serv;
}

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

int _connect() 
{
	pid_t ppid = getpid();
	int newport;
	char *pid = (char*)&ppid;
	char *data = (char*)&newport;

	sockaddr serv_connect = init(AF_INET, inet_addr("127.0.0.1"), htons(PORT));
	socklen_t serv_connect_size = sizeof(serv_connect);

	int list_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (list_sock == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	send_to(list_sock, pid, sizeof(pid), 0, (struct sockaddr *) &serv_connect, serv_connect_size);

	recv_from(list_sock, data, sizeof(newport), 0, (struct sockaddr *) &serv_connect, &serv_connect_size);

	close(list_sock);
	newport = *((int32_t*)data);
	return newport;
}

void _handler(int arg) 
{
	int newport = arg;
	typedef struct msg {
		char text[MSG_LEN];
		char nickname[NAME_LEN];
	} msg;

	char text[MSG_LEN];
	char nickname[NAME_LEN];
	char ext[] = "/exit";

	msg message;
	msg *pointermsg;
	pointermsg = &message;

	printf("name: ");
	
	fgets(nickname, sizeof(nickname), stdin);
	strncpy(pointermsg -> nickname, nickname, sizeof(&nickname));
	term_del(message.nickname);

	sockaddr serv = init(AF_INET, inet_addr("127.0.0.1"), htons(newport));
	socklen_t serv_size = sizeof(serv);

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

		if (strncmp(text, ext, sizeof(int)) == 0)
		{
			strncpy(pointermsg -> text, "/exit", sizeof(&text));

			send_to(handler_sock, &message, sizeof(message), 0, (struct sockaddr *) &serv, serv_size); 

			printf("exit\n");
			exit(EXIT_SUCCESS);
		}

		strncpy(pointermsg -> text, text, sizeof(&text));
		term_del(message.text);

		send_to(handler_sock, &message, sizeof(message), 0, (struct sockaddr *) &serv, serv_size);

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