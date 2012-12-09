/*
 * @File : tcp.c
 *
 * @Author : Leo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary : Decode TCP
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
#include <string.h>

#include <arpa/inet.h>
#include <netinet/tcp.h>

#include <verbosity.h>

extern int verbosity_level;

char * build_str_flags(const struct tcphdr * tcp_t) {
	char buffer[30];
	memset(buffer, '\0', 30);

	if(tcp_t->fin)
		strcat(buffer, "|FIN");
	if(tcp_t->syn)
		strcat(buffer, "|SYN");
	if(tcp_t->rst)
		strcat(buffer, "|RST");
	if(tcp_t->psh)
		strcat(buffer, "|PUSH");
	if(tcp_t->ack)
		strcat(buffer, "|ACK");
	if(tcp_t->urg)
		strcat(buffer, "|URG");
	if(strlen(buffer) > 0)
		strcat(buffer, "|");

	return strndup(buffer, strlen(buffer)+1);	
}

void decode_tcp(const u_char * packet) {
  const struct tcphdr *tcp_t;
  tcp_t = (struct tcphdr *)(packet);

	char * str_flags = build_str_flags(tcp_t);

	V(2, "TCP - Port %d --> %d \e[1m%s\e[0m\n",
		 	htons(tcp_t->source), htons(tcp_t->dest), str_flags);
	/* VV(2, "Length : %d\n", udp_t->len); */
	/* VVV(2,"Checksum : %d\n", udp_t->check); */

	free(str_flags);
}
