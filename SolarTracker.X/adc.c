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
#include "adc.h"

/* --[ Local Definitions ]-- */

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

void ADC_Initialise ( void )
{
    ADPCFG = 0xFF00;     // Lowest 8 PORTB pins are analog inputs
	ADCON1 = 0;          // Manually clear SAMP to end sampling, start conversion
	ADCON2 = 0;          // Voltage reference from AVDD and AVSS
	ADCON3 = 0x0005;     // Manual Sample, ADCS=5 -> Tad = 3*Tcy
	ADCON1bits.ADON = 1; // Turn ADC ON
}

/* --[ Function ] --
 *
 * Function Name:	ADC_Read
 *
 * Description:
 * This function returns a decimal value representing the ADC voltage 
 * at the specified ADC channel.
 * 
 *
 * Inputs:
 * Integer: 0 - 3
 *
 * Outputs:
 * Float: 0 - 1
 *
 * Notes:
 * 
 * AN0: Pin 2
 * AN1: Pin 3
 * AN2: Pin 4
 * AN3: Pin 5
 *
 */

float ADC_Read ( int channel )
{
    unsigned int uiTemp;

    ADCHS = channel;          // Select the requested channel 
  
    ADCON1bits.SAMP = 1;      // start sampling
    __delay32(30);            // 1us delay @ 30 MIPS
    ADCON1bits.SAMP = 0;      // start Converting
    while (!ADCON1bits.DONE); // Should take 12 * Tad = 1.2us 
    uiTemp = ADCBUF0;
    
    return ((float)uiTemp)/1024;
}

