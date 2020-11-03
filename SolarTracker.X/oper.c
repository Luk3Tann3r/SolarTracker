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
#include "pid.h"

/* --[ Local Definitions ]-- */
#define SUB_EXECUTE_RATE 10
#define TELMAN_INDEX 0
#define SUN_INDEX 1
/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */
stOPER Oper; 
/* --[ Public Data ]-- */

/* --[ Private Data ]-- */
static unsigned short usBlink = 0;
//char buffer[20];
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
    memset ( &Oper, 0, sizeof(Oper) );
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
    Oper.sysTick++;
    // Gather sensor data
    SENSOR_Execute ( );
    
    //Implement function to control motors with PID
    
    // Gather GPS data
    GPS_Execute ( );
    // Execute telemetry module
    if((Oper.sysTick + TELMAN_INDEX )% SUB_EXECUTE_RATE == 0 )
    {
        TELMAN_Execute ( );
    }
    
    // Calculate sun angles
    if((Oper.sysTick + SUN_INDEX )% SUB_EXECUTE_RATE == 0 )
    {
        //SUN_CalcAngles ( Gps.fLatitude, Gps.fLongitude );
        
        SPA_DATA.year          = 2003;
        SPA_DATA.month         = 10;
        SPA_DATA.day           = 17;
        SPA_DATA.hour          = 12;
        SPA_DATA.minute        = 30;
        SPA_DATA.second        = 30;
        SPA_DATA.timezone      = -7.0;
        SPA_DATA.delta_ut1     = 0;
        SPA_DATA.delta_t       = 67;
        SPA_DATA.longitude     = -105.1786;
        SPA_DATA.latitude      = 39.742476;
        SPA_DATA.elevation     = 1830.14;
        SPA_DATA.pressure      = 820;
        SPA_DATA.temperature   = 11;
        SPA_DATA.slope         = 30;
        SPA_DATA.azm_rotation  = -10;
        SPA_DATA.atmos_refract = 0.5667;

        
        
        SPA_DATA.function = SPA_ZA;        // Switch to choose functions for desired output (from enumeration)
        
        spa_calculate(&SPA_DATA);
    }

    //PID based on sensors and sun angles
    /* ############# PID AND MOTOR CONTROL ############# */
    
    if( !getPIDstate()){ //Turn PID and its interrupts on
        enablePID();

    }else{
        //PID is on and running 
        //Add logic here if you want it to stop
    }
    
    /* Set the setpoint for both motors */
    setPidPoints(spa_data.azimuth,spa_data.zenith);
    
    //Motor control to execute PID
    
    //Transmit to GUI
    
    //Print out first pot value to serial
//    sprintf(buffer, "%f\r", sensor.fAngleAzimuth);
//    UART1_WriteString ( buffer );
    
    //Use sensor outputs on remaining 3 pots to control PWM
    /*
    PWM_Set( 1, sensor.fAngleZenith);
    PWM_Set( 2, sensor.fCurrentAzimuth);
    PWM_Set( 3, sensor.fCurrentZenith);
    */
    
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
