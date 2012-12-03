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

#include <net/ethernet.h>

#include "ip.h"
#include "ethernet.h"
#include "verbosity.h"

extern int verbosity_level;

char * str_ethernet_addr(const u_int8_t * addr) {
  int i = 0;
  char * saddr = (char*)malloc(30);
  char hexbuffer[3]; 

  for(i = 0; i < 32; i++) {
    saddr[i] = '\0';
  }
  for(i = ETH_ALEN -1 ; i >= 0; i--) {
    sprintf(hexbuffer, "%02X", addr[i]);
    strncat(saddr, hexbuffer, 2);
    if(i != 0)
      strncat(saddr, ":", 1);
  }
  return saddr;
}

void decode_ethernet(const u_char * packet) {
  char * str_shost = NULL;
  char * str_dhost = NULL;

  const struct ether_header *ethernet;
  ethernet = (struct ether_header*)(packet);
  
  str_shost = str_ethernet_addr(ethernet->ether_shost);
  str_dhost = str_ethernet_addr(ethernet->ether_dhost);

  V("Ethernet - %s --> %s - Type : ", str_shost, str_dhost);

  switch(ethernet->ether_type) {
    case 0x0008 :
      V("IP\n");
      decode_ip(packet + sizeof(struct ether_header));
      break;
    case 0x0608 :
      V("ARP\n");
      break;
    case 0x3508 :
      V("RARP\n");
      break;
    default :
      V("Unknown\n");
      break;
  }

  free(str_shost);
  free(str_dhost);
}

