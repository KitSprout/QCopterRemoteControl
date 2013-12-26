/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "QCopterRC_transport.h"
#include "module_nrf24l01.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
TR_RECV_DATA RF_RecvData;
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Transport_Recv
**功能 : 紀錄接收資料
**輸入 : Recv_Buf
**輸出 : None
**使用 : Transport_Recv(RxBuf);
**=====================================================================================================*/
/*=====================================================================================================*/
void Transport_Recv( u8* RecvBuf )
{
  RF_RecvData.Packet    = (u8)RecvBuf[0];
  RF_RecvData.Time.Min  = (u8)RecvBuf[1];
  RF_RecvData.Time.Sec  = (u8)RecvBuf[2];
  RF_RecvData.Time.mSec = (u8)RecvBuf[3];

  switch(RF_RecvData.Packet) {

    case 0x01:
      RF_RecvData.PID.KP      = (u16)Byte16(RecvBuf[4],  RecvBuf[5]);
      RF_RecvData.PID.KI      = (u16)Byte16(RecvBuf[6],  RecvBuf[7]);
      RF_RecvData.PID.KD      = (u16)Byte16(RecvBuf[8],  RecvBuf[9]);
      RF_RecvData.Thr.CH1     = (u16)Byte16(RecvBuf[10], RecvBuf[11]);
      RF_RecvData.Thr.CH2     = (u16)Byte16(RecvBuf[12], RecvBuf[13]);
      RF_RecvData.Thr.CH3     = (u16)Byte16(RecvBuf[14], RecvBuf[15]);
      RF_RecvData.Thr.CH4     = (u16)Byte16(RecvBuf[16], RecvBuf[17]);
      RF_RecvData.Thr.CH5     = (u16)Byte16(RecvBuf[18], RecvBuf[19]);
      RF_RecvData.Thr.CH6     = (u16)Byte16(RecvBuf[20], RecvBuf[21]);
      RF_RecvData.Batery.Vol  = (u8)RecvBuf[22];
      RF_RecvData.Batery.Cur  = (u8)RecvBuf[23];
      RF_RecvData.Batery.Cap  = (u16)Byte16(RecvBuf[24], RecvBuf[25]);
      break;

    case 0x02:
      RF_RecvData.Acc.X       = (s16)Byte16(RecvBuf[4],  RecvBuf[5]);
      RF_RecvData.Acc.Y       = (s16)Byte16(RecvBuf[6],  RecvBuf[7]);
      RF_RecvData.Acc.Z       = (s16)Byte16(RecvBuf[8],  RecvBuf[9]);
      RF_RecvData.Gyr.X       = (s16)Byte16(RecvBuf[10], RecvBuf[11]);
      RF_RecvData.Gyr.Y       = (s16)Byte16(RecvBuf[12], RecvBuf[13]);
      RF_RecvData.Gyr.Z       = (s16)Byte16(RecvBuf[14], RecvBuf[15]);
      RF_RecvData.Mag.X       = (s16)Byte16(RecvBuf[16], RecvBuf[17]);
      RF_RecvData.Mag.Y       = (s16)Byte16(RecvBuf[18], RecvBuf[19]);
      RF_RecvData.Mag.Z       = (s16)Byte16(RecvBuf[20], RecvBuf[21]);
      RF_RecvData.Baro.Temp   = (u16)Byte16(RecvBuf[22], RecvBuf[23]);
      RF_RecvData.Baro.Press  = (u32)Byte32(0, RecvBuf[24], RecvBuf[25], RecvBuf[26]);
      RF_RecvData.Baro.Height = (u32)Byte32(0, RecvBuf[27], RecvBuf[28], RecvBuf[29]);
      break;

    case 0x03:
      RF_RecvData.Ang.X       = (s16)Byte16(RecvBuf[4],  RecvBuf[5]);
      RF_RecvData.Ang.Y       = (s16)Byte16(RecvBuf[6],  RecvBuf[7]);
      RF_RecvData.Ang.Z       = (s16)Byte16(RecvBuf[8],  RecvBuf[9]);
      RF_RecvData.Vel.X       = (s16)Byte16(RecvBuf[10], RecvBuf[11]);
      RF_RecvData.Vel.Y       = (s16)Byte16(RecvBuf[12], RecvBuf[13]);
      RF_RecvData.Vel.Z       = (s16)Byte16(RecvBuf[14], RecvBuf[15]);
      RF_RecvData.Pos.X       = (s16)Byte16(RecvBuf[16], RecvBuf[17]);
      RF_RecvData.Pos.Y       = (s16)Byte16(RecvBuf[18], RecvBuf[19]);
      RF_RecvData.Pos.Z       = (s16)Byte16(RecvBuf[20], RecvBuf[21]);
      RF_RecvData.GPS.Lon     = (u32)Byte32(0, RecvBuf[22], RecvBuf[23], RecvBuf[24]);
      RF_RecvData.GPS.Lat     = (u32)Byte32(0, RecvBuf[25], RecvBuf[26], RecvBuf[27]);
      break;

    default:
      // ERROR
      break;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Transport_Send
**功能 : 紀錄發送資料
**輸入 : SendBuf
**輸出 : None
**使用 : Transport_Send(TxBuf);
**=====================================================================================================*/
/*=====================================================================================================*/
void Transport_Send( u8* SendBuf )
{
  SendBuf[0]  = 0;
  SendBuf[1]  = 0;
  SendBuf[2]  = 0;
  SendBuf[3]  = 0;
  SendBuf[4]  = 0;
  SendBuf[5]  = 0;
  SendBuf[6]  = 0;
  SendBuf[7]  = 0;
  SendBuf[8]  = 0;
  SendBuf[9]  = 0;
  SendBuf[10] = 0;
  SendBuf[11] = 0;
  SendBuf[12] = 0;
  SendBuf[13] = 0;
  SendBuf[14] = 0;
  SendBuf[15] = 0;
  SendBuf[16] = 0;
  SendBuf[17] = 0;
  SendBuf[18] = 0;
  SendBuf[19] = 0;
  SendBuf[20] = 0;
  SendBuf[21] = 0;
  SendBuf[22] = 0;
  SendBuf[23] = 0;
  SendBuf[24] = 0;
  SendBuf[25] = 0;
  SendBuf[26] = 0;
  SendBuf[27] = 0;
  SendBuf[28] = 0;
  SendBuf[29] = 0;
  SendBuf[30] = 0;
  SendBuf[31] = 0;
}
//  KEYR_J    = (u16)RecvBuf[0];
//  KEYR_U    = (u16)RecvBuf[1];
//  KEYR_D    = (u16)RecvBuf[2];
//  KEYR_L    = (u16)RecvBuf[3];
//  KEYR_R    = (u16)RecvBuf[4];
//  KEYR_S1   = (u16)RecvBuf[5];
//  KEYR_S2   = (u16)RecvBuf[6];
//  KEYL_J    = (u16)RecvBuf[7];
//  KEYL_U    = (u16)RecvBuf[8];
//  KEYL_D    = (u16)RecvBuf[9];
//  KEYL_L    = (u16)RecvBuf[10];
//  KEYL_R    = (u16)RecvBuf[11];
//  KEYL_S1   = (u16)RecvBuf[12];
//  KEYL_S2   = (u16)RecvBuf[13];
//  Exp_Pitch = (u16)((RecvBuf[15] << 8) | RecvBuf[14]);
//  Exp_Roll  = (u16)((RecvBuf[17] << 8) | RecvBuf[16]);
////   JSR_X     = (u16)((RecvBuf[15] << 8) | RecvBuf[14]);
////   JSR_Y     = (u16)((RecvBuf[17] << 8) | RecvBuf[16]);
//  JSR_Z     = (u16)((RecvBuf[19] << 8) | RecvBuf[18]);
//  Exp_Yaw   = (u16)((RecvBuf[21] << 8) | RecvBuf[20]);
//  Exp_Thr   = (u16)((RecvBuf[23] << 8) | RecvBuf[22]);
////   JSL_X     = (u16)((RecvBuf[21] << 8) | RecvBuf[20]);
////   JSL_Y     = (u16)((RecvBuf[23] << 8) | RecvBuf[22]);
//  JSL_Z     = (u16)((RecvBuf[25] << 8) | RecvBuf[24]);
////   Exp_Pitch = (u16)((RecvBuf[27] << 8) | RecvBuf[26]);
////   Exp_Roll  = (u16)((RecvBuf[29] << 8) | RecvBuf[28]);
////   Exp_Thr   = (u16)((RecvBuf[31] << 8) | RecvBuf[30]);
//  RecvTime_Sec = (u8)(RecvBuf[30]);
//  RecvTime_Min = (u8)(RecvBuf[31]);
/*=====================================================================================================*/
/*=====================================================================================================*/
