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
	char str[10]="Hi";
	struct sockaddr_un serv;
    serv.sun_family=AF_LOCAL;
    strcpy(serv.sun_path, "sock_serv");
	socklen_t serv_size = sizeof(serv);

	struct sockaddr_un client;
    client.sun_family=AF_LOCAL;
    //strcpy(client.sun_path, "sock_cl");

	int fd = socket(AF_LOCAL, SOCK_DGRAM, 0);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	//видимо connect не работает с AF_LOCAL и SOCK_DGRAM, поэтому сделан bind

	// if (connect(fd, (struct sockaddr *) &serv, serv_size) == -1)
	// {
	// 	perror("connect error");
	// 	exit(EXIT_FAILURE);
	// }

	bind(fd, (struct sockaddr *) &client, sizeof(struct sockaddr_un));

	if (sendto(fd, str, sizeof(str), 0, (struct sockaddr *) &serv, serv_size) == -1) 
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}

	printf("Отправил серверу: %s\n", str);
   	
	if (recvfrom(fd, str, sizeof(str), 0, (struct sockaddr *) &serv, &serv_size) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}

	printf("Получил от сервера: %s\n", str);

	close(fd);
	//unlink("sock_cl");
    exit(EXIT_SUCCESS);
}