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
#include "telman.h"

/* --[ Local Definitions ]-- */

/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */
stTELMAN Telman;
/* --[ Public Data ]-- */

/* --[ Private Data ]-- */
char buffer[128];
/* --[ Private Functions ]-- */

/* --[ Function ] --
 *
 * Function Name:	TELMAN_Initialise
 *
 * Description:
 * This function initialises the telemetry module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void TELMAN_Initialise ( void )
{
    memset ( &Telman, 0, sizeof(Telman) );
}

/* --[ Function ] --
 *
 * Function Name:	TELMAN_Execute
 *
 * Description:
 * This function executes the telemetry module
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

void TELMAN_Execute ( void )
{   
    sprintf(buffer, "$%lu,%lu,%lu,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\r\n", Oper.sysTick, Gps.ulDate, Gps.ulUTCTime, (double)Gps.fLatitude, (double)Gps.fLongitude, (double)Gps.fAltitude,
            (double)Sun.fAngleAzimuth, (double)Sun.fAngleZenith, (double)Sun.fAngleOfDeclination,
            (double)sensor.fAngleAzimuth, (double)sensor.fAngleZenith, (double)sensor.fCurrentAzimuth, (double)Sun.modJulianDate);
    //sprintf(buffer, "$%lu,%u,%u,%u,%u,%u,%f,%f,%f,%u,%u,%u,%u\r\n", Oper.sysTick, Gps.uiMessageCount, Gps.uiPosCount, Gps.uiTimeCount, Gps.uiStatusCount, Gps.uiUTCSecond, (double)Gps.fLongitude, (double)Gps.fLatitude , (double)Gps.fAltitude, NAV_TIMEUTC_Buf[0],NAV_TIMEUTC_Buf[1],NAV_TIMEUTC_Buf[2],NAV_TIMEUTC_Buf[3]);
    UART_WriteString (UART_1, buffer );
}

