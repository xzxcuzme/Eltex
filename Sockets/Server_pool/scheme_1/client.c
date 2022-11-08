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

int _connect() 
{
	pid_t ppid = getpid();
	int newport;
	char *pid = (char*)&ppid;
	char *data = (char*)&newport;

	struct sockaddr_in serv_cnct;
	serv_cnct.sin_family = AF_INET;
	serv_cnct.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	serv_cnct.sin_port = htons(PORT);
	socklen_t serv_cnct_size = sizeof(serv_cnct);

	int list_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (list_sock == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (sendto(list_sock, pid, sizeof(pid), 0, (struct sockaddr *) &serv_cnct, serv_cnct_size) == -1) 
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}

	if (recvfrom(list_sock, data, sizeof(data), 0, (struct sockaddr *) &serv_cnct, &serv_cnct_size) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}

	close(list_sock);
	newport = *(int32_t*)data;
	return (newport);
}

void _hndlr(int arg) 
{
	int newport = arg;
	typedef struct msg {
		char text[MSG_LEN];
		char nickname[NAME_LEN];
	} msg;
	char text[MSG_LEN];
	char ext[6] = "/exit";
	msg message;
	msg *pointermsg;
	pointermsg = &message;
	printf("name: ");
	char nickname[NAME_LEN];
	fgets(nickname, sizeof(nickname), stdin);
	strncpy(pointermsg -> nickname, nickname, sizeof(&nickname));
	int len = strlen(nickname);
	if (message.nickname[len-1] == '\n') message.nickname[len-1] = 0;

	struct sockaddr_in serv;
	socklen_t serv_size = sizeof(serv);
	serv.sin_family = AF_INET;
	serv.sin_port = htons(newport);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	int hndlr_sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (hndlr_sock == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	printf("write '/exit' to exit\n");

	while(1)
	{
		printf("write a message: ");
		fgets(text, sizeof(text), stdin);

		if(strncmp(text, ext, sizeof(6)) == 0)
		{
			strncpy(pointermsg -> text, "/exit", sizeof(&text));

			if (sendto(hndlr_sock, &message, sizeof(message), 0, (struct sockaddr *) &serv, serv_size) == -1) 
			{
				perror("sendto error");
				exit(EXIT_FAILURE);
			}

			printf("exit\n");
			exit(EXIT_SUCCESS);
		}

		strncpy(pointermsg -> text, text, sizeof(&text));
		int len = strlen(text);
		if (message.text[len-1] == '\n') message.text[len-1] = 0;
		printf("%s: ", message.nickname);
		printf("%s\n", message.text);

		if (sendto(hndlr_sock, &message, sizeof(message), 0, (struct sockaddr *) &serv, serv_size) == -1) 
		{
			perror("sendto error");
			exit(EXIT_FAILURE);
		}
	}

	close(hndlr_sock);
}

int main()
{
	int newport = _connect();
	_hndlr(newport);
	exit(EXIT_SUCCESS);
}