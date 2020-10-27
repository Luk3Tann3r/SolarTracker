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
#include "timer.h"

/* --[ Local Definitions ]-- */
#define SYS_TICK 5 //5 Hz System tick

/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */

/* --[ Public Data ]-- */

/* --[ Private Data ]-- */

/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	ADC_Initialise
 *
 * Description:
 * This function initialises the ADC module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void TIMER_Initialise ( void )
{
    T1CON = 0;            // Clear the Timer 1 configuration
	TMR1 = 0;             // Reset Timer 1 counter
	PR1 = FCY/(256*SYS_TICK);          // Set the Timer 1 period (max 65535)
	T1CONbits.TCS = 0;    // Select internal clock (Fosc/4)
	T1CONbits.TCKPS = 2;  // Prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
	_T1IP = 1;            // Set the Timer 1 interrupt priority
	_T1IF = 0;            // Clear the Timer 1 interrupt flag
	_T1IE = 1;            // Enable Timer 1 interrupt
	T1CONbits.TON = 1;    // Turn on Timer 1
}


/* --[ Function ] --
 *
 * Function Name:	T1Interrupt
 *
 * Description:
 * This function services the Timer 1 interrupt
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void){
    
	_T1IF = 0;
    
    OPER_Execute ( );  
}