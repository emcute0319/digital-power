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
 *   typedef.h
 * DESCRIPTION:
 *   Base type definition.
 * HISTORY:
 *   2010.1.26        PANDA         Create/Update
 *
*****************************************************************************/

#ifndef __TYPEDEF_H
#define __TYPEDEF_H


#include <compiler_defs.h>


/* these parameters are defined only for easy code reading */
#define IN                      /* nothing */
#define OUT                     /* nothing */

typedef bit                     BOOL;       /* Boolean: TRUE/FALSE */
typedef unsigned char           BYTE;
typedef unsigned char           UINT8;      /* 8-bit */
typedef signed   char           SINT8;
typedef unsigned short          UINT16;     /* 16-bit */
typedef signed   short          SINT16;
typedef unsigned long           UINT32;     /* 32-bit */
typedef signed   long           SINT32;

#define TRUE                    1
#define FALSE                   0

#define HIGH                    1
#define LOW                     0

/* NULL pointer */
#define NULL                    ((void *)0)


#include <base_macro.h>


#endif /* __TYPEDEF_H */

