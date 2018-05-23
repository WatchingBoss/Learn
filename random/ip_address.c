/* 
 * Get and display IP address
 */

/*
 * Problem:
 * Display the IP address of the system
 *
 * Solution:
 * 1. Create a socket to define network interface IPv4
 * 2. Define the IPv4 address type
 * 3. Define the port name where network is attached
 * 4. Access the network interface information by passing address using ioctl
 * 5. Extract the IP address
 */

#include <stdio.h>
#include <string.h>      // strncpy()
#include <sys/socket.h>  // socket(), SOCK_DGRAM
#include <sys/ioctl.h>   // ioctl(), SIOCGIFADDR
#include <net/if.h>      // struct ifreq, IFNAMSIZ
#include <unistd.h>      // close()
#include <arpa/inet.h>   // inet_ntoa(), struct sockaddr_in
	
int main()
{
	int n;
	struct ifreq ifr;
	char *array = "eth0";
	
	/* Create a socket to define network interface IPv4 using
	 * statement socket(AF_INET, SOCK_DGRAM, 0) and store it in the
	 * variable n */
	n = socket(AF_INET, SOCK_DGRAM, 0);

	/* Type of address to retrieve - IPv4 IP address */
	ifr.ifr_addr.sa_family = AF_INET;

	/* Define the port name where network is attached using
	 * statement strncpy(ifr.ifr_name , array , IFNAMSIZ – 1), where
	 * array is initialized with string “etho” */
	/* Copy the interface name in the ifreq structure */
	strncpy(ifr.ifr_name, array, IFNAMSIZ - 1);

	/* Call the ioctl function to access the network interface information by passing the address. */
	ioctl(n, SIOCGIFADDR, &ifr);

	close(n);
	/* Use this (inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr)->sin_addr)) 
	 * to extract the IP address and print the same as output */
	printf("IP Address is %s - %s\n", array,
		   inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

	return(0);
}

