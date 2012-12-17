/*
 * @File : dns.c
 *
 * @Author : Leo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary : Decode POP packet
 *
 * @Version : 2012/12/17
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

#include <application/pop.h>

#include <output.h>
#include <verbosity.h>

extern int verbosity_level;

void decode_pop(const u_char * packet) {
	char buffer[1500];
	int i = 0;
	char * yellow_str;
	while(packet[i] != '\n' && packet[i] != '\0') {
		buffer[i] = packet[i];
		i++;
	}
	buffer[i] = '\0';
	if(strcmp(buffer, "")) {
		yellow_str = yellow(buffer)
		V(3, "POP : ");
		V(0, "%s\n", yellow_str);
		free(yellow_str);
	}
}




