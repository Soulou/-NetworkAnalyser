/*
 * @File : ip.c
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
 *
 * @Summary : Decoding IP header
 *
 * @Version : 2012/12/03
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <leo@unbekandt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return 
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/ip6.h>

#include <network/ip6.h>

#include <transport/tcp.h>
#include <transport/udp.h>

#include <output.h>
#include <verbosity.h>

extern int verbosity_level;

void decode_ip6(const u_char * packet) {
  char str_sip[INET6_ADDRSTRLEN];
  char str_dip[INET6_ADDRSTRLEN];
  char buffer[128];

  char * yellow_plen, *yellow_nxt, *b_sip, *b_dip;
	const struct ip6_hdr * ip_t;
	ip_t = (struct ip6_hdr *)(packet);

  inet_ntop(AF_INET6, &(ip_t->ip6_src), str_sip, INET6_ADDRSTRLEN);
  inet_ntop(AF_INET6, &(ip_t->ip6_dst), str_dip, INET6_ADDRSTRLEN);

  b_sip = bold(str_sip);
  b_dip = bold(str_dip);

  sprintf(buffer, "%d", htons(ip_t->ip6_ctlun.ip6_un1.ip6_un1_plen));
  yellow_plen = yellow(buffer);
  sprintf(buffer, "%x", ip_t->ip6_ctlun.ip6_un1.ip6_un1_plen);
  yellow_nxt = yellow(buffer);

	V(1, "IPv6 - %s --> %s\n", b_sip, b_dip);
	uint32_t flow = htonl(ip_t->ip6_ctlun.ip6_un1.ip6_un1_flow);
	VV(1, "Payload Length : %s - Next Header : %s\n", yellow_plen, yellow_nxt);
			/* htons(ip_t->ip6_ctlun.ip6_un1.ip6_un1_plen), ip_t->ip6_ctlun.ip6_un1.ip6_un1_nxt); */
	VVV(1,"Version : %d - Traffic Class : %x - Flow Label : %x - Hop Limit : %d\n",
			flow >> 28, (flow & 0x0ff00000) >> 20, flow & 0x000fffff,	ip_t->ip6_ctlun.ip6_un1.ip6_un1_hlim);

	int offset = sizeof(struct ip6_hdr);
	switch(ip_t->ip6_ctlun.ip6_un1.ip6_un1_nxt) {
		case 0x06:
			decode_tcp(packet + offset);
			break;
		case 0x11:
			decode_udp(packet + offset);
			break;
	}

  free(yellow_plen);
  free(yellow_nxt);
  free(b_sip);
  free(b_dip);
}

