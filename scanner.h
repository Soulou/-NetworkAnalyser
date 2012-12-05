/*
 * @File : scanner.h
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
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

#ifndef _SCANNER_H
#define _SCANNER_H

#include <pcap.h>

void start_scanner(char * interface);
void start_file_scanner(char * file);
void scan_packet(
    u_char * args, 
    const struct pcap_pkthdr * header, 
    const u_char * packet);

#endif

