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
	unlink("sock_serv");
	char str[10] = "hello";
	struct sockaddr_un serv;
	struct sockaddr_un client;
    serv.sun_family=AF_LOCAL;
    strcpy(serv.sun_path, "sock_serv");

    socklen_t cl_size = sizeof(client);

	int fd = socket(AF_LOCAL, SOCK_DGRAM, 0);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (bind(fd, (struct sockaddr *) &serv, sizeof(serv)) == -1) 
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	// int new_fd = accept(fd, (struct sockaddr *) &client, &cl_size);

	// if (new_fd == -1)
	// {
	// 	perror("accept error");
	// 	exit(EXIT_FAILURE);
	// }

	if (recvfrom(fd, str, sizeof(str), 0, (struct sockaddr *) &client, &cl_size) == -1)
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}

	printf("Получил от клиента: %s\n", str);

	strcpy(str,"Hello");

	if (sendto(fd, "Hello", sizeof(str), 0, (struct sockaddr *) &client, cl_size) == -1)
	{
		perror("sendto error");
		exit(EXIT_FAILURE);	
	}

	printf("Отправил клиенту: %s\n", str);

	close(fd);
	unlink("sock_serv");
    exit(EXIT_SUCCESS);
}