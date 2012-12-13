/*
 * @File : ip.c
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
 *
 * @Summary : Decoding ARP header
 *
 * @Version : 2012/12/12
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

#include <net/if_arp.h>
#include <netinet/ether.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <network/arp.h>

#include <verbosity.h>
#include <output.h>

extern int verbosity_level;

char * str_arp_pro(short int pro) {
	switch(pro) {
		case 0x0800:
			return "IP";
			break;
		default:
			return "Unknown";
	}
}

char * str_arp_op(short int type) {
	switch(type) {
		case ARPOP_REQUEST :
			return "Request";
			break;
		case ARPOP_REPLY :
			return "Reply";
			break;
		case ARPOP_RREQUEST :
			return "RARP Request";
			break;
		case ARPOP_RREPLY:
			return "RARP Reply";
			break;
		case ARPOP_InREQUEST:
			return "InARP Request";
			break;
		case ARPOP_InREPLY:
			return "InARP Reply";
			break;
		case ARPOP_NAK:
			return "NAK";
			break;
		default:
			return "Unknown";
	}
}

char * str_arp_hw(short int hw) {
	switch(hw) {
		case 0x0001:
			return "Ethernet";
			break;
		default:
			return "Unknown";
			break;
	}
}

void decode_arp(const u_char * packet) {

	struct arphdr * arp_t;
	arp_t = (struct arphdr*)packet;

	V(1, "ARP %s ", str_arp_op(htons(arp_t->ar_op)));
	VV(0, "Protocol : %s\n", str_arp_pro(htons(arp_t->ar_pro)));
	VVV(1, "Hardware Type : %s\n", str_arp_hw(htons(arp_t->ar_hrd)));

	const u_char * arp_data = packet + sizeof(struct arphdr);

	u_char * hwd_addr = malloc(sizeof(arp_t->ar_hln));
	u_char * pro_addr = malloc(sizeof(arp_t->ar_pln));

	struct ether_addr mac,mac2;
	struct in_addr ip, ip2;

	memcpy(hwd_addr, arp_data, arp_t->ar_hln);
	memcpy(pro_addr, arp_data + arp_t->ar_hln, arp_t->ar_pln);
	VV(1, "From : ");
	if(htons(arp_t->ar_hrd) == 0x01 && arp_t->ar_hln == ETH_ALEN) {
		memcpy(&(mac.ether_addr_octet), hwd_addr, ETH_ALEN);
		VV(0, "%s (", ether_ntoa(&mac));
	}
	if(htons(arp_t->ar_pro) == 0x0800 && arp_t->ar_pln == 0x04) {
		memcpy(&(ip.s_addr), pro_addr, arp_t->ar_pln);
		VV(0, "%s)\n", inet_ntoa(ip));
	}

	memcpy(hwd_addr, arp_data + arp_t->ar_hln + arp_t->ar_pln, arp_t->ar_hln);
	memcpy(pro_addr, arp_data + 2*arp_t->ar_hln + arp_t->ar_pln, arp_t->ar_pln);
	VV(1, "To : ");
	if(htons(arp_t->ar_hrd) == 0x01 && arp_t->ar_hln == ETH_ALEN) {
		memcpy(&(mac2.ether_addr_octet), hwd_addr, ETH_ALEN);
		VV(0, "%s (", ether_ntoa(&mac2));
	}
	if(htons(arp_t->ar_pro) == 0x0800 && arp_t->ar_pln == 0x04) {
		memcpy(&(ip2.s_addr), pro_addr, arp_t->ar_pln);
		VV(0, "%s)\n", inet_ntoa(ip2));
	}

	char buffer[128];
	bzero(buffer, 128);
	char * yellow_str;
	if(htons(arp_t->ar_op) == ARPOP_REQUEST) {
		sprintf(buffer, "Who is %s ? (to %s [%s])\n", 
				inet_ntoa(ip2), inet_ntoa(ip), ether_ntoa(&mac));
	} else if(htons(arp_t->ar_op) == ARPOP_REPLY) {
		sprintf(buffer, "%s is %s\n", inet_ntoa(ip), ether_ntoa(&mac));
	}

	if(strcmp(buffer, "")) {
		yellow_str = yellow(buffer);
		V(1, yellow_str);
		free(yellow_str);
	}

	free(hwd_addr);
	free(pro_addr);
}

