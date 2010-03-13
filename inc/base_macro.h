/******************************************************************************
 *
 * (C) Copyright 2007-2010
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA 02111-1307 USA
 *
 * FILE NAME:
 *   base_macro.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __BASE_MACRO_H
#define __BASE_MACRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#define CONST	    SEG_CODE

#ifndef __C51__

 #include <intrins.h>
 #include <absacc.h>

 #define CBYTE  ((UINT8  volatile SEG_CODE  *) 0)  /*  8-bit data in  code area */
 #define DBYTE  ((UINT8  volatile SEG_DATA  *) 0)  /*  8-bit data in  data area */
 #define PBYTE  ((UINT8  volatile SEG_PDATA *) 0)  /*  8-bit data in pdata area */
 #define XBYTE  ((UINT8  volatile SEG_XDATA *) 0)  /*  8-bit data in xdata area */

 #define CWORD  ((UINT16 volatile SEG_CODE  *) 0)  /* 16-bit data in  code area */
 #define DWORD  ((UINT16 volatile SEG_DATA  *) 0)  /* 16-bit data in  data area */
 #define PWORD  ((UINT16 volatile SEG_PDATA *) 0)  /* 16-bit data in pdata area */
 #define XWORD  ((UINT16 volatile SEG_XDATA *) 0)  /* 16-bit data in xdata area */

#endif

#define CDWORD ((UINT32 volatile SEG_CODE  *) 0)   /* 32-bit data in  code area */
#define DDWORD ((UINT32 volatile SEG_DATA  *) 0)   /* 32-bit data in  data area */
#define PDWORD ((UINT32 volatile SEG_PDATA *) 0)   /* 32-bit data in pdata area */
#define XDWORD ((UINT32 volatile SEG_XDATA *) 0)   /* 32-bit data in xdata area */


#define KB(x)               ((x)*1024)
#define MB(x)               ((x)*1024*1024)


/* Calculate the total element of an array.
 *
 * e.g:
 *   int  array[100];
 *  To get the total element of (array), just use COUNT_OF(array).
 *   acturally, the total element in this sample is 100.
 */
#define COUNT_OF(n)         (SINT32)(sizeof(n) / sizeof((n)[0]))

/* calculate the Byte Offset of member in struct.
 *
 * e.g:
 *  typedef struct
 *  {
 *      int  a;
 *      int  b;
 *      char c;
 *  } TYPE_S;
 *
 * To get the Byte Offset of (c) in TYPE_S, just use offsetof(TYPE_S, c).
 *  acturally, the offset in this sample is 8.
 */
#undef offsetof
#ifdef __compiler_offsetof
 #define offsetof(TYPE, MEMBER)  __compiler_offsetof(TYPE, MEMBER)
#else
 #define offsetof(TYPE, MEMBER)  ((size_t) &((TYPE *)0)->MEMBER)
#endif

/* remove warning */
#define NO_WARNING(x)       do { if (x) {} } while (0)

#ifndef MIN
 #define MIN(a, b)          (((a)<(b))?(a):(b))
#endif

#ifndef MAX
 #define MAX(a, b)          (((a)>(b))?(a):(b))
#endif

/* get the absolute value */
#define ABS(x)              (((x) >= 0) ? (x) : -(x))

/* bit operation */
#define SET_BIT(n, b)       do { (n) |= (1 << (b));  } while (0)
#define CLR_BIT(n, b)       do { (n) &= ~(1 << (b)); } while (0)
#define READ_BIT(n, b)      (BOOL)((n) >> (b))


/* operate memory as big-endian */
#define SET_BE_16(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT16)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT16)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_BE_16(buf)    (UINT16)(  ((UINT16)((const UINT8 *)(buf))[0] <<  8)  \
                                   | ((UINT16)((const UINT8 *)(buf))[1] <<  0))

#define SET_BE_32(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT32)(val) >> 24) & 0xFF);            \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT32)(val) >> 16) & 0xFF);            \
        ((UINT8 *)(buf))[2] = (UINT8)(((UINT32)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[3] = (UINT8)(((UINT32)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_BE_32(buf)    (  ((UINT32)((const UINT8 *)(buf))[0] << 24)          \
                           | ((UINT32)((const UINT8 *)(buf))[1] << 16)          \
                           | ((UINT32)((const UINT8 *)(buf))[2] <<  8)          \
                           | ((UINT32)((const UINT8 *)(buf))[3] <<  0))


/* operate memory as little-endian */
#define SET_LE_16(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT16)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT16)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_LE_16(buf)    (UINT16)(  ((UINT16)((const UINT8 *)(buf))[1] <<  8)  \
                                   | ((UINT16)((const UINT8 *)(buf))[0] <<  0))

#define SET_LE_32(buf, val)                                                     \
    do {                                                                        \
        ((UINT8 *)(buf))[3] = (UINT8)(((UINT32)(val) >> 24) & 0xFF);            \
        ((UINT8 *)(buf))[2] = (UINT8)(((UINT32)(val) >> 16) & 0xFF);            \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT32)(val) >>  8) & 0xFF);            \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT32)(val) >>  0) & 0xFF);            \
    } while (0)

#define GET_LE_32(buf)    (  ((UINT32)((const UINT8 *)(buf))[3] << 24)          \
                           | ((UINT32)((const UINT8 *)(buf))[2] << 16)          \
                           | ((UINT32)((const UINT8 *)(buf))[1] <<  8)          \
                           | ((UINT32)((const UINT8 *)(buf))[0] <<  0))


/* Swap data:  Big-Endian  <-->  Little-Endian */
#define SWAP_16(x)     (UINT16)(  (((UINT16)(x) >> 8) & 0x00FF)                 \
                                | (((UINT16)(x) << 8) & 0xFF00))

#define SWAP_32(x)     (  (((UINT32)(x) >> 24) & 0x000000FF)                    \
                        | (((UINT32)(x) >>  8) & 0x0000FF00)                    \
                        | (((UINT32)(x) <<  8) & 0x00FF0000)                    \
                        | (((UINT32)(x) << 24) & 0xFF000000))


#endif /* __BASE_MACRO_H */

