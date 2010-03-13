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
 *   apl_display.c
 * DESCRIPTION:
 *   Display LED Application.
 * HISTORY:
 *   2010.2.1        panda.xiong         Create/Update
 *
*****************************************************************************/

#include <plf.h>
#include <apl_display.h>


static CONST UINT8  aLedTable[] =
{
    0x12,0xDE,0x83,0x86,0x4E,0x26,0x22,0x9E,
    0x02,0x06,0x0A,0x62,0x33,0xC2,0x23,0x2B
};


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
void APL_Display(SINT32 vVoltage)
{
    UINT8   vHighData, vLowData;
    BOOL    bDisplayP;

    if (vVoltage >= 100)
    {
        /*  display format: xx  */
        vHighData = vVoltage / 100;
        vLowData  = (vVoltage % 100) / 10;
        bDisplayP = FALSE;
    }
    else
    {
        /*  display format: x.x  */
        vHighData = vVoltage / 10;
        vLowData  = vVoltage % 10;
        bDisplayP = TRUE;
    }

    /* dynamic-display High Byte */
    DRV_IO_WritePinData(IO_PIN(LED_SEL_1), LOW);
    DRV_IO_WritePortData(IO_PORT_LED_DATA_OUT, aLedTable[vHighData]);
    if (bDisplayP)
    {
        /* display Point of High Byte */
        DRV_IO_WritePinData(IO_PIN(LED_DATA_p), 0);
    }
    DRV_IO_WritePinData(IO_PIN(LED_SEL_0), HIGH);
    DRV_CPU_DelayMs(5);

    /* dynamic-display Low Byte */
    DRV_IO_WritePinData(IO_PIN(LED_SEL_0), LOW);
    DRV_IO_WritePortData(IO_PORT_LED_DATA_OUT, aLedTable[vLowData]);
    DRV_IO_WritePinData(IO_PIN(LED_SEL_1), HIGH);
    DRV_CPU_DelayMs(5);
}


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
void APL_Display_Init(void)
{
    /* light all LED, to dianostic mode */
    DRV_IO_WritePortData(IO_PORT_LED_DATA_OUT, 0x00);
    DRV_IO_WritePinData(IO_PIN(LED_SEL_0), HIGH);
    DRV_IO_WritePinData(IO_PIN(LED_SEL_1), HIGH);
    DRV_CPU_DelayMs(500);   /* delay 0.5 second */

    /* dark all LED, to normal mode */
    DRV_IO_WritePinData(IO_PIN(LED_SEL_0), LOW);
    DRV_IO_WritePinData(IO_PIN(LED_SEL_1), LOW);
    DRV_CPU_DelayMs(500);   /* delay 0.5 second */
}

