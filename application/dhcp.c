/*
 * @File : dhcp.c
 *
 * @Author : Unbekandt Leo
 *
 * @Summary : Decode DHCP packet
 *
 * @Version : 2012/12/09
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Unbekandt Leo wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return 
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <application/dhcp.h>

#include <verbosity.h>

extern int verbosity_level;

char * dhcp_str_types[] = {
	"DISCOVER",
	"OFFER",
	"REQUEST",
	"DECLINE",
	"ACK",
	"NACK",
	"RELEASE",
	"INFORM"
};

char * str_ip(const u_char * ptr) {
		struct in_addr ip_t;
		memcpy(&(ip_t.s_addr), ptr, 4);
		char * ret = inet_ntoa(ip_t);
		return strndup(ret, strlen(ret)+1);
}

char * str_ips(const u_char * ptr, int n) {
	int i;
	// 16 : ip length, n*2 -> ", ", 3 -> [ ] \0
	char * ret = malloc(n*16+n*2+3);
	char * ip;
	bzero(ret, n*16+n*2+3);
	strcat(ret, "[");
	for(i = 0; i < n; i++) {
		ip = str_ip(ptr+i*4);
		strcat(ret, ip);
		if(i != n-1) {
			strcat(ret, ", ");
		}
		free(ip);
	}
	strcat(ret, "]");
	return ret;
}	

char * get_dhcp_method(u_char c) {
	return dhcp_str_types[c-1];
}

void decode_dhcp(const u_char * packet) {
	
	const struct bootp_data * bootp_t;
	bootp_t = (struct bootp_data *)(packet);

	if (bootp_t->op == BOOTP_REQUEST) {
		VVV(3, "BOOTP Request\n");
	} else if (bootp_t->op == BOOTP_RESPONSE) {
		VVV(3, "BOOTP Response\n");
	}
	
	const u_char * dhcp_data = (u_char *)bootp_t->vend;
	const u_int32_t * magic_cookie = (u_int32_t *)bootp_t->vend;

	if(htonl(*magic_cookie) == DHCP_MAGIC_COOKIE) {
		VVV(3, "DHCP Magic cookie : %d\n", DHCP_MAGIC_COOKIE)
		
		int n = 4, nb_ip, i;
		char * tmp_str;
		u_int16_t size;
		u_int32_t time;

		while(dhcp_data[n] != DHCP_END_OPT) {
			switch(dhcp_data[n]) {
				case DHCP_MSGTYPE:
					V(3, "DHCP %s\n", get_dhcp_method(dhcp_data[n+2]));
					break;
				case DHCP_LEASE:
					VVV(3, "Lease time : %d\n", (u_int32_t)dhcp_data[n+2]);
					break;
				case DHCP_SERVID:
					tmp_str = str_ip(dhcp_data+n+2);
					VV(3, "Server ID : %s\n", tmp_str);
					free(tmp_str);
					break;
				case DHCP_SUBNET_MASK:
					tmp_str = str_ip(dhcp_data+n+2);
					VV(3, "Subnet Mask : %s\n",	tmp_str);
					free(tmp_str);
					break;
				case DHCP_ROUTER_OPT:
					nb_ip = dhcp_data[n+1]/4;
					tmp_str = str_ips(dhcp_data+n+2, nb_ip);
					VVV(3, "Router Option : %s\n", tmp_str);
					free(tmp_str);
					break;
				case DHCP_DNS:
					nb_ip = dhcp_data[n+1]/4;
					tmp_str = str_ips(dhcp_data+n+2, nb_ip);
					VV(3, "DNS : %s\n", tmp_str);
					free(tmp_str);
					break;
        case DHCP_IP:
          tmp_str = str_ip(dhcp_data+n+2);
          VV(3, "Requested IP : %s\n", tmp_str);
          free(tmp_str);
          break;
				case DHCP_BROADCAST:
					tmp_str = str_ip(dhcp_data+n+2);
					VV(3, "Broadcast : %s\n",	tmp_str);
					free(tmp_str);
					break;
				case DHCP_DOMAINNAME:
					tmp_str = malloc(dhcp_data[n+1]);
					memcpy(tmp_str, dhcp_data +n+2, dhcp_data[n+1]);
					VV(3, "Domain name : %s\n", tmp_str);
					free(tmp_str);
					break;
				case DHCP_MAXMSGSIZE:
					memcpy(&size, dhcp_data+n+2, 2);
					VVV(3, "Max message size : %d\n", htons(size)); 
					break;
				case DHCP_VENDORID:
					tmp_str = malloc(dhcp_data[n+1]+1);
					memcpy(tmp_str, dhcp_data +n+2, dhcp_data[n+1]);
					tmp_str[dhcp_data[n+1]] = '\0';
					VVV(3, "Vendor ID : %s\n", tmp_str);
					free(tmp_str);
					break;
				case DHCP_RENEWTIME:
					memcpy(&time, dhcp_data+n+2, 2);
					VVV(3, "Bind renew time : %d\n", htons(time)); 
					break;
				case DHCP_REBINDTIME:
					memcpy(&time, dhcp_data+n+2, 2);
					VVV(3, "Bind rebind time : %d\n", htons(time)); 
					break;
				case DHCP_HOSTNAME:
					tmp_str = malloc(dhcp_data[n+1]+1);
					tmp_str[dhcp_data[n+1]] = '\0';
					memcpy(tmp_str, dhcp_data +n+2, dhcp_data[n+1]);
					VV(3, "Hostname : %s\n", tmp_str);
					free(tmp_str);
					break;
				case DHCP_PARAMREQ:
					tmp_str = malloc(dhcp_data[n+1]);
					memcpy(tmp_str, dhcp_data +n+2, dhcp_data[n+1]);
					VVV(3,"Parameter Request : [");
					for(i = 0; i < dhcp_data[n+1]; i++) {
						VVV(0, "%d", dhcp_data[n+2+i]);
						if(i != dhcp_data[n+1] -1) {
							VVV(0, ", ");
						}
					}
					VVV(0, "]\n");
					free(tmp_str);
					break;
				default:
					VVV(3, "Option %d, size : %d\n", dhcp_data[n], dhcp_data[n+1])
			}
			n += (dhcp_data[n+1] + 2);
		}
	}
}
