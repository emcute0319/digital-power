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
 *   apl_readvoltage.c
 * DESCRIPTION:
 *   Read Voltage Application.
 * HISTORY:
 *   2010.2.1        panda.xiong         Create/Update
 *
*****************************************************************************/

#include <plf.h>
#include <apl_readvoltage.h>


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
SINT32 APL_ReadVoltage(void)
{
    static UINT8    vLoop;
    static UINT32   vVoltage;
    UINT8           aDataBuf[2];

    if (vLoop++ >= 75)
    {
        vLoop = 0;

        DRV_SPI_ReadBytes(sizeof(aDataBuf), aDataBuf);

        vVoltage = (  ((UINT16)(aDataBuf[0]) << (8-3))
                    | ((UINT16)aDataBuf[1] >> 3) );

        /* calculate the real voltage */
        vVoltage *= 152;
        vVoltage /= 10;
        vVoltage += 50;
        vVoltage /= 100;
        vVoltage /= 10;
        vVoltage &= 0x7FFF;     /* return voltage is always a positive value */
    }

    return vVoltage;
}

