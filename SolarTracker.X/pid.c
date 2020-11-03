

/* --[ Include Files ]-- */
#include <xc.h>
#include <libpic30.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "system.h"
#include "pwm.h"
#include "sensor.h"

/* ########### Notes ########### */

/*
  ^^^^^^^ Dependencies ^^^^^^^^
 system.h
 PWM.h
 Sensors.h
 */

/*
  ^^^^^^^ Functions ^^^^^^^^
 * Have a look at the predefined variables of the functions in the pid.h file
 */

/*
 * PINS USED 
 * - Switch Interrupts -> pin 17 (INT0) and 23 (INT1) 
 * - Motor Direction -> pin 22 (RD2) and 19(RD3)
 * 
 * - PWM -> pin 35 (PWM2H) and 33 (PWM3H)
 */


/* PID
 * These were selected manually 
 If these values do not work - Tune loop manually by graphing the finalPID values ( print them to uart and take it from there )

 Set ki and kd = 0
 increase Kp slowly until it shows an underdamped response 
 then 
 adjust Ki to reduce the steady state error ( steps of +0.1)
 Once steady state is found
 adjust kd to to reduce the overshoot
 */

/* ########### Notes ########### */

/* Define variables */
/* PID gains Azimuth */
double kp1 = 2;
double ki1 = 0.01;
double kd1 = 0.02;

/* PID gains Zenith */
double kp2 = 2;
double ki2 = 0.01;
double kd2 = 0.02;

double azimuthSetpoint = 0; // Setpoint is set from function
double zenethSetpoint = 0;

double lastErrorA = 0; // Last error terms 
double lastErrorZ = 0;

double integratorA = 0;// Integrator Terms
double integratorZ = 0;

bool enableAzimuth = true; // Cases for motors to be stopped 
bool enableZeneth = true;

int counterA = 0; // Counters for motors to be stopped
int counterZ = 0;
/* End Define variables */

void setupPID(){
    /* Have pid run on timer 2 */
    int pidFreq = 11;// ~10kHz
    
    T2CON = 0;            // Clear the Timer 1 configuration
	TMR2 = 0;             // Reset Timer 1 counter
	PR2 = FCY/(256*pidFreq);          // Set the Timer 1 period (max 65535) 
	T2CONbits.TCS = 0;    // Select internal clock (Fosc/4)
	T2CONbits.TCKPS = 2;  // Prescaler (0=1:1, 1=1:8, 2=1:64, 3=1:256)
	_T2IP = 1;            // Set the Timer 1 interrupt priority
	_T2IF = 0;            // Clear the Timer 1 interrupt flag
	_T2IE = 1;            // Enable Timer 1 interrupt
	T2CONbits.TON = 0;    // Turn on Timer 1
    
    
    /* Switch interrupt */
    /* PIN 17 and pin 23*/
    INTCON2bits.INT0EP = 1;
    IEC1bits.INT1IE = 1;
    IFS1bits.INT1IF = 0;
    
    INTCON2bits.INT1EP = 1;
    IEC0bits.INT0IE = 1;
    IFS0bits.INT0IF = 0;
}

void enablePID(){
    T2CONbits.TON = 1; 
}
void disablePID(){
    T2CONbits.TON = 0; 
}

bool getPIDstate(){
    if(T2CONbits.TON == 1){
        return true;
    }else{
        return false;
    }
}

void setPidPoints(double a, double z){ // Set the PID setpoints 
    if(a >= 0){
        azimuthSetpoint = a;
    }
    
    if(z >= 0){
        zenethSetpoint  = z;
    }
    
}

double convertADCtoAngle(double adcVal,bool isAzimuth){
    double angle = 0.0;
    //could use 
    if( isAzimuth ){
        //Relate voltage to degrees
        angle = adcVal/360;
    }else{
        angle = adcVal/360; 
    }
    
    return angle;
}

void setDirection(double PidVal,bool isAzimuth){
    // D2 and D3 
    //pin 22 (RD2) and 19(RD3)
    int PWMdirection = PidVal < 0 ? 0 : 1;
    
    if(isAzimuth){
        LATDbits.LATD2 = PWMdirection;
        
    }else{
        LATDbits.LATD3 = PWMdirection;
    }
}

void runPID(double currentAngle,bool isAzimuth){

    /*Init with default vals*/
double funcKp = 2;
double funcKi = 0.01;
double funcKd = 0.02;

double integratorTerm = 0.0;
double diffTerm = 0.0;

double lastErr = 0.0;

double setpointAngle = 0;

    if(isAzimuth){
        if( !enableAzimuth ){ // Stopping because current is too high
            PWM_Set ( 2, 0 );
            return;
        }
        /*Set specific PID constants */
        funcKp = kp1;
        funcKi = ki1;
        funcKd = kd1;
        setpointAngle = azimuthSetpoint;
        integratorTerm = integratorA;
        lastErr = lastErrorA;
    }else{
        if(!enableZeneth){// Stopping because current is too high
            PWM_Set ( 3, 0 );
            return;
        }
        
        /*Set specific PID constants */
        funcKp = kp2;
        funcKi = ki2;
        funcKd = kd2;  
        setpointAngle = zenethSetpoint;
        integratorTerm = integratorZ;
        lastErr = lastErrorZ;
    }

double error = setpointAngle - currentAngle; //Calculate error

double propTerm = funcKp * error; // Calculate the Proportional adjustment

integratorTerm += funcKi * error; //Calculate the Integrators' adjustment - could multiply error with sample time for better accuracy

/* Check if the integrator will push PID over bounds */
if(integratorTerm > PR2){
    integratorTerm = PR2;
}else if(integratorTerm < (-1)*PR2){
    integratorTerm = (-1)*PR2;
}

diffTerm = ( -funcKd ) * ( error - lastErr ); //Calculate the Differentiator's adjustment - could divide error difference with sample time for better accuracy 

double finalPID = propTerm + integratorTerm + diffTerm; // Final PID adjustment calculation

/* Check if the new duty cycle will go over bounds */
if(finalPID > PR2){
    finalPID = PR2;
}else if(finalPID < (-1)*PR2){
    finalPID = (-1)*PR2;
}

if( finalPID > -3 && finalPID < 3){ /* Correct position give or take some tolerance*/
    finalPID = 0; /* Stop motor - Duty cycle 0% */
}

/* if final PID value is -ve it will move motor backwards and +ve moves motor forwards */
    setDirection(finalPID, isAzimuth);
    
    if(isAzimuth){     
        /* Set PWM */
        PWM_Set ( 2, finalPID );
        /*Store variables for next run */
        integratorA = integratorTerm;
        lastErrorA = lastErr;
    }else{
        /* Set PWM */
        PWM_Set ( 3, finalPID );
        /*Store variables for next run */
        integratorZ = integratorTerm;
        lastErrorZ = lastErr;
    }
 
}

/* PID TIMER INTERRUPT */
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void){
    
	_T2IF = 0;
    
    /* Read all ADC values before running PID */
    SENSOR_Execute();

    //Define your current setpoint here
    double currentLimit = 1.5;
    
    /* MOTOR current checks */
    if(sensor.fCurrentAzimuth >= currentLimit  || !enableAzimuth ){ // Current went over limit stop system, increment counter 
        enableAzimuth = false;
        counterA++;
    }
    
    if( counterA >= 1000){//Wait 1 ms then enable the motor again
        counterA = 0; //reset counter
        enableAzimuth = true;
    }
    
   /* MOTOR current checks */
    if(sensor.fCurrentZenith >= currentLimit || !enableZeneth){ // Current went over limit stop system, increment counter 
        enableZeneth = false;
        counterZ++;
    }
    
    if( counterZ >= 1000){//Wait 1 ms then enable the motor again
        counterZ = 0;
        enableZeneth = true;
    }
    
    double angleA = convertADCtoAngle(sensor.fAngleAzimuth,true);// get angle
    
    runPID(angleA,true);//run pid with angle from sensor 
            
    double angleZ = convertADCtoAngle(sensor.fAngleZenith,true);
    
    runPID(angleZ,false);
    
}

/*Switch interrupts*/

/*Azimuth switch hit */  
void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt(void){
    IFS0bits.INT0IF = 0;
    /*Azimuth switch hit */   
    /* No need to check which switch was hit, the PID will automatically change the direction based on the error */
    PWM_Set ( 2, 0 );// turn off pwm -> Make a 0 duty cycle
    setPidPoints(135.00,-1.0);//set new setpoint to be halfway and leave the other unchanged
}

/*Zenith switch hit */
void __attribute__((__interrupt__, __auto_psv__)) _INT1Interrupt(void){
    IFS1bits.INT1IF = 0;
    /* No need to check which switch was hit, the PID will automatically change the direction based on the error */
    PWM_Set ( 3, 0 );// turn off pwm -> Make a 0 duty cycle
    setPidPoints(-1.0, 45.00);//set new setpoint to be halfway and leave the other unchanged

}

