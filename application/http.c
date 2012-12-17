/*
 * @File : dns.c
 *
 * @Author : Leo Unbekandt <leo@unbekandt.eu>
 *
 * @Summary : Decode HTTP packet
 *
 * @Version : 2012/12/16
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
#include <ctype.h> 

#include <arpa/inet.h>
#include <netinet/in.h>

#include <application/http.h>

#include <output.h>
#include <verbosity.h>

extern int verbosity_level;

void decode_http(const u_char * packet) {
	char buffer[1500];
	int i = 0;
	char * yellow_str;
	while(packet[i] != '\n' && packet[i] != '\0') {
		buffer[i] = packet[i];
		i++;
	}
  buffer[i] = '\0';

  V(3, "HTTP - ");
  if(!strlen(buffer)) {
    V(0, "No DATA\n");
  }
  else if(!strcspn(buffer, "PUT") || !strcspn(buffer, "POST") || !strcspn(buffer, "GET") ||
        !strcspn(buffer, "PATCH") || !strcspn(buffer, "DELETE")) {
    yellow_str = yellow(buffer)
    V(0, "%s\n", yellow_str);
    free(yellow_str);
  }
  else {
    V(0, "DATA\n")
    VVV(4, "\e[37m");
    for(i = 0; i < strlen(buffer); i++) {
      if(!isprint(buffer[i])) {
        VVV(0, "%x", buffer[i]);
      } else {
        VVV(0, "%c", buffer[i]);
      }
    }
    VVV(0, "\e[0m\n");
  }
}




