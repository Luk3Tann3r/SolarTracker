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
#define UART2_BAUD 9600
#define UBRG2_VALUE (FCY/UART2_BAUD)/16 - 1
/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */

/* --[ Public Data ]-- */

/* --[ Private Data ]-- */

static unsigned int uiUbxCounter = 0;
static enUBX_MSG_TYPE MessageType = eUBX_MSG_N;
static char Temp_Buf[7] = {'0','0','0','0','0','0','0'};
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

void UART_Initialise ( int channel )
{
    switch ( channel )
    {
        case UART_1:
             
            U1BRG=UBRG1_VALUE; ///baud rate 19200
            U1MODEbits.ALTIO=0;
            IEC0bits.U1RXIE=1;
            U1STA&=0xfffc;
            U1MODEbits.UARTEN=1;
            U1STAbits.UTXEN=1;
            
            break;
            
        case UART_2:
            
            U2BRG=UBRG2_VALUE; ///baud rate 19200
            IEC1bits.U2RXIE=1;
            U2STA&=0xfffc;
            U2MODEbits.UARTEN=1;
            U2STAbits.UTXEN=1; 
   
            break;
            
    }
}

/* --[ Function ] --
 *
 * Function Name:	UART_Write
 *
 * Description:
 * Writes a single character to UART
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void UART_Write (int channel, unsigned int data )
{
    switch ( channel )
    {
        case UART_1:
    
            while (U1STAbits.TRMT==0);
            if(U1MODEbits.PDSEL == 3)
                U1TXREG = data;
            else
                U1TXREG = data & 0xFF;

            break;
            
        case UART_2:
            
            while (U2STAbits.TRMT==0);
            if(U2MODEbits.PDSEL == 3)
                U2TXREG = data;
            else
                U2TXREG = data & 0xFF;
            
            break;
            
        default:
            break;
    }
}

/* --[ Function ] --
 *
 * Function Name:	UART_WriteString
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

void UART_WriteString ( int channel, const char * s )
{
    while(*s)
        UART_Write(channel, *s++);
}

/* --[ Function ] --
 *
 * Function Name:	UART 1 ISR
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

void __attribute__((__interrupt__, __auto_psv__)) _U1RXInterrupt()
{
    // Process GUI commands
    IFS0bits.U1RXIF = 0;
    
    char tempRX = '0';
    tempRX = U1RXREG;
    
    /*switch (tempRX)
    {
        case: 'S'
    }*/
    
}

/* --[ Function ] --
 *
 * Function Name:	UART 2 ISR
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

void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt()
{
    char tempRX = '0';
    enUBX_MSG_TYPE TempMessageType; 
    IFS1bits.U2RXIF = 0;
    tempRX = U2RXREG;
    
    Temp_Buf[0] = Temp_Buf[1];
    Temp_Buf[1] = Temp_Buf[2];
    Temp_Buf[2] = Temp_Buf[3];
    Temp_Buf[3] = Temp_Buf[4];
    Temp_Buf[4] = Temp_Buf[5];
    Temp_Buf[5] = Temp_Buf[6];
    Temp_Buf[6] = U2RXREG;
    
//    if((Temp_Buf[0] == SYNC_BYTE_1) && (Temp_Buf[1] == SYNC_BYTE_2))
//    {
//        Gps.uiMessageCount++;
//    }

    if((Temp_Buf[1] == SYNC_BYTE_2) && (Temp_Buf[2] == NAV_CLASS))
    {
        Gps.uiMessageCount++;
        if (Temp_Buf[3] == NAV_POSLLH_ID)
        {
            MessageType = eNAV_POSLLH;
            uiUbxCounter = 0;
            
        }
        else if (Temp_Buf[3] == NAV_TIMEUTC_ID)
        {
            MessageType = eNAV_TIMEUTC;
            uiUbxCounter = 0;
            
        }
        else if (Temp_Buf[3] == NAV_STATUS_ID)
        {
            MessageType = eNAV_STATUS;
            uiUbxCounter = 0;
            
        }
    }
    
    switch(MessageType)
    {
        case eNAV_POSLLH:
            
            NAV_POSLLH_Buf[uiUbxCounter] = Temp_Buf[6];
            TempMessageType = eNAV_POSLLH; 
            uiPOSLLH_READY = 0;
            uiUbxCounter++;
            
            if(uiUbxCounter == NAV_POSLLH_LENGTH)
            {
               Gps.uiPosCount++;
               uiPOSLLH_READY = 1;
               TempMessageType = eUBX_MSG_N; 
            }
            break;
            
        case eNAV_TIMEUTC:
            
            NAV_TIMEUTC_Buf[uiUbxCounter] = Temp_Buf[6];
            TempMessageType = eNAV_TIMEUTC;
            uiTIMEUTC_READY = 0;
            uiUbxCounter++;

            if(uiUbxCounter == NAV_TIMEUTC_LENGTH)
            {
               Gps.uiTimeCount++;
               uiTIMEUTC_READY = 1;
               TempMessageType = eUBX_MSG_N; 
            }
            break;
            
        case eNAV_STATUS:
            
            NAV_STATUS_Buf[uiUbxCounter] = Temp_Buf[6];
            TempMessageType = eNAV_STATUS;
            uiSTATUS_READY = 0;
            uiUbxCounter++;
            
            if(uiUbxCounter == NAV_STATUS_LENGTH)
            {
               Gps.uiStatusCount++;
               uiSTATUS_READY = 1;
               TempMessageType = eUBX_MSG_N; 
            }
            break;
            
        default:
            TempMessageType = eUBX_MSG_N;
            break;
    }
    
    MessageType = TempMessageType;
       
}
