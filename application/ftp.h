/*
 * @File : dns.h
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
 *
 * @Summary : Decode FTP Packet
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

#ifndef _FTP_H
#define _FTP_H

void decode_ftp(const u_char * packet);
void decode_ftp_data(const u_char * packet);

#endif

