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
#define YEAR_PERIOD 				365.25
#define PI	            			3.14159265358979323846
#define TWOPI 						(2*PI)
#define SECONDS_PER_HOUR			3600		/* 60*60 */
#define SECONDS_PER_DAY				86400		/* 60*60*24 */
#define DIV(a,b) 					((a) / (b) - ((a) % (b) < 0))
#define LEAPS_THRU_END_OF(y) 		(DIV (y, 4) - DIV (y, 100) + DIV (y, 400))
#define	ISLEAP(year)				((year) % 4 == 0 && ((year) % 100 != 0 || (year) % 400 == 0))
/* --[ Default Settings ]-- */

/* --[ External Functions ]-- */

/* --[ External Data ]-- */
stSUN Sun;
/* --[ Public Data ]-- */

/* --[ Private Data ]-- */
static float fAzimuth = 0.0f;		/* default to 0 rad (0 deg) */
static float fZenith = PI/2.0f;	/* default to PI/2 rad (90 deg) */
/* --[ Private Functions ]-- */
static float ModifiedJulianDate (void);
static float TimeOfDayMinutes (void);
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

void SUN_CalcAngles ( float fLatitude, float fLongitude )
{
    /* Convert lat and long to radians */
    float fLatitude_Rad = fLatitude * (PI/180);     /* units = radians */
    float fLongitude_Rad = fLongitude * (PI/180);   /* units = radians */
    
    float f_mod_julian_date;		/* <Julian day number>.<Decimal fraction of a day> */
	float f_time_of_day;
    
	float f_tau_d;
	float f_declination_angle;
	float f_bn;						/* units = radians */
	float f_equ_of_time;
	float f_local_solar_time;
	float f_hour_angle;				/* units = radians */

    f_mod_julian_date = ModifiedJulianDate ( );
    //f_mod_julian_date = 59107.5;
    f_time_of_day = TimeOfDayMinutes ( );
    
    /* Calculate declination angle of earth at specific day and time of year */
	f_tau_d = TWOPI*(f_mod_julian_date)/YEAR_PERIOD;
	f_declination_angle = 0.006918 - 0.399912*cos ( f_tau_d ) +
		0.070257*sin ( f_tau_d ) - 0.006758*cos ( 2.0*f_tau_d ) +
		0.000907*sin ( 2.0*f_tau_d ) - 0.002697*cos ( 3.0*f_tau_d ) +
		0.001480*sin ( 3.0*f_tau_d );

	/* Calculate local solar time*/
	/* Equation of time */
	f_bn = (360.0 * (f_mod_julian_date - 80.0)/364.0) * PI/180.0;
	f_equ_of_time = (9.87*sin ( 2.0*f_bn )) - (7.53*cos ( f_bn )) - (1.5*sin ( f_bn ));

	/* Local Solar Time */
	f_local_solar_time = f_time_of_day + 4.0*(fLongitude_Rad*(180.0/PI)) + f_equ_of_time;

	/* Hour angle. f_local_solar_time-720 = minutes from solar noon +=E -=W */
	f_hour_angle = (0.25 * (f_local_solar_time-720.0))*PI/180.0;

	/* Calculate Elevation and Azimuth angles */
	/* Elevation angle from horizon */
	fZenith = asin ((cos (fLatitude_Rad)*cos (f_declination_angle)*cos (f_hour_angle)) + (sin (fLatitude_Rad)*sin (f_declination_angle)));
	/* Azimuth angle from true south */
	fAzimuth = acos ((cos (f_hour_angle)*cos (f_declination_angle)*sin (fLatitude_Rad) - sin (f_declination_angle)*cos (fLatitude_Rad))/cos (fZenith));

	/* Changes azim reference to north CW pos */
	fAzimuth = -1 * fAzimuth + PI;

	if ( f_hour_angle < -1.0*PI )
	{
		fAzimuth = TWOPI - fAzimuth;
	}
	else
	if ( (f_hour_angle > -1.0*PI)&&(f_hour_angle <= 0) )
	{
		fAzimuth = fAzimuth;
	}
	else
	if ( (f_hour_angle > 0)&&(f_hour_angle < PI) )
	{
		fAzimuth = TWOPI - fAzimuth;
	}
	else
	if ( f_hour_angle > PI )
	{
		fAzimuth = TWOPI + fAzimuth;
	}

	/* Limit the azimuth angle between 0 and 360 */
	if ( fAzimuth > TWOPI )
	{
		fAzimuth = fAzimuth - TWOPI;
	}
	else
	if ( fAzimuth < 0 )
	{
		fAzimuth = fAzimuth + TWOPI;
	}

	/* Only use positive elevation for sun angles calcs during day */
	if ( fZenith < 0 )
	{
		fZenith = 0;
	}
    
    Sun.fAngleAzimuth = fAzimuth * (180/PI);
    Sun.fAngleZenith = fZenith * (180/PI);
    Sun.fAngleOfDeclination = f_declination_angle * 180/PI;
    Sun.modJulianDate = f_mod_julian_date;
}


/* --[ Function ] --
 *
 * Function Name:	ModifiedJulianDate
 *
 * Description:
 * This function calculates the modified Julian date from UTC date.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

static float ModifiedJulianDate (void)
{
    double julianDate = 0;
    
    julianDate = 365.25 * ((Gps.uiYear - 1) + 4713);
    
    // Assuming we're in 2020
    switch(Gps.uiMonth)
    {
        case 1:
            julianDate += 0;
            break;
            
        case 2:
            julianDate += 31;
            break;
            
        case 3:
            julianDate += 60;
            break;
            
        case 4:
            julianDate += 91;
            break;
            
        case 5:
            julianDate += 121;
            break;
            
        case 6:
            julianDate += 152;
            break;
            
        case 7:
            julianDate += 182;
            break;
            
        case 8:
            julianDate += 213;
            break;
            
        case 9:
            julianDate += 244;
            break;
            
        case 10:
            julianDate += 274;
            break;
            
        case 11:
            julianDate += 305;
            break;
            
        case 12:
            julianDate += 335;
            break;
            
        default:
            break;
    }
    
    julianDate += (Gps.uiDay - 1);
    
    // Calculate fractional part
    
    float dayFraction = 0;
    
    dayFraction = ((float)Gps.uiUTCHour) / 24 + ((float)Gps.uiUTCMinute) / (24*60) + ((float)Gps.uiUTCSecond) / (SECONDS_PER_DAY);
    
    if(dayFraction > 0.5)
    {
        julianDate += (dayFraction - 0.5);
    }
    else
    {
        julianDate -= 1;
        julianDate += (dayFraction + 0.5);
    }
    
    return (float)(julianDate - 2400000.5);
}

/* --[ Function ] --
 *
 * Function Name:	TimeOfDayMinutes
 *
 * Description:
 * This function calculates the time of day in minutes.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Notes:
 *
 */

static float TimeOfDayMinutes (void)
{
    float timeOfDay;
    
    timeOfDay = (Gps.uiUTCHour * 60) + Gps.uiUTCMinute + (((float)Gps.uiUTCSecond)/60);
    
    return timeOfDay;
}
