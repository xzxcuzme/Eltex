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
#include <net/if.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>

#define DEST_PORT 9006
#define SOURCE_PORT 7777
#define MESSAGE_SIZE 256

short CRC16(char * ip_hdr) {
	int csum = 0;
    short* ptr = (short*)ip_hdr;

    for (int i = 0; i < 10; i++) {
    	csum+= *ptr;
    	ptr++;
    }

    short tmp = csum >> 16;
    csum = (csum & 0xFFFF) + tmp;
    ((struct iphdr*)ip_hdr)->check = ~csum;
    return 0;
}

char* message(char* ip_udp_msg, char* msg, uint32_t version, uint32_t ihl, uint32_t tot_len, uint32_t id, uint32_t frag_off,
 uint32_t ttl, uint32_t protocol, uint32_t check, uint32_t saddr, uint32_t daddr, uint32_t tos, unsigned char *source_mac, unsigned char *dest_mac, 
 uint32_t source_port, uint32_t dest_port, uint32_t len, uint32_t checksum) {
	((struct iphdr*)ip_udp_msg)->version = version;
	((struct iphdr*)ip_udp_msg)->ihl = ihl;
	((struct iphdr*)ip_udp_msg)->tot_len = tot_len;
	((struct iphdr*)ip_udp_msg)->id = id;
	((struct iphdr*)ip_udp_msg)->frag_off = frag_off;
	((struct iphdr*)ip_udp_msg)->ttl = ttl;
	((struct iphdr*)ip_udp_msg)->protocol = protocol;
	((struct iphdr*)ip_udp_msg)->check = check;
	((struct iphdr*)ip_udp_msg)->saddr = saddr;
	((struct iphdr*)ip_udp_msg)->daddr = daddr;
	((struct iphdr*)ip_udp_msg)->tos = tos;
	((struct ethhdr*)ip_udp_msg)->h_source[6] = *source_mac;
	((struct ethhdr*)ip_udp_msg)->h_dest[6] = *dest_mac;
	((struct ethhdr*)ip_udp_msg)->h_proto = htons(0x08);
	CRC16(ip_udp_msg);
	ip_udp_msg += sizeof(struct iphdr);
	
	((struct udphdr*)ip_udp_msg)->dest = dest_port;
	((struct udphdr*)ip_udp_msg)->source = source_port;
	((struct udphdr*)ip_udp_msg)->len = len;
	((struct udphdr*)ip_udp_msg)->check = checksum;
	strncpy(ip_udp_msg + sizeof(struct udphdr), msg, sizeof(struct iphdr));
	return ip_udp_msg;
}

int main()
{
	char str[20]="client";
	char payload[MESSAGE_SIZE];
	char buf[MESSAGE_SIZE];
	int OptVal = 1;
	int OptLen = sizeof(OptVal);
	unsigned char source_mac[6] = {0x18, 0xc0, 0x4d, 0x30, 0x32, 0xc5};
	unsigned char dest_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; //поменяю

	struct sockaddr_ll serv;
	serv.sll_family 			= AF_INET;   
	serv.sll_protocol 			= 0;
	serv.sll_ifindex 			= if_nametoindex("enp9s0");;  
	serv.sll_hatype 			= 0;   
	serv.sll_pkttype			= 0;  
	serv.sll_halen 				= 6;
	serv.sll_addr[6] 			= *source_mac;
	socklen_t serv_size			= sizeof(serv);
	//ip header
	uint32_t version 			= 4;
	uint32_t ihl 				= 5;
	uint32_t tot_len 			= htons(sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(payload));
	uint32_t id 				= 0;
	uint32_t frag_off 			= 0;
	uint32_t ttl 				= 128;
	uint32_t protocol 			= IPPROTO_UDP;
	uint32_t check 				= 0;
	uint32_t saddr				= htonl(INADDR_LOOPBACK); //поменяю
	uint32_t daddr 				= htonl(INADDR_LOOPBACK); //поменяю
	uint32_t tos 				= 0;
	//udp header
	uint32_t source_port 		= htons(SOURCE_PORT);
	uint32_t destination_port 	= htons(DEST_PORT);
	uint32_t len 				= htons(sizeof(struct udphdr) + sizeof(payload));
	uint32_t checksum 			= 0;

	message(payload, str, version, ihl, tot_len, id, frag_off, ttl, protocol, check, saddr, daddr, tos, source_mac, dest_mac, source_port, destination_port, len, checksum);

	int fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, (char *)&OptVal, OptLen) == -1)
	{
		perror("setsockopt error");
		exit(EXIT_FAILURE);
	}

	if (fd == -1) 
	{
		perror("socket create error");
		exit(EXIT_FAILURE);
	}

	if (sendto(fd, (char *)payload, sizeof(struct udphdr) + sizeof(struct ip) + sizeof(payload), 0, (struct sockaddr *) &serv, serv_size) == -1) 
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

		printf("Получил от сервера: %s\n", buf + sizeof(struct ip) + sizeof(struct udphdr) + sizeof(struct ethhdr));
	}

	close(fd);
	exit(EXIT_SUCCESS);
}