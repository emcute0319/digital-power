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
 *   drv_uart.c
 * DESCRIPTION:
 *   UART Driver.
 * HISTORY:
 *   2010.1.27        panda.xiong         Create/Update
 *
*****************************************************************************/

#include <drv.h>

#if DRV_UART_SUPPORT

/* Global variable define */
static BOOL     bTxReady;
static BOOL     bRxReady;
static UINT8    aRxBuf[4];
static UINT8    vRxBufPtr;  /* always point to the empty buffer */


#if 0 /* ( defined(_CPU_AT89C52_) || defined(_CPU_AT89S52_) ) */
 #define UART_Baudrate_Generated_By_T2  /* UART baudrate is generated by T2 */
#else
 #define UART_Baudrate_Generated_By_T1  /* UART baudrate is generated by T1 */
#endif


#include <stdarg.h>
#include <drv_uart.h>


typedef void (*PUT_CHAR_FUNC)(UINT8 ch);

static void drv_uart_vsprintf
(
    PUT_CHAR_FUNC   put_func,
    const char     *format,
    va_list         arg_prt
)
{
    char          fch;       /* get format value       */
//    char         *p_str;
    unsigned char num, div;
    unsigned char odd;
    unsigned char len_count;

    while (1)
    {
        while ((fch = *format++) != '%')
        {
            if (fch == '\0')
            {
                /* to the end of string */
                return;
            }

            put_func(fch);
        }

		/* skip '%' character */
		fch = *format++;

        switch (fch)
        {
#if 0
            case 'd':
            case 'i':
            case 'u':
                num = (unsigned char)va_arg(arg_prt, char);

                div = 1;
                len_count = 1;
                do
                {
                    div *= 10;
                    len_count++;

					if (div > num)
					{
						div /= 10;
                        len_count--;
						break;
					}
					else if (div >= (unsigned char)(~0) / 10)
					{
						break;
					}
                } while (1);

                do
                {
                    odd  = num / div;
                    num  = num % div;
                    div /= 10;
                    put_func(odd - 0x0 + '0');
                } while (--len_count != 0);
                break;
#endif

            case 'x':
            case 'X':
                num = (unsigned char)va_arg(arg_prt, char);

                div = 1;
                len_count = 1;
                do
                {
                    div *= 16;
                    len_count++;

					if (div > num)
					{
						div /= 16;
                        len_count--;
						break;
					}
					else if (div >= (unsigned char)(~0) / 16)
					{
						break;
					}
                } while (1);

                do
                {
                    odd  = num / div;
                    num  = num % div;
                    div /= 16;

                    if (odd >= 0xA)
                    {
                        put_func(odd - 0xA + 'A');
                    }
                    else
                    {
                        put_func(odd - 0x0 + '0');
                    }
                } while (--len_count != 0);
                break;

#if 0
            case 'c':
                put_func((unsigned char)va_arg(arg_prt, char));
                break;

            case 's':
                p_str = va_arg(arg_prt, char *);
				while (*p_str != '\0')
				{
                    put_func(*p_str++);
				}
                break;
#endif

            default:
                put_func(fch);
                break;
        }
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *      drv_uart_WriteByte
 * DESCRIPTION:
 *      Write byte data to UART.
 * PARAMETERS:
 *      vByte : Byte data to be written.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void drv_uart_WriteByte(IN UINT8 vByte)
{
	SBUF = vByte;

    /* wait for uart sent out data */
	while (TI == 0)
	{}

    TI = 0;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_Printf
 * DESCRIPTION:
 *      Print string to UART.
 * PARAMETERS:
 *      fmt : String to be written.
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_UART_Printf(const char *fmt, ...)
{
    va_list   ptr;

    va_start(ptr, fmt);
    drv_uart_vsprintf(drv_uart_WriteByte, fmt, ptr);
    va_end(ptr);
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_UART_Init
 * DESCRIPTION:
 *      Uart Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2010.1.27        panda.xiong         Create/Update
 *****************************************************************************/
void DRV_UART_Init(void)
{
    /* init internal variable */
	bTxReady  = TRUE;
	bRxReady  = TRUE;
	vRxBufPtr = 0;
    memset(aRxBuf, 0x00, sizeof(aRxBuf));


	/*
	    The baudrate function using timer0 & timer1 is:

     *  In mode 1:
        baudrate  =  f(osc) / 12

     *  In mode 2:
                       2^(SMOD)
        baudrate  =  ------------  -  f(osc)
                         64

     *  In mode 1 & 3: (usually use)
                       2^(SMOD)      f(osc)          1
        baudrate  =  ------------ * -------- * ( -------------------- )
                         32            12         2^(K) - (TH1, TL1)

    	In this formula:
          If T1 is in mode 0,     K = 13;
          If T1 is in mode 1 & 3, K = 16;
          If T1 is in mode 2,     K =  8(usually use).

        So:
                                 2^(SMOD) * f(osc)
        init_value  =  256  -  --------------------  (timer1 is in mode 2)
                                  384 * baudrate
    */


	/*
	    The baudrate function using timer2 is:

		                            f(osc)
		baudrate  =  -----------------------------------
	                   32 * (65536 - (RCAP2H, RCAP2L))

		So:
		                                     f(osc)
		(RCAP2H, RCAP2L)  =  65536  -  -----------------
		                                 32 * baudrate
	*/


	/*
	    Below are some usually used baudrate & initial values: (SCON = 0x50)

	 *  Timer1: (mode 1 & 3)
	        f(osc) = 12MHz
		        Baudrate    SMOD    TMOD    TH1(TL1)
		          4800        1     0x20      0XF3
		          2400        0     0x20      0xF3
		    f(osc) = 11.0592MHz
		        Baudrate    SMOD    TMOD    TH1(TL1)
		         19200        1     0x20      0XFD
		          9600        0     0x20      0xFD
				  4800        0     0x20      0xFA
				  2400        0     0x20      0xF4

	 *  Timer2: (T2CON = 0x34)
			f(osc) = 12MHz
			    Baudrate    RCAP2H,RCAP2L(TH2,TL2)   T2MOD(only AT89C52/AT89S52)
				  38400       0xFF, 0xF6              0x00(error = 2.34%)
				  19200       0xFF, 0xEC              0x00(error = 2.34%)
				   9600       0xFF, 0xD9              0x00(error = 0.16%)
				   4800       0xFF, 0xB2              0x00(error = 0.16%)
	        f(osc) = 11.0592MHz
			    Baudrate    RCAP2H,RCAP2L(TH2,TL2)   T2MOD(only AT89C52/AT89S52)
			     115200       0xFF, 0xFD              0x00
				  57600       0xFF, 0xFA              0x00
				  38400       0xFF, 0xF7              0x00
				  19200       0xFF, 0xEE              0x00
				   9600       0xFF, 0xDC              0x00
				   4800       0xFF, 0xB8              0x00
				   2400       0xFF, 0x70              0x00
	*/

	TMOD  |= 0x20;
    SCON   = 0x50;
    PCON  |= 0x80;
	TH1    = 0xF3;
    TL1    = 0xF3;
	TR1    = 1;
}

#endif

