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
 *   apl_display.h
 * DESCRIPTION:
 *   N/A
 * HISTORY:
 *   2010.2.1        panda.xiong         Create/Update
 *
*****************************************************************************/

#ifndef __APL_DISPLAY_H
#define __APL_DISPLAY_H


/******************************************************************************
 * FUNCTION NAME:
 *      APL_Display
 * DESCRIPTION:
 *      Display Voltage.
 * PARAMETERS:
 *      vVoltage  : Voltage to be displayed.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.4        PANDA         Create/Update
 *****************************************************************************/
void APL_Display(SINT32 vVoltage);

/******************************************************************************
 * FUNCTION NAME:
 *      APL_Display_Init
 * DESCRIPTION:
 *      Display Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.2.4        PANDA         Create/Update
 *****************************************************************************/
void APL_Display_Init(void);


#endif /* __APL_DISPLAY_H */

