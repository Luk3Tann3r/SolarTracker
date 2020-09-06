/* 
 * File:   pwm.h
 * Author: matthan.delport
 *
 * Created on 23 August 2020, 12:23
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void PWM_Initialise ( void );
void PWM_Set (int channel, float dutyCycle );

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

