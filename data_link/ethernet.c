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

#include <network/ip.h>
#include <network/ip6.h>
#include <data_link/ethernet.h>

#include <verbosity.h>
#include <output.h>

extern int verbosity_level;

char * str_ethernet_addr(const u_int8_t * addr) {
  int i = 0;
  char * saddr = (char*)malloc(30);
  char hexbuffer[3]; 

  for(i = 0; i < 32; i++) {
    saddr[i] = '\0';
  }
  for(i = 0 ; i < ETH_ALEN; i++) {
    sprintf(hexbuffer, "%02X", addr[i]);
    strncat(saddr, hexbuffer, 2);
    if(i != ETH_ALEN-1)
      strncat(saddr, ":", 1);
  }
  return saddr;
}

void decode_ethernet(const u_char * packet) {
  char * str_shost = NULL;
  char * str_dhost = NULL;
	char * b_str_shost = NULL;
	char * b_str_dhost = NULL;

  const struct ether_header *ethernet;
  ethernet = (struct ether_header*)(packet);
  
  str_shost = str_ethernet_addr(ethernet->ether_shost);
  str_dhost = str_ethernet_addr(ethernet->ether_dhost);
	b_str_shost = bold(str_shost);
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
				break;
			case 0x0835 :
				V(0, "RARP\n");
				break;
			default :
				V(0, "Unknown (%x)\n", etype);
				break;
		}
	}

  free(str_shost);
  free(str_dhost);
}

