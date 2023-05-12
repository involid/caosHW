#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//Sourec - https://a-khakimov.github.io/posts/ping-in-c/

size_t unique_id = 0;
int ans = 0;
#define ping_pkt_data_size  64

typedef struct {
	struct icmp hdr;
	char data[ping_pkt_data_size];
} ping_pkt_t;

typedef struct {
    struct ip ip_hdr;
    ping_pkt_t ping_pkt;
} ip_pkt_t;

static ushort checksum(void *b, int len)
{
    ushort *buf = b;
    uint sum=0;
    ushort result;

    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }
    if (len == 1) {
        sum += *(unsigned char*)buf;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void prepare_icmp_pkt(ping_pkt_t* ping_pkt) {
	memset(ping_pkt, 0, sizeof(ping_pkt_t));
	int i = 0;
    for (; i < sizeof(ping_pkt->data) - 1; ++i) {
        ping_pkt->data[i] = i + 'a';
    }
    ping_pkt->data[i] = 0;
	ping_pkt->hdr.icmp_hun.ih_idseq.icd_id = unique_id;
	ping_pkt->hdr.icmp_type = ICMP_ECHO;
    ping_pkt->hdr.icmp_hun.ih_idseq.icd_seq = 0;
    ping_pkt->hdr.icmp_cksum = checksum(ping_pkt, sizeof(ping_pkt_t));
	++unique_id;
}

int ping(const char* ip, int timeout, int interval) {
	alarm(timeout);
	int icmp_socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	while (1) {
		ping_pkt_t ping_pkt;
		prepare_icmp_pkt(&ping_pkt);
		const short reply_id = ping_pkt.hdr.icmp_hun.ih_idseq.icd_id;
		struct sockaddr_in to_addr = {
				.sin_family = AF_INET, .sin_addr = inet_addr(ip)};
    	socklen_t socklen = sizeof(struct sockaddr_in);
    	sendto(icmp_socket_fd, &ping_pkt, sizeof(ping_pkt_t), 0, (struct sockaddr*)&to_addr, socklen);
		ip_pkt_t ip_pkt;
		struct sockaddr_in from_addr;
		socklen = sizeof(struct sockaddr_in);
		recvfrom(icmp_socket_fd, &ip_pkt, sizeof(ip_pkt_t), 0, (struct sockaddr*)&from_addr, &socklen);
		if (to_addr.sin_addr.s_addr == from_addr.sin_addr.s_addr
                    && reply_id == ip_pkt.ping_pkt.hdr.icmp_hun.ih_idseq.icd_id) {
			++ans;
        }
		usleep(interval);
	}
	close(icmp_socket_fd);
	return ans;	
}

void handler(int signum) {
	printf("%d\n", ans);
	exit(0);
}

int main(int argc, char* argv[]) {
	const char* ip = argv[1];
	int timeout = atoi(argv[2]);
	int interval = atoi(argv[3]);

	struct sigaction act;
	act.sa_handler = handler;
	sigaction(SIGALRM, &act, NULL);

	printf("%d\n", ping(ip, timeout, interval));
}