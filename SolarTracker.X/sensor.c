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
#include "sensor.h"

/* --[ Local Definitions ]-- */

/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */

/* --[ Public Data ]-- */

/* --[ Private Data ]-- */
stSENSOR sensor;
/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	SENSOR_Initialise
 *
 * Description:
 * This function initialises the sensor module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void SENSOR_Initialise ( void )
{
    memset ( &sensor, 0, sizeof(sensor) );
}

/* --[ Function ] --
 *
 * Function Name:	SENSOR_Execute
 *
 * Description:
 * This function executes the sensor module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void SENSOR_Execute ( void )
{
    sensor.fAngleAzimuth = ADC_Read (0);
    sensor.fAngleZenith = ADC_Read (1);
    sensor.fCurrentAzimuth = ADC_Read (2);
    sensor.fCurrentZenith = ADC_Read (3);
}

