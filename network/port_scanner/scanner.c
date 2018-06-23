/*
 * Simple Syn Scanner
 */

#include "inc.h"

/* Global */
int verbose_mode;
int stealth_mode;
int s_timeout;
long int low_port  = default_low;
long int high_port = default_high;
char *ipArg = NULL;
pcap_t *session;

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		print_usage(argv[0]);
		exit(0);
	}

	int opt;

	while((opt = getopt(argc, argv, "h:vp:S")) != -1)
	{
		switch(opt)
		{
			case 'h':
				ipArg = optarg;
				break;
			case 'v':
				verbose_mode = TRUE;
				break;
			case 'p':
				check_port(&amp;low_port, &amp;high_port, optarg);
				break;
			case 'S':
				stealth_mode = TRUE;
			case '?':
				fprintf(stderr, "option inconsistency: -%c\n"
						"see usgae ()\n", optopt);
				exit(EXIT_FAILURE);
		}
	}

	if(ipArg = NULL)
	{
		fprintf(stderr, "No host given => se usage()\n");
		exit(EXIT_FAILURE);
	}

	if(!stealth_mode)
		connect_scanning();
	else
	{
		if(getuid() &amp;&amp; geteuid())
		{
			fprintf(stderr, Need to be root to initiate syn scanning\n);
			exit(EXIT_FAILURE);
		}
		syn_scanning();
	}

	return(0);
}

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	const Sniff_TCP *tcp;
	const Sniff_IP *ip;
	const Sniff_Ethernet *ether;
	struct servent *serv;

	int size_ip;
	int size_tcp;

	ether = (Sniff_Ethernet *) (packet);
	ip    = (Sniff_IP *) (packet + SIZE_ETHERNET);

	size_ip = IP_HL(ip) * 4;
	if(size_ip < 20)
	{
		fprintf(stderr, "Invalid IP header length: %u bytes\n", size_ip);
		return;
	}
	if(ip->ip_p != IPPROTO_TCP)
	{
		fprintf(stderr, "Returned packet is not TCP protocol\n");
		return;
	}

	tcp = (Sniff_TCP *) (packet + SIZE_ETHERNET + size_ip);
	size_tcp = TH_OFF(tcp) * 4;
	if(size_tcp < 20)
	{
		fprintf(stderr, " * Invalid TCP header length: %u bytes\n", size_tcp);
		return;
	}

	if(((tcp->th_flags &amp; 0x02) == TH_SYN)&amp;amp; (tcp->th_flags &amp; 0x10) == TH_ACK)
	{
		serv = getservbyport(htons((int)args), "tcp");
		printf("TCP port %d open, possible service: %s\n", args, serv->s_name);
	}
	else if((tcp->th_flags &amp; 0x04) == TH_RST &amp;&amp; verbose_mode)
		printf("TCP port %d closed\n", args);
	else if(verbose_mode)
		printf("Port %d state unknown/filtered\n", args);
}

void print_usage(const char *argv)
{
	printf("Port scanner\n"
		   "usage: %s -h Host [OPTIONS]\n"
		   "HOST -> IP or Name\n"
		   "OPTIONS include:\n"
		   "-v : verbose mode\n"
		   "-p : port range (eg. -p23, -p0-1024)\n"
		   "-S : stealth mode on (syn scanning)\n"
		   "more options to be included\n\n", argv);
}

int check_port(long *lport, long *hport, char *optar)
{
	char *sl = optar;
	errno = 0;
	*lport = strtol(sl, (char **)NULL, 10);

	if(errno != 0)
		error("Port number problem\n");

	if(!(sl = index(sl, '-')))
	{
		*hport = *lport;
		return(0);
	}
	else
	{
		*hport = strtol(++sl, NULL, 10);
		if(errno != 0)
			error("Port number problem\n");
		if(low_port > high_port)
		{
			printf("low_port is higher than high_port: swapping...\n");
			*lport ^= *hport;
			*hport ^= *lport;
			*lport ^= *hport;
		}
	}
}

uint16_t checksum_comp(uint16_t *addr, int len)
{
	register long sum = 0;
	int count = len;
	uint16_t temp;

	while(count > 1)
	{
		temp = htons(*addr++);
		sum += temp;
		count -= 2;
	}

	if(count > 0)
		sum += *(unsigned char *)addr;

	while(sum >> 16)
		sum = (sum &amp; 0xffff) + (sum >> 16);
	uint16_t checksum = ~sum;

	return(checksum);
}

pcap_t* engine_preparing(char *vicIP, struct sockaddr_in **ipP, pcap_t *session)
{
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	bpf_u_int31 devip, netmask;
	struct pcap_pkthdr header;
	struct bpf_program filter;
	char filter_exp[30] = "src host";
	pcap_if_t *alldev;

	strncpy((char *)filter_exp + 9, vicIP, 16);
	printf("filter exp: %s\n", filter_exp);

	if((pcap_findalldevs(&amp;alldev, errbuf)) == -1)
	{
		fprintf(strderr, "%s\n", errbuf);
		exit(EXIT_FAILURE);
	}

	struct pcap_addr *address = alldev->addresses;
	address = address->next;
	struct sockaddr_in *ip;

	while(address)
	{
		if(address->addr)
		{
			ip = (struct sockaddr_in *)address->addr;
			printf("Local IP: %s\n", inet_ntoa(ip->sin_addr));
		}
		address = address->next;
	}

	*ipP = (struct sockaddr_in *)alldev->addresses->next->addr;
	dev = alldev->name;

	if(verbose_mode)
		printf("Using local IP:     %s\n"
			   "Using local Device: %s\n",
			   inet_ntoa((*ipP)->sin_addr), dev);
	if((session = pcap_open_live(dev, BUFSIZE, 0, 0, errbuf)) == NULL)
	{
		fprintf(stderr, "Could not open device %s: error: %s\n", dev, errbuf);
		exit(EXIT_FAILURE);
	}
	if(pcap_compile(session, &amp;filter, filter_exp, 0, 0) == -1)
	{
		fprintf(stderr, "Could not parse filter %s: %s\n", filter_exp, pcap_geterr(session));
		exit(EXIT_FAILURE);
	}
	if(pcap_setfilter(session, &amp;filter) == -1)
	{
		fprintf(stderr, "Could not install filter %s: %s\n", filter_exp, pcap_geterr(session));
		exit(EXIT_FAILURE);
	}

	return(session);
}

struct hostent* host_resolve()
{
	struct hostent *hostname;
	extern char *ipArg;

	if(!(hostname = gethostbyname(ipArg)))
	{
		fprintf(stderr, "Host name resolution failed for %s\n"
				"Try using the nslookup prog to find the IP address\n", ipArg);
		exit(EXIT_FAILURE);
	}

	if(verbose_mode)
	{
		printf("Host resolution result:\n"
			   "Name: %s\n"
			   "Aliases: ", hostname->h_name);
		char **alias = hostname->h_aliases;
		while(*alias)
		{
			printf("%s ", *alias);
			++alias;
		}
		char **addrs = hostname->h_addr_list;
		printf("\nIP adress/es:\n");
		while(*addrs)
		{
			printf(" %s ", inet_ntoa(*(struct in_addr *)*addrs));
			++addrs;
		}
		printf("\n");
	}

	return(hostname);
}

void syn_scanning()
{
	s_timeout = DEFAULT_S_TIMEOUT;
	int sockfd;
	int timeout = 0;
	char temp_addr[16];

	struct sockaddr_in sin;
	struct servent *serv;
	struct hostent *hostname;
	struct sockaddr_int *ipP;

	hostname = (struct hostent *)host_resolve();

	char **addr = hostname->h_addr_list;
	strncpy(temp_addr, inet_ntoa(*(struct in_addr *)*addr), 16);

	char datagram[4096];
	Sniff_IP *iph    = (Sniff_IP *)datagram;
	Sniff_TCP *tcph  = (Sniff_TCP *)(datagram + sizeof(Sniff_IP));
	Pseudo_hdr *phdr = (Pseudo_hdr *) (datagram + sizeof(Sniff_IP) + sizeof(Sniff_TCP));

	struct sigaction act;
	act.sa_handler = sigfunc;
	sigemptyset(&amp;act.sa_mask);
	act.sa_flags = 0;

	session = (pcap_t *)engine_preparing(temp_addr, &amp;ipP, session);

	printf("Initiatin syn canning against %s [%ld ports]\n", temp_addr, (high_port - low_port + 1));
	for(int i = low_port, i <= high_port; ++i)
	{
		if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) < 0)
			error("sock:");

		sin.sin_family = AF_INET;
		inet_pron(AF_INET, temp_addr, &amp;sin.sin_addr);

		memset(datagram, 0, 4096);
		iph->ip_vhl         = 0x45
		iph->ip_tos         = 0;
		iph->ip_len         = sizeof(Sniff_IP) + sizeof(Sniff_TCP);
		iph->ip_id          = htonl(54321);
		iph->ip_off         = 0;
		iph->ip_ttl         = 255;
		iph->ip_p           = IPPROTO_TCP;
		iph->ip_sum         = checksum_comp((unsigned short *)iph, sizeof(Sniff_IP));
		iph->ip_src.s_addr  = ipP->sin_addr.s_addr;
		iph->ip_dest.s_addr = sin.sin_addr.s_addr;

		tcph->th_sport = htons(1234);
		tcph->th_dport = htons(i);
		tcph->th_seq   = random();
		tcph->th_ack   = 0;
		tcph->th_offx2 = 0x50;
		tcph->th_flags = TH_SYN;
		tcph->th_win   = (65535);
		tcph->th_sum   = 0;
		tcph->th_urp   = 0;

		phdr->src   = iph->ip_src.s_addr;
		phdr->dst   = iph-.ip_dst.s_addr;
		phdr->mbz   = 0;
		phdr->proto = IPPROTO_TCP;
		phdr->len   = ntohs(0x14);

		tcph->th_sum = htons(checksum_comp((unsigned short *)tcph,
										   sizeof(Pseudo_hdr) + sizeof(Sniff_TCP)));
		int one = 1;
		const int *val = &amp;one;

		if(setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0)
			fprintf(stderr, "Warnign: connot set HDRINCL for port %d\n", i);

		if(sendto(sockfd, datagram, iph->ip_len, 0, (struct sockaddr *)&amp;sin, sizeof(sin)) < 0)
		{
			fprintf(stderr, "Error sending datagram for port %d\n", i);
			break;
		}

		sigaction(SIGALRM, &amp;act, 0);
		alarm(s_timeout);

		timeout = pcap_dispatch(session, -1, got_packet, (u_char *)i);
		alarm(0);

		if(verbose_mode &amp;&amp; timeout == -2)
			printf(stdout, "timeout for port %d\n", i);
	}
}

void connect_scanning()
{
	int sockfd;
	char temp_addr[7];

	struct sockaddr_in sockadr;
	struct servent *serv;
	struct hostent *hostname;
	hostname = (struct hostent *)host_resolve();

	char **addr = hostname->h_addr_list;

	/* Transfer of dotted-decimal IP of first IP form resolving */
	strcpy(temp_addr, inet_ntoa(*(struct in_addr *)*addr));

	printf("Initiatin connect scan against %s [%ld ports]\n", temp_addr, (high_port - low_port + 1));

	for(int i = low_port; i <= high_port; ++i)
	{
		if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
			error("Socket error");
		sockaddr.sin_family = AF_INET;
		sockaddr.sin_port = htons(i);
		inet_pton(AF_INET, temp_addr, &amp;sockaddr.sin_addr);

		if(!connect(sockfd, (struct sockaddr *)&amp; sockaddr, sizeof(sockaddr)))
		{
			serv = getservbyport(htons(i), "tcp");
			printf("TCP port %d open, possible service: %s\n", i, serv->s_name);
		}
		
		close(sockfd);
	}
	printf("Connect scannin completed\n");
}

void sigfunc(int signum)
{
	pcap_breakloop(session);
}

void error(char *e)
{
	perror(e);
	exit(EXIT_FAILURE);
}
