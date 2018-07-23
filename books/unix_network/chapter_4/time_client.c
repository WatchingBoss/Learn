#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void sys_error(char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

int main()
{
	int my_socket;
	struct sockaddr_in server_st;
	char buf[40] = {0};

	if( (my_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		sys_error("socket error");

	memset(&server_st, 0, sizeof(server_st));
	server_st.sin_family = AF_INET;
	server_st.sin_port = htons(13);
	inet_pton(AF_INET, "192.168.43.122", &server_st.sin_addr);

	if( connect(my_socket, (struct sockaddr *)&server_st, sizeof(server_st)) < 0)
		sys_error("listen error");

	read(my_socket, buf, sizeof(buf));

	printf("%s\n", buf);

	return 0;
}

