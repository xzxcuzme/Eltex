#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 9002

int main()
{
	char str[10] = "hello";
	struct sockaddr_in serv;
	struct sockaddr_in client;
	serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1")
    serv.sin_port = htons(PORT);

    socklen_t cl_size = sizeof(client);

	int fd = socket(AF_INET, SOCK_DGRAM, 0);

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
	void *ptr;
	*ptr = int newport;
	newport = PORT;
	newport++;

	if (sendto(fd, newport, sizeof(newport), 0, (struct sockaddr *) &client, cl_size) == -1)
	{
		perror("sendto error");
		exit(EXIT_FAILURE);	
	}

	printf("Отправил клиенту номер порта: %d\n", newport);

	pid_t pid = fork();

	if (pid == -1) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
	{	
		serv.sin_port = htons(PORT);

		int new_fd = socket(AF_INET, SOCK_DGRAM, 0);

		if (new_fd == -1) 
		{
			perror("socket create error");
			exit(EXIT_FAILURE);
		}

		if (recvfrom(new_fd, str, sizeof(str), 0, (struct sockaddr *) &client, &cl_size) == -1)
		{
			perror("recvfrom error");
			exit(EXIT_FAILURE);	
		}

		printf("Получил от клиента: %s\n", str);

		strcpy(str,"Hello");

		if (sendto(new_fd, "Hello", sizeof(str), 0, (struct sockaddr *) &client, cl_size) == -1)
		{
			perror("sendto error");
			exit(EXIT_FAILURE);	
		}

		printf("Отправил клиенту: %s\n", str);

		close(new_fd);
	    exit(EXIT_SUCCESS);
	}
	else 
	{
		close(fd);
		exit(EXIT_SUCCESS);
	}
}