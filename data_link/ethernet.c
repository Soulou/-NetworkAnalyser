/*
 * @File : ethernet.c
 *
 * @Author : Léo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary :  
 *
 * @Version : 2012/12/03
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Léo Unbekandt wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return 
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/ether.h>

#include <network/arp.h>
#include <network/ip.h>
#include <network/ip6.h>
#include <data_link/ethernet.h>

#include <verbosity.h>
#include <output.h>

extern int verbosity_level;

void decode_ethernet(const u_char * packet) {
  char * str_shost = NULL;
  char * str_dhost = NULL;
	char * b_str_shost = NULL;
	char * b_str_dhost = NULL;

  const struct ether_header *ethernet;
  ethernet = (struct ether_header*)(packet);
  
	const struct ether_addr mac;
	memcpy(&(mac.ether_addr_octet), ethernet->ether_shost, ETH_ALEN);
	str_shost = ether_ntoa(&mac);
	b_str_shost = bold(str_shost);
	memcpy(&(mac.ether_addr_octet), ethernet->ether_dhost, ETH_ALEN);
	str_dhost = ether_ntoa(&mac);
	b_str_dhost = bold(str_dhost);

  V(0, "Ethernet - %s --> %s - Type : ", b_str_shost, b_str_dhost);

	u_int16_t etype = htons(ethernet->ether_type);
	if(etype < 0x05dc) {
		V(0, "IEEE802.3\n");
	}	else {
		switch(etype) {
			case 0x0800 :
				V(0, "IPv4\n");
				decode_ip(packet + sizeof(struct ether_header));
				break;
			case 0x86dd :
				V(0, "IPv6\n");
				decode_ip6(packet + sizeof(struct ether_header));
				break;
			case 0x0806 :
				V(0, "ARP\n");
				decode_arp(packet + sizeof(struct ether_header));
				break;
			case 0x0835 :
				V(0, "RARP\n");
				decode_arp(packet + sizeof(struct ether_header));
				break;
			default :
				V(0, "Unknown (%x)\n", etype);
				break;
		}
	}

  free(b_str_shost);
  free(b_str_dhost);
}

