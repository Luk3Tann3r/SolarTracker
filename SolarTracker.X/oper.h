/* 
 * File:   oper.h
 * Author: matthan.delport
 *
 * Created on 23 August 2020, 14:04
 */

#ifndef OPER_H
#define	OPER_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _stOPER
{	           
    unsigned long int sysTick;
} stOPER; 

extern stOPER Oper;

void OPER_Initialise ( void );
void OPER_Execute ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* OPER_H */

