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
#include <netinet/in.h>
#include <netinet/ip.h>

#include <network/ip.h>
#include <network/icmp.h>
#include <transport/tcp.h>
#include <transport/udp.h>

#include <verbosity.h>
#include <output.h>

extern int verbosity_level;

void decode_ip(const u_char * packet) {
  char * str_sip, * str_dip, * b_str_dip, * b_str_sip;

  const struct ip *ip_t;
  ip_t = (struct ip *)(packet);

  str_sip = inet_ntoa(ip_t->ip_src);
  str_sip = strndup(str_sip, strlen(str_sip));

  str_dip = inet_ntoa(ip_t->ip_dst);
  str_dip = strndup(str_dip, strlen(str_dip));
	b_str_dip = bold(str_dip);
	b_str_sip = bold(str_sip);

	V(1, "IPv4 - %s --> %s\n", b_str_sip, b_str_dip);
	VV(1, "Header length : %d - Length : %d\n",
			ip_t->ip_hl, ip_t->ip_len);
	VVV(1,"ID : %d - Fragment Offset : %d - TTL : %d\n",
			ip_t->ip_id, ip_t->ip_off, ip_t->ip_ttl);

	// If there are options, we need to set the pointer after
	// them, so we don't use the sizeof(struct ip), but we
	// calculate the real offset according to the IHL field
	int offset = ip_t->ip_hl * 4;
	switch(ip_t->ip_p) {
		case 0x01:
			decode_icmp(packet + offset);
			break;
		case 0x06:
			decode_tcp(packet + offset);
			break;
		case 0x11:
			decode_udp(packet + offset);
			break;
	}

	free(str_dip);
	free(str_sip);
	free(b_str_dip);
	free(b_str_sip);
}

