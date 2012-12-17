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

#include <application/ftp.h>
#include <application/http.h>
#include <application/smtp.h>
#include <application/pop.h>
#include <application/imap.h>

#include <verbosity.h>
#include <output.h>

extern int verbosity_level;

char * build_str_flags(const struct tcphdr * tcp_t) {
	char buffer[32];
	memset(buffer, '\0', 32);

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
	char * wor_str_flags = white_on_red(str_flags);

  char str_sport[6], str_dport[6], *red_sport, *red_dport;
  sprintf(str_sport, "%d", htons(tcp_t->source));
  sprintf(str_dport, "%d", htons(tcp_t->dest));
  red_sport = red(str_sport);
  red_dport = red(str_dport);

	V(2, "TCP - Port %s --> %s %s\n",red_sport, red_dport, wor_str_flags);
	VV(2, "Data Offset : %d - SEQ : %x - ACK_SEQ : %x\n", tcp_t->doff, htonl(tcp_t->seq), htonl(tcp_t->ack_seq));
	VVV(2,"Reserved : %x - Window Size : %d - Checksum : %x\n", tcp_t->res1, tcp_t->window, tcp_t->check);

	if(htons(tcp_t->source) == 21 || htons(tcp_t->dest) == 21) {
		decode_ftp(packet + tcp_t->doff * 4);
	} else if(htons(tcp_t->source) == 20 || htons(tcp_t->dest) == 20) {
		decode_ftp_data(packet + tcp_t->doff * 4);
	} else if(htons(tcp_t->source) == 80 || htons(tcp_t->dest) == 80) {
		decode_http(packet + tcp_t->doff*4);
	} else if(htons(tcp_t->source) == 25 || htons(tcp_t->dest) == 25) {
		decode_smtp(packet + tcp_t->doff*4);
	} else if(htons(tcp_t->source) == 110 || htons(tcp_t->dest) == 110) {
		decode_pop(packet + tcp_t->doff*4);
	} else if(htons(tcp_t->source) == 143 || htons(tcp_t->dest) == 143) {
		decode_imap(packet + tcp_t->doff*4);
  } else {
    V(3, "Unknown applicative protocol\n");
  }

  free(red_sport);
  free(red_dport);
	free(str_flags);
	free(wor_str_flags);
}
