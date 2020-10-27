/* 
 * File:   telemetry.h
 * Author: matthan.delport
 *
 * Created on 20 September 2020, 12:44
 */

#ifndef TELEMETRY_H
#define	TELEMETRY_H

#ifdef	__cplusplus
extern "C" {
#endif

/* Pack structures tightly */
#pragma pack(push, 1)
    
/* --[ Public Definitions ]-- */
#define SYNCWORD_START 0x6364
#define SYNCWORD_END 0x6364
    
/* Telemetry Page */
typedef struct _stTELEM_PAGE
{
	/* Header */
	uint16_t SyncWord1; /**/
//	uint16_t TimestampSec;
//	struct
//	{
//		uint8_t Year;
//		uint8_t Month;
//		uint8_t Day;
//		uint8_t Hour;
//		uint8_t Min;
//		uint8_t Sec;   
//	} Gps;
//	/* Sensor Telemetry */
//	struct
//	{
//		uint16_t zenithAngle;
//        uint16_t azimuthAngle;
//        uint16_t zenithCurrent;
//        uint16_t azimuthCurrent;
//	} Sensors;

	uint16_t SyncWord2;

} stTELEM_PAGE;

/* Restore packing */
#pragma pack(pop)

#ifdef	__cplusplus
}
#endif

#endif	/* TELEMETRY_H */

