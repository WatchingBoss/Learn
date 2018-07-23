#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void sys_error(char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}

int main()
{
	int my_socket, from_accept;
	socklen_t len;
	struct sockaddr_in server_st, client_st;
	char buf[40] = {0};
	time_t current_time;
	pid_t pid;

	if( (my_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		sys_error("socket error");
	
	memset(&server_st, 0, sizeof(server_st));
	server_st.sin_family = AF_INET;
	server_st.sin_port = htons(13); // Datetime port
	inet_pton(AF_INET, "192.168.43.122", &server_st.sin_addr);

	if(bind(my_socket, (struct sockaddr *)&server_st, sizeof(server_st)) < 0)
		sys_error("bind error");

	if(listen(my_socket, 4) < 0)
		sys_error("listen error");

	for( ; ; )
	{
		len = sizeof(client_st);
		if( (from_accept = accept(my_socket, (struct sockaddr *)&client_st, &len)) < 0)
			sys_error("accept error");
		if( !(pid = fork()) )
		{
			close(my_socket);
			memset(buf, 0, sizeof(buf));
			printf("Address: %s Port: %d\n",
				   inet_ntop(AF_INET, &client_st.sin_addr, buf, sizeof(buf)),
				   ntohs(client_st.sin_port));

			memset(buf, 0, sizeof(buf));
			current_time = time(NULL);
			strftime(buf, sizeof(buf), "%A %F %T", localtime(&current_time));

			write(from_accept, buf, strlen(buf));

			memset(buf, 0, sizeof(buf));
			read(from_accept, buf, sizeof(buf));
			printf("%s", buf);

			close(from_accept);
			exit(EXIT_SUCCESS);
		}
		close(from_accept);
	}

	close(my_socket);

	return 0;
}
