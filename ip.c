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

#include "ip.h"
#include "verbosity.h"

extern int verbosity_level;

void decode_ip(const u_char * packet) {
  char * str_sip;
  char * str_dip;

  const struct ip *ip_t;
	/* const struct iphdr * ip_hdr; */
  ip_t = (struct ip *)(packet);
	/* ip_hdr = (struct iphdr *)(packet); */

  str_sip = inet_ntoa(ip_t->ip_src);
  str_sip = strndup(str_sip, strlen(str_sip));

  str_dip = inet_ntoa(ip_t->ip_dst);
  str_dip = strndup(str_dip, strlen(str_dip));

	if(ip_t->ip_v == 0x04) {
		V(1, "IPv4 - %s --> %s\n", str_sip, str_dip);
		if(verbosity_level >= 2) {
			VV(1, "Header length : %d - Length : %d\n",
					ip_t->ip_hl, ip_t->ip_len);
			VVV(1,"ID : %d - Fragment Offset : %d - TTL : %d\n",
					ip_t->ip_id, ip_t->ip_off, ip_t->ip_ttl);
		}
	} else {
		V(1,"IPv6 ?????");
	}

	free(str_dip);
	free(str_sip);
}

