/*
 * @File : verbosity.c
 *
 * @Author : Léo Unbekandt
 *
 * @Summary : Indentation and verbosity
 *
 * @Version : 2012/12/03
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Léo Unbekandt wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return 
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

extern int verbosity_level;

void _V(int _tabs, char * format, ...) {
  va_list argp;
	va_start(argp, 0);
  int __i;
  for(__i = 0; __i < _tabs; __i++) 
    printf("  "); 
  vprintf(format, argp); 
	va_end(argp);
}

