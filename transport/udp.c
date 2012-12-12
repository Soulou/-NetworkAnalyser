/*
 * @File : udp.c
 *
 * @Author : Leo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary : Decode UDP
 *
 * @Version : 2012/12/09
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

#include <arpa/inet.h>
#include <netinet/udp.h>

#include <application/dhcp.h>
#include <application/dns.h>

#include <verbosity.h>

extern int verbosity_level;

void decode_udp(const u_char * packet) {
  const struct udphdr *udp_t;
  udp_t = (struct udphdr *)(packet);

	u_int16_t source = htons(udp_t->source);
	u_int16_t dest = htons(udp_t->dest);

	V(2, "UDP - Port %d --> %d\n", source, dest);
	VV(2, "Length : %d\n", htons(udp_t->len));
	VVV(2,"Checksum : %x\n", udp_t->check);

	if(source == 0x35 || dest == 0x35) {
		decode_dns(packet + sizeof(struct udphdr));
	} else if(source == 0x43 || dest == 0x43) {
		decode_dhcp(packet + sizeof(struct udphdr));
	}
}
