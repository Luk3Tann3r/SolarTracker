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
#include "gps.h"

/* --[ Local Definitions ]-- */

/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */
stGPS Gps;
/* --[ Public Data ]-- */

/* --[ Private Data ]-- */

/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	GPS_Initialise
 *
 * Description:
 * This function initialises the GPS module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void GPS_Initialise ( void )
{
    memset ( &Gps, 0, sizeof(Gps) );
}

/* --[ Function ] --
 *
 * Function Name:	GPS_Execute
 *
 * Description:
 * This function executes the GPS module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void GPS_Execute ( void )
{
    // Write to UART 2, obtain gps data and populate GPS structure
}
