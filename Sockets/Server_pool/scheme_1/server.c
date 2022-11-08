#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9006

void* server(void *arg) {
	int newport = *(int*)arg;
	char str[100];
	printf("я в потоке с портом %d\n", newport);

	struct sockaddr_in serv_2;
	struct sockaddr_in client_2;
	serv_2.sin_family = AF_INET;
    serv_2.sin_addr.s_addr = inet_addr("127.0.0.1"); //INADDR_ANY; //inet_addr("127.0.0.1")
    serv_2.sin_port = htons(newport);

    socklen_t cl_2_size = sizeof(client_2);
    printf("порт %d\n", serv_2.sin_port);
    printf("адрес %d\n", serv_2.sin_addr.s_addr);
    printf("создаю сокет\n");
	int new_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if (new_fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}
	
	printf("бинд\n");
	if (bind(new_fd, (struct sockaddr *) &serv_2, sizeof(serv_2)) == -1) 
	{
		perror("bind error");
		exit(EXIT_FAILURE);
	}

	printf("ресив\n");
	while(1) 
	{
		if (recvfrom(new_fd, str, sizeof(str), 0, (struct sockaddr *) &client_2, &cl_2_size) == -1)
		{
			perror("recvfrom error");
			exit(EXIT_FAILURE);	
		}
		printf("Получил от клиента %s\n", str);
	}
	close(new_fd);
}

int main()
{
	pthread_t thread;
	int status;
	int status_addr;

	pid_t name = getpid();
	char *pid = (char*)&name;
    int32_t newport;

    char str[10]="server";

	struct sockaddr_in serv;
	struct sockaddr_in client;
	serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr("127.0.0.1"); //inet_addr("127.0.0.1")
    serv.sin_port = htons(PORT);

    socklen_t cl_size = sizeof(client);
    
	while(1) 
	{
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


		if (recvfrom(fd, pid, sizeof(pid), 0, (struct sockaddr *) &client, &cl_size) == -1)
		{
			perror("recvfrom error");
			exit(EXIT_FAILURE);	
		}

		printf("Клиент %d подсоеденился\n", *(pid_t*)pid);

		newport = rand();
		newport++;
		char *data = (char*)&newport;

		if (sendto(fd, data, sizeof(data), 0, (struct sockaddr *) &client, cl_size) == -1)
		{
			perror("sendto from lister server error");
			exit(EXIT_FAILURE);	
		}

		printf("Отправил клиенту номер порта: %d\n", *(int*)data);
		
		status = pthread_create(&thread, NULL, server, &newport);
		if (status != 0) {
			perror("pthread_create error");
			exit(EXIT_FAILURE);
		}

	   
	
		close(fd);
	}
	// status = pthread_join(thread, (void**)&status_addr);
	// if (status != 0) {
	// 	perror("pthread_join error");
	// 	exit(EXIT_FAILURE);
	// }
	exit(EXIT_SUCCESS);

}