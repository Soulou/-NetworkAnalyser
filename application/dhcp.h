/*
 * @File : dhcp.h
 *
 * @Author : Unbekandt Leo <leo@soulou.fr>
 *
 * @Summary : Decode DHCP packet
 *
 * @Version : 2012/12/09
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <leo@soulou.fr> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return 
 * ----------------------------------------------------------------------------
 */

#ifndef _DHCP_H
#define _DHCP_H


struct bootp_data {
	u_int8_t op;
#define BOOTP_REQUEST 0x01
#define BOOTP_RESPONSE 0x02
	u_int8_t htype;
	u_int8_t hlen;
	u_int8_t hops;
	u_int32_t xid;
	u_int16_t secs;
	u_int16_t flags;
	u_int32_t ciaddr;
	u_int32_t yiaddr;
	u_int32_t siaddr;
	u_int32_t giaddr;
	u_char chaddr[16];
	u_char sname[64];
	u_char file[128];
	u_char vend[64];
};

#define DHCP_MAGIC_COOKIE 0x63825363
#define DHCP_END_OPT 0xff

enum { 
	DHCP_DISCOVER = 1,
	DHCP_OFFER,
	DHCP_REQUEST,
	DHCP_DECLINE,
	DHCP_ACK,
	DHCP_NACK,
	DHCP_RELEASE,
	DHCP_INFORM
};

// https://tools.ietf.org/html/rfc2132
enum {
	DHCP_SUBNET_MASK = 1,	DHCP_TIME_OFFSET,	DHCP_ROUTER_OPT,
	DHCP_TIMESERVER,	DHCP_NS,	DHCP_DNS,
	DHCP_LOGSERVER,	DHCP_COOKIESERVER, DHCP_LPRSERVER,
	DHCP_IMPRESSERVER,	DHCP_RESLOCSERVER,	DHCP_HOSTNAME,
	DHCP_BOOTFILESIZE,	DHCP_MERITDUMP,	DHCP_DOMAINNAME,
	DHCP_SWAPSERVER,	DHCP_ROOTPATH,	DHCP_EXTPATH,
	DHCP_IPFORW,	DHCP_NONLOCALROUTING,	DHCP_POLICYFILTER,
	DHCP_MAXDATAGRAMREASSIZE,	DHCP_DEFAULTTTL,	DHCP_PATHMTUTIMEOUT,
	DHCP_PATHMTUPLATEAU, DHCP_INTERFACEMTU, DHCP_ALLSUBNLOCAL,
	DHCP_BROADCAST, DHCP_MASKDISCOVERY, DHCP_MASKSUPPL,
	DHCP_ROUTERDISC, DHCP_ROUTERSOLADDR, DHCP_STATICROUTE,
	DHCP_TRAILERENC, DHCP_ARPCACHETIMEOUT, DHCP_ETHENC, 
	DHCP_TCPDEFAULTTTL, DHCP_TCPKATTL, DHCP_TCPKAGARBAGE,
	DHCP_NISDOMAIN, DHCP_NISERVERS, DHCP_NTPSERVERS,
	DHCP_VENDOR, DHCP_NETBIOSTCPNS, DHCP_NETBIOSTCPDISTS,
	DHCP_NETBIOSTCPNODETYPE, DHCP_NETBIOSTCPSCOPE, DHCP_XFONT,
	DHCP_XDISPMAN, DHCP_IP, DHCP_LEASE,
	DHCP_OVERLOAD, DHCP_MSGTYPE, DHCP_SERVID,
	DHCP_PARAMREQ, DHCP_MSG, DHCP_MAXMSGSIZE,
	DHCP_RENEWTIME, DHCP_REBINDTIME, DHCP_VENDORID,
	DHCP_CLIENTID
};
// Some are missing, but in the case of this project, we won't use them
// (actually, I'll only use the mose used)



void decode_dhcp(const u_char * packet);

#endif

