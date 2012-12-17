/*
 * @File : dns.c
 *
 * @Author : Leo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary : Decode IMAP packet
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

#include <application/imap.h>

#include <output.h>
#include <verbosity.h>

extern int verbosity_level;

void decode_imap(const u_char * packet) {
	char buffer[1500];
	int i = 0, j = 0;
	char * yellow_str, * grey_str;
	while(packet[j] != '\0') {
    while(packet[j] != '\n' && packet[j] != '\0') {
		  buffer[i] = packet[i];
  		i++;
      j++;
    }
    buffer[i] = '\0';
    if(!strcspn(buffer, "*")) {
      yellow_str = yellow(buffer)
      V(3, "IMAP : ");
      V(0, "%s\n", yellow_str);
      free(yellow_str);
	  }
    else if(!strcmp(buffer, "")) {
      V(3, "IMAP - NO DATA\n");
    }
    else {
      grey_str = grey(buffer)
      V(3, "IMAP - DATA : ");
      V(0, "%s\n", grey_str);
      free(grey_str);
    }
    i = 0;
    j++;
	}
}




