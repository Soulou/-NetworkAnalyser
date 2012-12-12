/*
 * @File : dns.c
 *
 * @Author : Leo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary : Decode DNS packet
 *
 * @Version : 2012/12/11
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

#include <application/dns.h>

#include <verbosity.h>

extern int verbosity_level;

void print_dns_field(u_int16_t type) {
		switch(type) {
			case DNS_A:
				V(0, " [A] ");
				break;
			case DNS_NS:
				V(0, " [NS] ");
				break;
			case DNS_CNAME:
				V(0, " [CNAME] ");
				break;
			case DNS_SOA:
				V(0, " [SOA] ");
				break;
			case DNS_MX:
				V(0, " [MX] ");
				break;
			case DNS_AAAA:
				V(0, "[AAAA] ");
				break;
			default:
				V(0,"[0x%04x] ", type);
		}
}

void print_dns_class(u_int16_t class) {
	VV(0, "Type : ");
	switch(class) {
		case DNS_IN:
			VV(0, "IN");
			break;
		case DNS_ANY:
			VV(0, "ANY");
			break;
		default:
			VV(0, "%x", class);
			break;
	}
}

void decode_dns(const u_char * packet) {
	
	const struct dns_hdr * dns_t;
	const struct dns_ans * dns_ans_t;
	dns_t = (struct dns_hdr *)(packet);

	if(!(dns_t->flags >> 15)) {
		V(3, "DNS Request : ");
	} else {
		V(3, "DNS Response : ");
	}
	V(0, "(ID %d) ", htons(dns_t->id));

	const u_char * dns_data = packet + sizeof(struct dns_hdr);

	int offset = 0, next_length;
	int nb_qu = htons(dns_t->qdcount);
	int nb_ans = htons(dns_t->ancount);

	u_char buffer[256];
	bzero(buffer,256);
	while(nb_qu > 0) {
		next_length = dns_data[offset];
		memcpy(buffer, dns_data + offset + 1, next_length);
		buffer[next_length] = '\0';
		V(0, "%s.", buffer);
		offset += (next_length + 1);
		if(!dns_data[offset]) {
			offset++;
			print_dns_field(htons(*((u_int16_t *)(dns_data + offset))));
			offset += sizeof(u_int16_t);
			print_dns_class(htons(*((u_int16_t *)(dns_data + offset))));
			offset += sizeof(u_int16_t);
			V(0, "\n");
			nb_qu--;
		}
	}
	
	struct in_addr ip;
  char str_ip[INET6_ADDRSTRLEN];

	while(nb_ans > 0) {
		dns_ans_t = (struct dns_ans *)(dns_data + offset);
		V(3, "Answer (TTL %d) ", htons(dns_ans_t->ttl));
		print_dns_field(htons(dns_ans_t->type));

		offset += sizeof(struct dns_ans);
		memcpy(buffer, dns_data + offset, htons(dns_ans_t->length));
		buffer[htons(dns_ans_t->length)] = '\0';

		if(htons(dns_ans_t->type) == DNS_A) {
			ip.s_addr = *(u_int32_t*)(buffer);
			V(0, "%s\n", inet_ntoa(ip));
		} else if(htons(dns_ans_t->type) == DNS_MX) {
			V(0, "%s\n", buffer);
		} else if(htons(dns_ans_t->type) == DNS_AAAA) {
			inet_ntop(AF_INET6, (u_int32_t*)(buffer), str_ip, INET6_ADDRSTRLEN);
			V(0, "%s\n", str_ip);
		} else {
			V(0, "%s\n", buffer);
		}
		offset += htons(dns_ans_t->length);
		nb_ans--;
	}
}




