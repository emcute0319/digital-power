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
 *   drv_int.c
 * DESCRIPTION:
 *   Interrupt Service Routine.
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#include <drv.h>


#define DRV_ISR_START(_int_name)    /* do nothing */
#define DRV_ISR_END(_int_name)      /* do nothing */


/******************************************************************************
 * FUNCTION NAME:
 *      ISR_INT0
 * DESCRIPTION:
 *      External INT0 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void ISR_INT0(void) __interrupt(INT_ID_INT0, REG_GROUP_2)
{
    DRV_ISR_START(INT0);
    /* Add porting code here */
    DRV_ISR_END(INT0);
}


/* RTX-Tiny OS will use Timer 0 as OS tick-timer */
#if !OS_RtxTiny_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      ISR_Timer0
 * DESCRIPTION:
 *      Timer0 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void ISR_Timer0(void) __interrupt(INT_ID_TIMER0, REG_GROUP_2)
{
    DRV_ISR_START(TIMER0);
    /* Add porting code here */
    DRV_ISR_END(TIMER0);
}

#endif


/******************************************************************************
 * FUNCTION NAME:
 *      ISR_INT1
 * DESCRIPTION:
 *      External INT1 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void ISR_INT1(void) __interrupt(INT_ID_INT1, REG_GROUP_2)
{
    DRV_ISR_START(INT1);
    /* Add porting code here */
    DRV_ISR_END(INT1);
}


/* uart always use Timer 1 as baudrate generator */
#if !DRV_UART_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *      ISR_Timer1
 * DESCRIPTION:
 *      Timer1 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void ISR_Timer1(void) __interrupt(INT_ID_TIMER1, REG_GROUP_2)
{
    DRV_ISR_START(TIMER1);
    /* Add porting code here */
    DRV_ISR_END(TIMER1);
}

#else

#if 0
/******************************************************************************
 * FUNCTION NAME:
 *      ISR_UART
 * DESCRIPTION:
 *      UART ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void ISR_UART(void) __interrupt(INT_ID_UART0, REG_GROUP_1)
{
    DRV_ISR_START(UART0);
    DRV_UART_ISR();
    DRV_ISR_END(UART0);
}
#endif
#endif


#if ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) )

/******************************************************************************
 * FUNCTION NAME:
 *      ISR_Timer2
 * DESCRIPTION:
 *      Timer2 ISR.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void ISR_Timer2(void) __interrupt(INT_ID_TIMER2, REG_GROUP_2)
{
    DRV_ISR_START(TIMER2);
    /* Add porting code here */
    DRV_ISR_END(TIMER2);
}

#endif

