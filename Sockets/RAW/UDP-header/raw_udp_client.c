#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>

#define SOURCE_PORT 7777
#define DEST_PORT 9006
#define MESSAGE_SIZE 256

char* message(char* udp_msg, char* msg, uint32_t source_port, uint32_t dest_port, uint32_t checksum) {

	((struct udphdr*)udp_msg)->dest = dest_port;
	((struct udphdr*)udp_msg)->source = source_port;
	((struct udphdr*)udp_msg)->len = htons(sizeof(struct udphdr) + sizeof(struct ip));
	((struct udphdr*)udp_msg)->check = checksum;

	strncpy((udp_msg + sizeof(struct udphdr)), msg, sizeof(struct udphdr));
	return udp_msg;
}

int main()
{
	char str[]="client";
	char msg[MESSAGE_SIZE];
	char buf[MESSAGE_SIZE];

	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK); 
	serv.sin_port = htons(SOURCE_PORT);
	socklen_t serv_size = sizeof(serv);

	message(msg, str, htons(SOURCE_PORT), htons(DEST_PORT), 0);

	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (sendto(fd, (char *)msg, sizeof(struct udphdr) + sizeof(msg), 0, (struct sockaddr *) &serv, serv_size) == -1) 
	{
		perror("sendto error");
		exit(EXIT_FAILURE);
	}

	printf("Отправил серверу: %s\n", str);

	while(1) 
	{
		if (recvfrom(fd, (char *)buf, sizeof(buf), 0, (struct sockaddr *) &serv, &serv_size) == -1) 
		{
			perror("recvfrom error");
			exit(EXIT_FAILURE);	
		}

		printf("Получил от сервера: %s\n", buf + sizeof(struct ip) + sizeof(struct udphdr));
	}

	close(fd);
	exit(EXIT_SUCCESS);
}