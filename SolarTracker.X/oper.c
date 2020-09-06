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
#include "oper.h"

/* --[ Local Definitions ]-- */

/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */

/* --[ Public Data ]-- */

/* --[ Private Data ]-- */
static unsigned short usBlink = 0;
char buffer[20];
/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	OPER_Initialise
 *
 * Description:
 * This function initialises the OPER module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void OPER_Initialise ( void )
{

}

/* --[ Function ] --
 *
 * Function Name:	OPER_Execute
 *
 * Description:
 * This function executes the OPER module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void OPER_Execute ( void )
{
    // Gather sensor data
    SENSOR_Execute ( );
    // Gather GPS data
    GPS_Execute ( );
    // Calculate sun angles
//    SUN_CalcAngles ( );
    
    //PID based on sensors and sun angles
    
    //Motor control to execute PID
    
    //Transmit to GUI
    
    //Print out first pot value to serial
    sprintf(buffer, "%f\r", sensor.fAngleAzimuth);
    UART1_WriteString ( buffer );
    
    //Use sensor outputs on remaining 3 pots to control PWM
    PWM_Set( 1, sensor.fAngleZenith);
    PWM_Set( 2, sensor.fCurrentAzimuth);
    PWM_Set( 3, sensor.fCurrentZenith);
    
    
    //Toggle Pin 6 for fun
    if(usBlink == 0)
    {
        usBlink = 1;
        LATBbits.LATB4 = 1;
    }
    else
    {
        usBlink = 0;
        LATBbits.LATB4 = 0;
    }
}
