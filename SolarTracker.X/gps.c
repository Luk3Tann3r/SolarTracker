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
char NAV_POSLLH_Buf[BUF_SIZE];
char NAV_TIMEUTC_Buf[BUF_SIZE];
char NAV_STATUS_Buf[BUF_SIZE];
unsigned int uiPOSLLH_READY = 0;
unsigned int uiTIMEUTC_READY = 0;
unsigned int uiSTATUS_READY = 0;
/* --[ Public Data ]-- */

/* --[ Private Data ]-- */
typedef struct _stPOSLLH
{	 
    unsigned long int timeOfWeekMs;
    long int longitude; /* 1e-7 scaling (deg)*/
    long int latitude; /* 1e-7 scaling (deg)*/
    long int heightAboveElipsoid;
    long int heightAboveSea; /*(mm)*/
    unsigned long int HoriAcc;
    unsigned long int VertiAcc;
} stPOSLLH;

typedef struct _stTIMEUTC
{	 
    unsigned long int timeOfWeekMs;
    unsigned long int timeAccuracyNs;
    long int nanosecondsUTC;
    unsigned int yearUTC;
    unsigned char monthUTC;
    unsigned char dayUTC;
    unsigned char hourUTC;
    unsigned char minUTC;
    unsigned char secUTC;
    union
	{
	unsigned char		_ucharval;
	struct
	{
    unsigned char		ucSpare1	: 2;
	unsigned char		ucUTCvalid	: 1;	
	unsigned char		ucSpare2	: 5;	
	}
	_bitval;
	}
	valid;

} stTIMEUTC;

typedef struct _stSTATUS
{	 
    unsigned long int timeOfWeekMs;
    unsigned char gpsFix;
    union
	{
	unsigned char		_ucharval;
	struct
	{
	unsigned char		ucGpsFixOk	: 1;	
	unsigned char		ucSpare		: 7;	
	}
	_bitval;
	}
	flags;
    unsigned char fixStat;
    unsigned char flags2;
    unsigned long int timeToFirstFix;
    unsigned long int timeSinceStartup;
} stSTATUS;

static stPOSLLH POSLLH;
static stTIMEUTC TIMEUTC;
static stSTATUS STATUS;
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
    memset ( &POSLLH, 0, sizeof(POSLLH) ); 
    memset ( &TIMEUTC, 0, sizeof(TIMEUTC) ); 
    memset ( &STATUS, 0, sizeof(STATUS) ); 
    memset ( &NAV_POSLLH_Buf, 0, sizeof(NAV_POSLLH_Buf) ); 
    memset ( &NAV_TIMEUTC_Buf, 0, sizeof(NAV_TIMEUTC_Buf) );
    memset ( &NAV_STATUS_Buf, 0, sizeof(NAV_STATUS_Buf) );
    
    /* Init GPS data to known values on start-up */
    
    Gps.uiFixed = 0;
    
    Gps.fLatitude = -25.754;
    Gps.fLongitude = 28.228;
    Gps.fAltitude = 1300;
    
    Gps.ulUTCTime = 100000;
    Gps.uiUTCHour = 10;
    Gps.uiUTCMinute = 0;
    Gps.uiUTCSecond = 0;
    
    Gps.ulDate = 251020;
    Gps.uiDay = 25;
    Gps.uiMonth = 10;
    Gps.uiYear = 2020;
    
    Gps.uiEpochTime = 1577880000;
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
    if(uiPOSLLH_READY == 1)
    {
        memcpy(&POSLLH, (void *)NAV_POSLLH_Buf, NAV_POSLLH_LENGTH);
    }
    
    if(uiTIMEUTC_READY == 1)
    {       
        memcpy(&TIMEUTC, (void *)NAV_TIMEUTC_Buf, NAV_TIMEUTC_LENGTH);
    }
    
    if(uiSTATUS_READY == 1)
    {       
        memcpy(&STATUS, (void *)NAV_STATUS_Buf, NAV_STATUS_LENGTH);
    }
    
    TIMEUTC.valid._bitval.ucUTCvalid = 0;
    
    if(TIMEUTC.valid._bitval.ucUTCvalid == 1)
    {
        Gps.uiUTCSecond = TIMEUTC.secUTC;
        Gps.uiUTCMinute = TIMEUTC.minUTC;
        Gps.uiUTCHour = TIMEUTC.hourUTC;       
        
        Gps.uiDay = TIMEUTC.dayUTC;
        Gps.uiMonth = TIMEUTC.monthUTC;
        Gps.uiYear = TIMEUTC.yearUTC;
        
         /* Used for telemetry purposes */
        unsigned long long int hour = Gps.uiUTCHour;
        Gps.ulUTCTime = hour*10000 + Gps.uiUTCMinute*100 + Gps.uiUTCSecond;
        
        unsigned long long int year = Gps.uiYear;
        Gps.ulDate = year*10000 + Gps.uiMonth*100 + Gps.uiDay;
    }
    
    Gps.uiFixed = STATUS.flags._bitval.ucGpsFixOk;
    
    if((Gps.uiFixed == 1) || (TIMEUTC.valid._bitval.ucUTCvalid == 1))
    {
        Gps.fLongitude = POSLLH.longitude/10000000;
        Gps.fLatitude = POSLLH.latitude/10000000;
        Gps.fAltitude = POSLLH.heightAboveSea/1000;
    }
}

