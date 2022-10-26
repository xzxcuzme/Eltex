#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define PORT 9006

int main()
{
	pid_t name=getpid();
	char *pid = (char*)&name;
    int32_t newport;
    char *data = (char*)&newport;

    char str[10]="client";

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

	if (sendto(fd, pid, sizeof(pid), 0, (struct sockaddr *) &serv, serv_size) == -1) 
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}

	printf("Отправил серверу: %d\n", *(pid_t*)pid);

	if (recvfrom(fd, data, sizeof(data), 0, (struct sockaddr *) &serv, &serv_size) == -1) 
	{
		perror("recvfrom error");
		exit(EXIT_FAILURE);	
	}

	printf("Получил от сервера: %d\n", *(int32_t*)data);
	
	//while(1)
	//{
		serv.sin_port = htons(*(int32_t*)data);
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
	//}

	close(fd);
    exit(EXIT_SUCCESS);
}