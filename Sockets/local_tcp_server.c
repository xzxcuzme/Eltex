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
	char str[10] = "Hello!";
	struct sockaddr_un serv;
	serv.sun_family = AF_LOCAL;
	strcpy(serv.sun_path, "sock_stream");

	int fd = socket(AF_LOCAL, SOCK_STREAM, 0);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (bind(fd, (struct sockaddr *) &serv, sizeof(struct sockaddr_un)) == -1)
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	listen(fd, 5);
	
	struct sockaddr_un client;
	socklen_t cl_size = sizeof(client);

	int new_fd = accept(fd, (struct sockaddr *) &client, &cl_size);

	if (new_fd == -1)
	{
		perror("accept error");
		exit(EXIT_FAILURE);
	}

	if (send(new_fd, str, sizeof(str), 0) == -1)
	{
		perror("send error");
		exit(EXIT_FAILURE);
	}

	if (recv(new_fd, str, sizeof(str), 0) == -1)
	{
		perror("receive error");
		exit(EXIT_FAILURE);
	}

	printf("Получил от клиента: %s\n", str);

	close(new_fd);
	close(fd);
    unlink("sock_stream");
    exit(EXIT_SUCCESS);
}