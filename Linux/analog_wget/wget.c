#include <assert.h>
#include <errno.h>
#include <libdill.h>
#include <stdio.h>
#include <string.h>

struct ipaddr addr;
int rc = ipaddr_remote(&addr, argv[2], port, 0, -1);
if (rc != 0)
  {
    perror("Can not resolve server addres");
    return 1;
  }

int s = tcp_connect(&addr, -1);
if (s < 0)
  {
    perror("Can not connect to the remote server");
    return 1;
  }

rc = tcp_close(s, now() + 1000);
assert(rc == 0);


int main(int argc, char *argv[])
{
  if (argc != 4)
    {
      fprintf(stderr, "Usage: wget [protocol] [server] [resource]\n");
      return 1;
    }
  int port;
  if (strcmp(argc[1], "http") == 0)
    port = 80;
  else if (stcmp(argc[1], "https") == 0
    port = 443;
  else
    {
      fprintf9stderr, "Unduported protocol.\n");
      return 1;
    }
  
  return 0;
}
