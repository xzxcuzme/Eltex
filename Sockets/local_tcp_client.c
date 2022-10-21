#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
	int fd = socket(AF_LOCAL, SOCK_STREAM, 0);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_un serv;
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, "sock_stream");

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