/*
 * Simple Syn Scanner
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <pcap.h>

#define BUFSIZE           65535 /* max size of datagram */
#define TRUE              1    
#define FALSE             0    
#define default_low       1    
#define default_high      1024
#define DEFAULT_S_TIMEOUT 5     /* scanner waits for answer from host */
#define SNAP_LEN          1518  /* snamp length */
#define SIZE_ETHERNET     14    /* ethernet headers are 14 bytes */
#define ETHER_ADDR_LEN    6     /* ethernet addresses are 6 bytes */

/* Ethernet header */
typedef struct sniff_ethernet
{
	u_char ether_dhost[ETHER_ADDR_LEN]; /* destination host address*/
	u_char ether_shost[ETHER_ADDR_LEN]; /* source host address */
	u_char ether_type;
} Sniff_Ethernet;

/* IP header */
typedef struct sniff_ip
{
	u_char         ip_vhl;
	u_char         ip_tos;
	u_short        ip_len;
	u_short        ip_id;
	u_short        ip_off;
	#define        IP_RF      0x8000
	#define        IP_DF      0x4000
	#define        IP_MF      0x2000
	#define        IP_OFFMASK 0x1fff
	u_char         ip_ttl;
	u_char         ip_p;
	u_short        ip_sum;
	struct in_addr ip_src, ip_dest;
} Sniff_IP;

#define IP_HL(ip) (((ip)->ip_vhl) &amp; 0x0f)
#define IP_V(ip)  (((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

typedef struct sniff_tcp
{
	u_short th_sport;
	u_short th_dport;
	tcp_seq th_seq;
	tcp_seq th_ack;
	u_char  th_offx2;
#define TH_OFF(th) (((th)->th_offx2 &amp; 0xf0) >> 4)
	u_char th_flags;
	#define TH_FIN  0x01
	#define TH_SYN  0x02
	#define TH_RST  0x04
	#define TH_PUSH 0x08
	#define TH_ACK  0x10
	#define TH_URG  0x20
	#define TH_ECE  0x40
	#define TH_CWR  0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	u_short th_win;
	u_short th_sum;
	u_short th_urp;
} Sniff_TCP;

/* Pseudo header used for tcp checksuming*/
typedef struct pseudo_hdr
{
	u_int32_t src;
	u_int32_t dst;
	u_char    mbz;
	u_char    proto;
	u_int16_t len;
} Pseudo_hdr;

/* Global */
int verbose_mode;
int stealth_mode;
int s_timeout;
long in low_port  = default_low;
long in high_port = default_high;
char *ipArg = NULL;
pcap_t *session;

/* Function prototypes */
void got_packet(u_char *, const struct pcap_pkthdr *, const u_char *);
void print_usage(const char *);
int check_port(long *, long *, char *);
uint16_t checksum_comp(uint16_t *, int);
pcap_t* engine_preparing(char *, struct sockaddr_in **, pcap_t *);
struct hostent* host_resolve();
void syn_scanning();
void connect_scanning();
void sigfunc(int);
/* Function prototypes end */
