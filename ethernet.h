/*
 * @File : ethernet.h
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
 *
 * @Summary : Decoding ethernet header
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

#ifndef _ETHERNET_H
#define _ETHERNET_H

void decode_ethernet(const u_char * packet);

#endif

