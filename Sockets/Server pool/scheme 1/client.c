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
	char str[10]="Hi";
	int newport;
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(PORT);
	socklen_t serv_size = sizeof(serv);

	int fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (recvfrom(fd, &newport, sizeof(newport), 0, (struct sockaddr *) &serv, &serv_size) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}
	close(fd);

 	serv.sin_port = htons(newport);

	int new_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (new_fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (sendto(new_fd, str, sizeof(str), 0, (struct sockaddr *) &serv, serv_size) == -1) 
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}

	printf("Отправил серверу: %s\n", str);
   	
	if (recvfrom(new_fd, str, sizeof(str), 0, (struct sockaddr *) &serv, &serv_size) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}

	printf("Получил от сервера: %s\n", str);

	close(new_fd);
    exit(EXIT_SUCCESS);
}