
#ifndef PID_H
#define	PID_H

void setupPID();

void enablePID();
void disablePID();
bool getPIDstate();

void setPidPoints(double a = 135.00, double z = 45.00);

double convertADCtoAngle(double adcVal,bool isAzimuth = false);
void setDirection(double PidVal,bool isAzimuth = false);
void runPID(double currentAngle,bool isAzimuth = false);



/* PID TIMER INTERRUPT */
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void);

/*Switch interrupts*/
void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt(void);
void __attribute__((__interrupt__, __auto_psv__)) _INT1Interrupt(void);

#endif
