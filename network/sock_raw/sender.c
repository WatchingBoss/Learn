/*
 * Sender
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEST "127.0.0.1"

typedef enum{false, true} bool;

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr    sockaddr;
typedef struct in_addr     in_addr;
typedef struct iphdr       iphdr;

int error(char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

void sender()
{
	int s;
	sockaddr_in destAddr;
	char packet[50];
	iphdr *ip = (iphdr *)packet;

	if((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
		error("socket() error (try root)");

	destAddr.sin_family = AF_INET;
	destAddr.sin_port = 0; // not needed in SOCK_RAW
	inet_pton(AF_INET, DEST, (in_addr *)&destAddr.sin_addr.s_addr);
	memset(destAddr.sin_zero, 0, sizeof(destAddr.sin_zero));
	memset(packet, 'A', sizeof(packet));

	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = htons(40);
	ip->frag_off = 0;
	ip->ttl = 65;
	ip->protocol = IPPROTO_RAW;
	ip->check = 0;
	ip->saddr = destAddr.sin_addr.s_addr;
	ip->daddr = destAddr.sin_addr.s_addr;

	while(true)
	{
		sleep(1);
		if(sendto(s, (char *)packet, sizeof(packet), 0,
				  (sockaddr *)&destAddr, (socklen_t)sizeof(destAddr)) < 0)
			error("packet send error");
	}
}

int main()
{
	sender();

	return(0);
}
