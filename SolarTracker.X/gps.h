/* 
 * File:   gps.h
 * Author: matthan.delport
 *
 * Created on 27 August 2020, 20:36
 */

#ifndef GPS_H
#define	GPS_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SYNC_BYTE_1 0xB5
#define SYNC_BYTE_2 0x62    
#define NAV_CLASS 0x01 
    
#define NAV_POSLLH_ID 0x02 
#define NAV_TIMEUTC_ID 0x21 
#define NAV_STATUS_ID 0x03 
    
#define NAV_POSLLH_LENGTH 28
#define NAV_TIMEUTC_LENGTH 20    
#define NAV_STATUS_LENGTH 16
    
#define BUF_SIZE 128
    
typedef enum _enUBX_MSG_TYPE
{
	eNAV_POSLLH = 0,
	eNAV_TIMEUTC,
	eNAV_STATUS,
	eUBX_MSG_N
} enUBX_MSG_TYPE;

typedef struct _stGPS
{	 
    unsigned int    uiFixed;
    
    float fLongitude; 
    float fLatitude;
    float fAltitude;
    
    unsigned long int    ulUTCTime; // hhmmss
    unsigned int    uiUTCHour;
    unsigned int    uiUTCMinute;
    unsigned int    uiUTCSecond;
    
    unsigned long int    ulDate; // ddmmyy
    unsigned int    uiDay;
    unsigned int    uiMonth;
    unsigned int    uiYear;
    
    unsigned long long int    uiEpochTime;
    
    unsigned int uiMessageCount;
    unsigned int uiPosCount;
    unsigned int uiTimeCount;
    unsigned int uiStatusCount;
     
    
} stGPS;

extern stGPS Gps;
extern char NAV_POSLLH_Buf[BUF_SIZE];
extern char NAV_TIMEUTC_Buf[BUF_SIZE];
extern char NAV_STATUS_Buf[BUF_SIZE];
extern unsigned int uiPOSLLH_READY;
extern unsigned int uiTIMEUTC_READY;
extern unsigned int uiSTATUS_READY;

void GPS_Initialise ( void );
void GPS_Execute ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* GPS_H */

