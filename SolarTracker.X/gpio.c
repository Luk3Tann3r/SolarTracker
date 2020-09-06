
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
#include "gpio.h"

/* --[ Local Definitions ]-- */

/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */

/* --[ Public Data ]-- */

/* --[ Private Data ]-- */

/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	GPIO_Initialise
 *
 * Description:
 * This function initialises the GPIO module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void GPIO_Initialise ( void )
{
    TRISF = 0b0011111;
    TRISFbits.TRISF0 = 1;
    TRISFbits.TRISF1 = 0;
   
    //Analog input
    TRISBbits.TRISB0 = 1;   //AN 0
    TRISBbits.TRISB1 = 1;   //AN 1
    TRISBbits.TRISB2 = 1;   //AN 2
    TRISBbits.TRISB3 = 1;   //AN 3
    //Digital Output
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    TRISBbits.TRISB8 = 0;
    PORTB = 0x0000;
    
    TRISCbits.TRISC13 = 0;
    TRISCbits.TRISC14 = 0;
    TRISCbits.TRISC15 = 0;
    PORTC = 0x0000;
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD2 = 0;
    TRISDbits.TRISD3 = 0;
    PORTD = 0x0000;
}
