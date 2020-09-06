/* 
 * File:   sensor.h
 * Author: matthan.delport
 *
 * Created on 23 August 2020, 15:39
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
typedef struct _stSENSOR
{	           
    float    fAngleZenith; 
    float    fAngleAzimuth;
    float    fCurrentZenith; 
    float    fCurrentAzimuth;

} stSENSOR;

extern stSENSOR sensor;

void SENSOR_Initialise ( void );
void SENSOR_Execute ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

