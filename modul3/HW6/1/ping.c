#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ping_pht_size 64

struct ping_pkt_t {
  struct icmp hdr;
  char msg[ping_pht_size];
};

struct ip_pkt_t {
  struct ip ip_hdr;
  struct ping_pkt_t ping_pkt;
};

ushort checksum(void *b, int len) {
  ushort *buf = b;
  uint sum = 0;
  ushort result;

  for (sum = 0; len > 1; len -= 2) {
    sum += *buf++;
  }
  if (len == 1) {
    sum += *(unsigned char *)buf;
  }
  sum = (sum >> 16) + (sum & 0xFFFF);
  sum += (sum >> 16);
  result = ~sum;
  return result;
}

int ans = 0;
int socket_fd;

void sig_handler() {
  printf("%d\n", ans);

  exit(0);
}

int main(int argc, char *argv[]) {
  struct sigaction act;
  act.sa_handler = sig_handler;
  sigaction(SIGALRM, &act, NULL);

  const char *ip_str = argv[1];
  in_addr_t ip = inet_addr(ip_str);
  struct sockaddr_in ipv4_addr = {.sin_family = AF_INET, .sin_addr = ip};

  int timeout = atoi(argv[2]);
  int interval = atoi(argv[3]);

  socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

  alarm(timeout); // set alarm for timeout seconds

  for (int i = 0;; ++i) {
    struct ping_pkt_t ping_pkt;
    bzero(&ping_pkt, sizeof(struct ping_pkt_t));

    int j = 0;
    for (; j < sizeof(ping_pkt.msg) - 1; ++j) {
      ping_pkt.msg[j] = j + 'a';
    }
    ping_pkt.msg[j] = 0;
    ping_pkt.hdr.icmp_hun.ih_idseq.icd_id = i;
    ping_pkt.hdr.icmp_type = ICMP_ECHO;
    ping_pkt.hdr.icmp_hun.ih_idseq.icd_seq = 0;
    ping_pkt.hdr.icmp_cksum = checksum(&ping_pkt, sizeof(struct ping_pkt_t));
    const short reply_id = ping_pkt.hdr.icmp_hun.ih_idseq.icd_id;

    sendto(socket_fd, &ping_pkt, sizeof(ping_pkt), 0,
           (struct sockaddr *)&ipv4_addr, sizeof(ipv4_addr));

    struct ip_pkt_t ip_pkt;
    struct sockaddr_in from_addr;
    socklen_t socklen = sizeof(struct sockaddr_in);
    recvfrom(socket_fd, &ip_pkt, sizeof(ip_pkt), 0,
             (struct sockaddr *)&from_addr, &socklen);

    if (ipv4_addr.sin_addr.s_addr == from_addr.sin_addr.s_addr &&
        reply_id == ip_pkt.ping_pkt.hdr.icmp_hun.ih_idseq.icd_id) {
      ++ans;
    }
    usleep(interval);
  }
}