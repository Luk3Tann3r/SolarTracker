/* 
 * File:   system.h
 * Author: matthan.delport
 *
 * Created on 23 August 2020, 12:24
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

#if !defined( ADC_H )
#include "adc.h"
#endif
    
#if !defined( GPIO_H )
#include "gpio.h"
#endif  
    
#if !defined( GPS_H )
#include "gps.h"
#endif 
    
#if !defined( OPER_H )
#include "oper.h"
#endif
    
#if !defined( PWM_H )
#include "pwm.h"
#endif
    
#if !defined( SENSOR_H )
#include "sensor.h"
#endif
    
#if !defined( SPA_H )
#include "spa.h"
#endif    
    
#if !defined( SUN_H )
#include "sun.h"
#endif
    
#if !defined( TELEMETRY_H )
#include "telemetry.h"
#endif 
        
#if !defined( TELMAN_H )
#include "telman.h"
#endif 
    
#if !defined( TIMER_H )
#include "timer.h"
#endif
    
#if !defined( UART_H )
#include "uart.h"
#endif
    
#if !defined( PID_H )
#include "pid.h"
#endif    
    
#define sysclock 120000000UL
#define FCY sysclock/4

#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

