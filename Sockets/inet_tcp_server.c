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
	char str[10] = "Hello!";
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(PORT);

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (bind(fd, (struct sockaddr *) &serv, sizeof(struct sockaddr_in)) == -1)
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	listen(fd, 5);
	
	struct sockaddr_in client;
	socklen_t cl_size = sizeof(client);

	int new_fd = accept(fd, (struct sockaddr *) &client, &cl_size);

	if (new_fd == -1)
	{
		perror("accept error");
		exit(EXIT_FAILURE);
	}

	printf("Отправил клиенту: %s\n", str);

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