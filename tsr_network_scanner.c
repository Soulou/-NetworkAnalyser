/*
 * @File : tsr_network_scanner.c
 *
 * @Author : Unbekandt Léo
 *
 * @Summary : Main file for TSR Network Scanner
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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "verbosity.h"
#include "scanner.h"

int verbosity_level = 0;

void usage(char * cli) {
  printf("Usage : %s (-i <interface> | -o <file>) [-f <BPF filter>] [-v <1..3 - verbosity>]\n", cli);
  exit(2);
}

int main(int argc, char * argv[])
{
  // Get flags from command line with getopt
  char * ovalue = NULL;
  char * ivalue = NULL;
  char * fvalue = NULL;
  char * vvalue = NULL;
  char c;

  while((c = getopt(argc, argv, "i:o:f:v:")) != -1) {
    switch(c) {
      case 'i':
        ivalue = optarg;
        break;
      case 'o':
        ovalue = optarg;
        break;
      case 'f':
        fvalue = optarg;
        break;
      case 'v':
        vvalue = optarg;
        verbosity_level = atoi(vvalue);
        if(verbosity_level < 1 || verbosity_level > 3) {
          fprintf(stderr, "Verbosity level must be between 1 and 3\n");
          usage(argv[0]);
        }
    }
  }
  if(!vvalue) {
    printf("No verbosity level asked, using 1 by default\n");
    verbosity_level = 1;
  }

  if(!ivalue && !ovalue) {
    fprintf(stderr, "An interface for live capturing or a file for offline analysis must be provided.\n");
    usage(argv[0]);
  }

  VV("Network interface chosen : %s\n", ivalue);

  start_scanner(ivalue);

	return 0;
}

