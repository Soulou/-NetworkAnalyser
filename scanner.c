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

#include <verbosity.h>
#include <scanner.h>
#include <data_link/ethernet.h>

#define PROMISC_MODE 0
#define TIMEOUT_MS 500
#define SNAPLEN 1500
#define NB_PACKETS_TO_CAPTURE -1

extern int verbosity_level;

/**
 * @param file pcap file containg packets to analyse
 * @param filter BPF filter to apply
 */
void start_file_scanner(char * file, char * filter) {
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t * pcap_inst;
  
  if((pcap_inst = pcap_open_offline(file, errbuf)) == NULL) {
    fprintf(stderr, "Failed to open file %s : %s\n", file, errbuf);
    exit(-1);
  }

  start_scanner(pcap_inst, filter);
}

/**
 * @param file Interface to open
 * @param filter BPF filter to apply 
 */
void start_live_scanner(char * interface, char * filter) {
  unsigned int net_ip, netmask;
  char * str_net_ip;
  char * str_netmask;
  struct in_addr addr;
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t * pcap_inst;

  if((pcap_lookupnet (interface, &net_ip, &netmask, errbuf)) == -1) {
    fprintf(stderr, "Failed to get information about %s : %s\n", interface, errbuf);
    exit(-1);
  }

  addr.s_addr = net_ip;
  str_net_ip = inet_ntoa(addr);
  str_net_ip = strndup(str_net_ip, strlen(str_net_ip));

  addr.s_addr = netmask;
  str_netmask = inet_ntoa(addr);
  str_netmask = strndup(str_netmask, strlen(str_netmask));

  VVV(0, "%s - %s (%s)\n", interface, str_net_ip , str_netmask);

  if((pcap_inst = pcap_open_live(interface, SNAPLEN, PROMISC_MODE, TIMEOUT_MS, errbuf)) == NULL) {
    fprintf(stderr, "Failed to open %s\n", interface);
    exit(-1);
  }

  free(str_net_ip);
  free(str_netmask);
  start_scanner(pcap_inst, filter);
}

void start_scanner(pcap_t * pcap_inst, char * filter) {
	if(filter) {
		struct bpf_program fp;
		if(pcap_compile(pcap_inst, &fp, filter, 0, 0) == -1) {
			fprintf(stderr, "Failed to compile filter : %s\n", filter);
			exit(-1);
		}
		if(pcap_setfilter(pcap_inst, &fp) == -1) {
			fprintf(stderr, "Failed to set filter : %s\n", filter);
			exit(-1);
		}
	}
  pcap_loop(pcap_inst, NB_PACKETS_TO_CAPTURE, scan_packet, NULL);
  pcap_close(pcap_inst);
}

void scan_packet(
    u_char * args, 
    const struct pcap_pkthdr * header, 
    const u_char * packet) {

  decode_ethernet(packet);
  printf("\n");
}




