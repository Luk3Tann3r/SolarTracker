/* 
 * File:   adc.h
 * Author: matthan.delport
 *
 * Created on 23 August 2020, 12:23
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

void ADC_Initialise ( void );
float ADC_Read ( int channel );

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

