/*
 * Simple server
 * Execute with arguments: 
 * -p <port number> -r <path>
 * post number 12000 and current of file path are used by default
 */

/*
 * TODO: How open html file?
 */

#include <stdio.h>      /* printf(); fprintf(); */
#include <string.h>     /* memset(); strtok(); strncmp(); strcpy(); */
#include <stdlib.h>     /* exit(); getenv(); */
#include <unistd.h>     /* write(); open(); close(); getopt(); */
#include <sys/socket.h> /* socket API; socket(); bind(); listen(); recv(); shutdown(); send(); */
#include <sys/types.h>  /* socket API; fork(); */
#include <netdb.h>      /* socket API; struct addrinfo; getaddrinfo(); freeaddrinfo(); */
#include <netinet/in.h> /* IP */
#include <netinet/ip.h> /* IP */
#include <sys/stat.h>   /*  */
#include <arpa/inet.h>  /*  */
#include <signal.h>     /*  */
#include <fcntl.h>      /*  */

#define CLIENT_MAX 10
#define BYTES 1024

char *root;
int listenfd, clients[CLIENT_MAX];
void fError(char *);
void serverStart(char *);
void respond(int);

int main(int argc, char *argv[])
{
	struct sockaddr_in clientAddress;
	socklen_t addrlen;
	char c;

	char port[6];
	root = getenv("PWD");
	strcpy(port, "12000");

	int slot = 0;

	while((c = getopt(argc, argv, "p:r:")) != -1)
	{
		switch(c)
		{
			case 'r':
				root = malloc(strlen(optarg));
				strcpy(root, optarg);
				break;
			case 'p':
				strcpy(port, optarg);
				break;
			case '?':
				fError("Wrong arguments\n");
				break;
			default:
				fError("Are you kidding?\n");
				break;
		}
	}

	printf("Server started at port %s%s%s with root directory as %s%s%s\n",
		   "\033[92m", port, "\033[0m",
		   "\033[92m", root, "\033[0m");

	for(int i = 0; i < CLIENT_MAX; ++i)
		clients[i] = -1;

	serverStart(port);

	while(1)
	{
		addrlen = sizeof(clientAddress);
		clients[slot] = accept(listenfd, (struct sockaddr *)&clientAddress, &addrlen);

		if(clients[slot] < 0)
			fError("accept() error");
		else
		{
			if(!fork())
			{
				respond(slot);
				fError("fork");
			}
		}

		while(clients[slot] != -1)
			slot = (slot + 1) % CLIENT_MAX;
	}

	return(0);
}

void fError(char *str)
{
	perror(str);
	exit(1);
}

void serverStart(char *port)
{
	struct addrinfo hints, *res, *p;

	/* Get address information for host */
	memset (&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;       // network uses IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP socket type
	hints.ai_flags = AI_PASSIVE;     // socket address will be suitable for binding a socket
									 // that will accept connections
	if(getaddrinfo(NULL, port, &hints, &res))
		fError("getaddrinfo error");

	for(p = res; p != NULL; p = p->ai_next)
	{
		listenfd = socket(p->ai_family, p->ai_socktype, 0); // create end point for communication
		if(listenfd == -1)
			continue;
		if(bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)  // bind name to socket
			break;
	}

	if(p == NULL)
		fError("socket() of bind()");

	freeaddrinfo(res);

	/* Listen for incomming connection */
	if(listen(listenfd, 1000000))
		fError("listen() error");
}

void respond(int slot)
{
	char mesg[1024],
		*reqline[3],
		dataToSend[BYTES],
		path[256];
	int rcvd,
		fd,
		bytesRead;

	memset((void *)mesg, (int)'\0', 1024);

	rcvd = recv(clients[slot], mesg, 1024, 0);

	if(rcvd < 0)
		fprintf(stderr, "recv() error");
	else if(rcvd == 0)
		fprintf(stderr, "Client disconnected unexpectedly\n");
	else // message received
	{
		printf("%s\n", mesg);

		reqline[0] = strtok(mesg, " \t\n");

		if(!strncmp(reqline[0], "GET\0", 4))
		{
			reqline[1] = strtok(NULL, " \t");
			reqline[2] = strtok(NULL, " \t\n");

			if(strncmp(reqline[1], "HTTP/1.0", 8) && strncmp(reqline[2], "HTTP/1.1", 8))
				write(clients[slot], "HTTP/1.0 400 bad request\n", 25);
			else
			{
				if(!strncmp(reqline[1], "/\0", 2))
					reqline[1] = "/index.html"; // no file -> open index.html by default

				strcpy(path, root);
				strcpy(&path[strlen(root)], reqline[1]);
				printf("file: %s\n", path);

				if((fd = open(path, O_RDONLY)) != -1)
				{
					send(clients[slot], "HTTP/1.0 200 OK", 17, 0);

					while((bytesRead = read(fd, dataToSend, BYTES)) > 0)
						write(clients[slot], dataToSend, bytesRead);
				}
				else
					write(clients[slot], "HTTP/1.0 404 Not Found", 23);
			}
		}
	}

	shutdown(clients[slot], SHUT_RDWR);
	close(clients[slot]);
	clients[slot] = -1;
}
