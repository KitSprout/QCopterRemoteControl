/* #include "QCopterRC_transport.h" */

#ifndef __QCOPTERRC_TRANSPORT_H
#define __QCOPTERRC_TRANSPORT_H

#include "stm32f4xx.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef struct {
  u8 Min;
  u8 Sec;
  u8 mSec;
} TRSTRUCT_TIME;
typedef struct {
  u16 KP;
  u16 KI;
  u16 KD;
} TRSTRUCT_PID;
typedef struct {
  u16 CH1;
  u16 CH2;
  u16 CH3;
  u16 CH4;
  u16 CH5;
  u16 CH6;
} TRSTRUCT_THROTTLE;
typedef struct {
  u8 Vol;
  u8 Cur;
  u16 Cap;
} TRSTRUCT_BATTERY;
typedef struct {
  s16 X;
  s16 Y;
  s16 Z;
} TRSTRUCT_SENSOR;
typedef struct {
  u16 Temp;
  u32 Press;
  u32 Height;
} TRSTRUCT_BAROMETER;
typedef struct {
  s16 X;
  s16 Y;
  s16 Z;
} TRSTRUCT_MOTION;
typedef struct {
  u32 Lon;
  u32 Lat;
} TRSTRUCT_GPS;
typedef __IO struct {
  u8 Packet;
  TRSTRUCT_TIME      Time;
  TRSTRUCT_PID       PID;
  TRSTRUCT_THROTTLE  Thr;
  TRSTRUCT_BATTERY   Batery;
  TRSTRUCT_SENSOR    Acc;
  TRSTRUCT_SENSOR    Gyr;
  TRSTRUCT_SENSOR    Mag;
  TRSTRUCT_BAROMETER Baro;
  TRSTRUCT_MOTION    Ang;
  TRSTRUCT_MOTION    Vel;
  TRSTRUCT_MOTION    Pos;
  TRSTRUCT_GPS       GPS;
} TR_RECV_DATA;
/*====================================================================================================*/
/*====================================================================================================*/
extern TR_RECV_DATA RF_RecvData;
/*====================================================================================================*/
/*====================================================================================================*/
void Transport_Recv( u8* RecvBuf );
void Transport_Send( u8* SendBuf );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
