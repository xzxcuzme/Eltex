#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define DEST_PORT 9006
#define MESSAGE_SIZE 256

int main()
{
	char str[] = "server";
	char buf[MESSAGE_SIZE];
	struct sockaddr_in serv;
	struct sockaddr_in client;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //поменяю
	serv.sin_port = htons(DEST_PORT);

	socklen_t cl_size = sizeof(client);

	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd == -1)
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (bind(fd, (struct sockaddr*) &serv, sizeof(serv)) == -1)
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	if (recvfrom(fd, (char*)buf, sizeof(buf), 0, (struct sockaddr *) &client, &cl_size) == -1)
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);
	}

	printf("Получил от клиента: %s\n", buf);

	if (sendto(fd, (char*)str, sizeof(str), 0, (struct sockaddr *) &client, cl_size) == -1)
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}

	printf("Отправил клиенту: %s\n", str);

	close(fd);
	exit(EXIT_SUCCESS);
}