/*
 * @File : dns.h
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
 *
 * @Summary : Decode DNS Packet
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

#ifndef _DNS_H
#define _DNS_H

// https://www.ietf.org/rfc/rfc1035.txt
#define DNS_A 0x1
#define DNS_NS 0x2
#define DNS_CNAME 0x5
#define DNS_SOA 0x6
#define DNS_MX 0xf 
#define DNS_AAAA 0x1c

#define DNS_IN 0x1 
#define DNS_ANY 0xff 

struct dns_hdr {
	u_int16_t id;
	u_int16_t flags;
	u_int16_t qdcount;
	u_int16_t ancount;
	u_int16_t nscount;
	u_int16_t arcount;
};

struct dns_ans {
	u_int16_t pointer;
	u_int16_t type;
	u_int16_t class;
	// We have to cut the ttl by 2, the compiler align 
	// the ttl and the structure doesn't fit the packet 
	// if we use a u_int32_t
	u_int16_t _ttl;
	u_int16_t ttl;
	u_int16_t length;
// Here start data;
};

void decode_dns(const u_char * packet);

#endif

