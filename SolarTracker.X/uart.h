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

void UART_Initialise ( void );
char* UART1_Read ( int channel );
void UART1_Write (unsigned int data);
void UART1_WriteString ( const char * s );

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

