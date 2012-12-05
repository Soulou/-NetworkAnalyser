/*
 * @File : debug.h
 *
 * @Author : Unbekandt Leo <leo@unbekandt.eu>
 *
 * @Summary :  
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

#ifndef _DEBUG_H
#define _DEBUG_H

void _V(int _tabs, ...);

// http://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
// ##__VA_ARGS__ removes the coma if there is no argument

#define V(indent, format, ...); \
  if(verbosity_level >= 1) { \
    _V(indent, format, ##__VA_ARGS__); \
  } 

#define VV(indent, format, ...); \
  if(verbosity_level >= 2) { \
    _V(indent ,format, ##__VA_ARGS__); \
  } 


#define VVV(indent, format, ...); \
  if(verbosity_level == 3) { \
    _V(indent ,format, ##__VA_ARGS__); \
  } 

#endif

