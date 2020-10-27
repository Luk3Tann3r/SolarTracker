/* 
 * File:   sun.h
 * Author: matthan.delport
 *
 * Created on 27 August 2020, 20:07
 */

#ifndef SUN_H
#define	SUN_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct _stSUN
{	           
    float    fAngleZenith; 
    float    fAngleAzimuth;
    float    fAngleOfDeclination;
    
    long double modJulianDate;

} stSUN;

extern stSUN Sun;

void SUN_Initialise ( void );
void SUN_CalcAngles ( float fLatitude, float fLongitude );

#ifdef	__cplusplus
}
#endif

#endif	/* SUN_H */

