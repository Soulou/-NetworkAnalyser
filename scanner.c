/*
 * @File : scanner.c
 *
 * @Author : Léo Unbekandt <leo@unbekandt.eu>
 * 
 * @Summary : Main loop of the scan
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
#include <pcap.h>

#include "verbosity.h"
#include "scanner.h"
#include "ethernet.h"

#define PROMISC_MODE 0
#define TIMEOUT_MS 500
#define SNAPLEN 1500
#define NB_PACKETS_TO_CAPTURE -1

extern int verbosity_level;

void start_file_scanner(char * file) {
	
}

void start_scanner(char * interface) {
  unsigned int net_ip, netmask;
  char * str_net_ip;
  char * str_netmask;
  struct in_addr addr;
  pcap_t * pcap_inst;
  char errbuf[PCAP_ERRBUF_SIZE];

  /* pcap_t * */ 

  if((pcap_lookupnet (interface, &net_ip, &netmask, errbuf)) == -1) {
    fprintf(stderr, "Failed to get information about %s : %s\n", interface, errbuf);
    exit(-1);
  }

  addr.s_addr = net_ip;
  str_net_ip = inet_ntoa(addr);
  // As inet_ntoa will erase the pointer when recalled
  str_net_ip = strndup(str_net_ip, strlen(str_net_ip));

  addr.s_addr = netmask;
  str_netmask = inet_ntoa(addr);
  str_netmask = strndup(str_netmask, strlen(str_netmask));

  VVV(0, "%s - %s (%s)\n", interface, str_net_ip , str_netmask);

  if((pcap_inst = pcap_open_live(interface, SNAPLEN, PROMISC_MODE, TIMEOUT_MS, errbuf)) == NULL) {
    fprintf(stderr, "Failed to open %s in promiscuous mode\n", interface);
    exit(-1);
  }

  pcap_loop(pcap_inst, NB_PACKETS_TO_CAPTURE, scan_packet, NULL);

  pcap_close(pcap_inst);
  free(str_net_ip);
  free(str_netmask);
}

void scan_packet(
    u_char * args, 
    const struct pcap_pkthdr * header, 
    const u_char * packet) {

  VVV(0, "%d/%d bytes captured\n", header->caplen, header->len);
  
  decode_ethernet(packet);
}




