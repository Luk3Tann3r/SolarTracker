/* 
 * File:   telman.h
 * Author: matthan.delport
 *
 * Created on 19 September 2020, 17:25
 */

#ifndef TELMAN_H
#define	TELMAN_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct _stTELMAN
{	           
    stTELEM_PAGE curPage;
} stTELMAN;

extern stTELMAN Telman;

void TELMAN_Initialise ( void );
void TELMAN_Execute ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* TELMAN_H */

