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

#include <verbosity.h>

extern int verbosity_level;

void decode_udp(const u_char * packet) {
	
  const struct udphdr *udp_t;
  udp_t = (struct udphdr *)(packet);

	V(2, "UDP - Port %d --> %d\n", htons(udp_t->source), htons(udp_t->dest));
	VV(2, "Length : %d\n", udp_t->len);
	VVV(2,"Checksum : %d\n", udp_t->check);
}
