/*
 * @File : ip.c
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
 *
 * @Summary : Decoding IP header
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

#include <netinet/ip.h>

#include "ip.h"
#include "verbosity.h"

extern int verbosity_level;

void decode_ip(const u_char * packet) {
  char * str_sip;
  char * str_dip;

  const struct ip *ip_header;
  ip_header = (struct ip *)(packet);

  str_sip = inet_ntoa(ip_header);
  str_sip = strndup(str_sip, strlen(str_sip));

  str_dip = inet_ntoa(ip_header);
  str_dip = strndup(str_dip, strlen(str_dip));
}

