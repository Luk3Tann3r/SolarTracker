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
#include "sun.h"

/* --[ Local Definitions ]-- */

/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */
stSUN Sun;
/* --[ Public Data ]-- */

/* --[ Private Data ]-- */

/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	SUN_Initialise
 *
 * Description:
 * This function initialises the Sun tracker module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void SUN_Initialise ( void )
{
    memset ( &Sun, 0, sizeof(Sun) );
}

/* --[ Function ] --
 *
 * Function Name:	SUN_CalcAngles
 *
 * Description:
 * This function calculates the azimuth and zenith angles of the Sun.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void SUN_CalcAngles ( int iLatitude, int iLongitude, unsigned int uiEpochTime )
{
    
}

