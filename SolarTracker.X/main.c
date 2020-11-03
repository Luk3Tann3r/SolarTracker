/* 
 * File:   main.c
 * Author: matthan.delport
 *
 * Created on 23 August 2020, 12:22
 */
#include <p30f4011.h>
#include <xc.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <libpic30.h>
#include "system.h"

#pragma config FOS = PRI, FPR = FRC_PLL16, WDT = WDT_OFF, FCKSMEN = CSW_FSCM_OFF
#pragma config FPWRT = PWRT_OFF, BOREN = PBOR_OFF, MCLRE = MCLR_DIS

int main(int argc, char** argv) {
    
    GPIO_Initialise( );
    ADC_Initialise( );
    PWM_Initialise ( );
    UART_Initialise ( UART_1 );
    UART_Initialise ( UART_2 );
    SUN_Initialise ( );
    SPA_Initialise( );
    GPS_Initialise ( );
    TELMAN_Initialise ( );
    OPER_Initialise ( );
    TIMER_Initialise ( );
    setupPID( ); //set up pid
    
    while(1)
    {
        //Stay here for eternity
    }
    
    return (EXIT_SUCCESS);
}

