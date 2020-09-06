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
#define PWM_FREQ 50 //50 Hz
/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */

/* --[ Public Data ]-- */

/* --[ Private Data ]-- */

/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	PWM_Initialise
 *
 * Description:
 * This function initialises the PWM module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void PWM_Initialise ( void )
{
    // Configure PWM for free running mode
	// PWM period = Tcy * prescale * PTPER = 33ns * 64 * 9470 = 20ms
	PWMCON1 = 0x00FF; // Enable all PWM pairs in complementary mode
	PTCON = 0;
	_PTCKPS = 3;      // prescale=1:64 (0=1:1, 1=1:4, 2=1:16, 3=1:64)
	PTPER = FCY/(64*PWM_FREQ);     // 20ms PWM period (15-bit period value)
	PDC1 = 0;         // 0% duty cycle on channel 1 (max is 65536)
	PDC2 = 0;         // 0% duty cycle on channel 2 (max is 65536)
	PDC3 = 0;         // 0% duty cycle on channel 3 (max is 65536)
	PTMR = 0;         // Clear 15-bit PWM timer counter
	_PTEN = 1;        // Enable PWM time base
}

/* --[ Function ] --
 *
 * Function Name:	PWM_Set
 *
 * Description:
 * This function sets the PWM duty cycle of  
 * the specified PWM channel.
 * 
 *
 * Inputs:
 * Integer: Channel 1 - 3
 * Float: dutyCycle 0 - 1 (0 - 100%)
 *
 * Outputs:
 *
 * Notes:
 * 
 * Channel 1: Pin 37
 * Channel 2: Pin 35
 * Channel 3: Pin 33
 * 
 *
 */

void PWM_Set (int channel, float dutyCycle )
{
    switch ( channel )
    {
        case 1:
            PDC1 = (int)(2 * dutyCycle * PTPER ); 
            break;
            
        case 2:
            PDC2 = (int)(2 * dutyCycle * PTPER ); 
            break;
            
        case 3:
            PDC3 = (int)(2 * dutyCycle * PTPER ); 
            break;
            
        default:
            break;
    } 
}

