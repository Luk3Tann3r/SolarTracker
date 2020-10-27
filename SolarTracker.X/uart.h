/* 
 * File:   uart.h
 * Author: matthan.delport
 *
 * Created on 23 August 2020, 16:27
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
    
/* UART definition */
#define UART_1 (int)(0)
#define UART_2 (int)(1)

void UART_Initialise ( int channel );
char* UART_Read ( int channel );
void UART_Write (int channel, unsigned int data);
void UART_WriteString (int channel, const char * s );

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

