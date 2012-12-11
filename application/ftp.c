/*
 * @File : dns.c
 *
 * @Author : Leo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary : Decode FTP packet
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

#include <application/ftp.h>

#include <output.h>
#include <verbosity.h>

extern int verbosity_level;

void decode_ftp_data(const u_char * packet) {
	char buffer[1500];
	int i = 0;
	char * grey_str;
	while(packet[i] != '\0') {
		buffer[i] = packet[i];
		i++;
	}
	buffer[i] = '\0';
	grey_str = grey(buffer)
	VV(3, "FTP-DATA : \n");
	if(verbosity_level < 3)
		VV(3, "Verbosity level at 3 shows the content.\n");
	VVV(0, "%s\n", grey_str);
	free(grey_str);
}

void decode_ftp(const u_char * packet) {
	char buffer[1500];
	int i = 0;
	char * yellow_str;
	while(packet[i] != '\n' && packet[i] != '\0') {
		buffer[i] = packet[i];
		i++;
	}
	buffer[i] = '\0';
	yellow_str = yellow(buffer)
	V(3, "FTP : ");
	V(0, "%s\n", yellow_str);
	free(yellow_str);
}




