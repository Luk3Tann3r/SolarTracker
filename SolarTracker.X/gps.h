/* 
 * File:   gps.h
 * Author: matthan.delport
 *
 * Created on 27 August 2020, 20:36
 */

#ifndef GPS_H
#define	GPS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _stGPS
{	           
    int    iLongitude; 
    int    iLatitude;
    int    iAltitude;
    unsigned int    uiNtp4Time;
    
} stGPS;

extern stGPS Gps;

void GPS_Initialise ( void );
void GPS_Execute ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* GPS_H */

