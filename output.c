/*
 * @File : output.c
 *
 * @Author : Unbekandt Leo
 *
 * @Summary : Manage color/bold in output
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

#include "output.h"

char * bold(char * s) {
	char * ret = malloc(strlen(s) + 10);
	sprintf(ret, "\e[1m%s\e[0m", s);
	return ret;
}
char * white_on_red(char * s) {
	char * ret = malloc(strlen(s) + 10);
	sprintf(ret, "\e[1;41m%s\e[0m", s);
	return ret;
}
