#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define PORT 9002

int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(PORT);

	socklen_t serv_size = sizeof(serv);

	if (connect(fd, (struct sockaddr *) &serv, serv_size) == -1)
	{
		perror("connect error");
		exit(EXIT_FAILURE);
	}

	char str[10];

	if (recv(fd, str, sizeof(str), 0) == -1) 
	{
		perror("receive error");
		exit(EXIT_FAILURE);
	}

    printf("Получил от сервера: %s\n", str);
    strcpy(str, "Hi!");

    if (send(fd, str, sizeof(str), 0) == -1) 
    {
		perror("send error");
		exit(EXIT_FAILURE);
	}

	printf("Отправил серверу: %s\n", str);

	close(fd);
    unlink("sock_stream");
    exit(EXIT_SUCCESS);
}