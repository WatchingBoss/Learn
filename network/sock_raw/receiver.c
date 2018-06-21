/* 
 * IPPROTO_RAW receiver
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum{false, true} bool;

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr    sockaddr;
typedef struct iphdr       iphdr;

int error(char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

void receiver()
{
	int s;
	sockaddr_in saddr;
	char packet[50];

	if((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
		error("socket() error (try root access)");

	memset(packet, 0, sizeof(packet));
	unsigned int fromlen = sizeof(saddr);

	while(true)
	{
		if(recvfrom(s, (char *)&packet, sizeof(packet), 0, (sockaddr *)&saddr, &fromlen) < 0)
			error("packet receive error");
		for(int i = sizeof(iphdr); i < sizeof(packet); ++i)
			fprintf(stderr, "%c", packet[i]);
		printf("\n");
	}
}

int main()
{
	receiver();

	return(0);
}
