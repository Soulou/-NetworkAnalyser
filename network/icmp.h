/*
 * @File : icmp.h
 *
 * @Author : Unbekandt Leo <leo@soulou.fr>
 *
 * @Summary : Decode ICMP packet
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

#ifndef _ICMP_H
#define _ICMP_H

void decode_icmp(const u_char * packet);

#endif

