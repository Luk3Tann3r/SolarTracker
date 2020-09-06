/* 
 * Abstract:
 *
 *
 * 
 */

/* --[ Include Files ]-- */
#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "system.h"
#include "uart.h"

/* --[ Local Definitions ]-- */
#define UART1_BAUD 19200
#define UBRG1_VALUE (FCY/UART1_BAUD)/16 - 1
#define UART2_BAUD 19200
#define UBRG2_VALUE (FCY/UART2_BAUD)/16 - 1
/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */

/* --[ Public Data ]-- */

/* --[ Private Data ]-- */

/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	UART_Initialise
 *
 * Description:
 * This function initialises the UART module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void UART_Initialise ( void )
{
    /* UART 1 */
    U1BRG=UBRG1_VALUE; ///baud rate 19200
    U1MODEbits.ALTIO=0;
    IEC0bits.U1RXIE=1;
    U1STA&=0xfffc;
    U1MODEbits.UARTEN=1;
    U1STAbits.UTXEN=1;
}

/* --[ Function ] --
 *
 * Function Name:	UART1_Write
 *
 * Description:
 * Writes a single character to UART1
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void UART1_Write ( unsigned int data )
{
    while (U1STAbits.TRMT==0);
    if(U1MODEbits.PDSEL == 3)
        U1TXREG = data;
    else
        U1TXREG = data & 0xFF;
}

/* --[ Function ] --
 *
 * Function Name:	UART1_WriteString
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void UART1_WriteString ( const char * s )
{
    while(*s)
            UART1_Write(*s++);
}