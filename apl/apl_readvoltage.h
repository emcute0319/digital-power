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
 *   apl_readvoltage.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.2.1        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __APL_READVOLTAGE_H
#define __APL_READVOLTAGE_H


/******************************************************************************
 * FUNCTION NAME:
 *      APL_ReadVoltage
 * DESCRIPTION:
 *      Read Output Voltage.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      The read output voltage, multiplied by 10.
 *      If return -1, means there is an error occur.
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.4        PANDA         Create/Update
 *****************************************************************************/
SINT32 APL_ReadVoltage(void);

/******************************************************************************
 * FUNCTION NAME:
 *      APL_ReadVoltage_Init
 * DESCRIPTION:
 *      Read Voltage Application Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.4        PANDA         Create/Update
 *****************************************************************************/
#define APL_ReadVoltage_Init()      /* do nothing */


#endif /* __APL_READVOLTAGE_H */

