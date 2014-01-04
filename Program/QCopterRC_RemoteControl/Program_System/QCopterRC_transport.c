/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "QCopterRC_board.h"
#include "QCopterRC_transport.h"
#include "module_nrf24l01.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
TR_RECV_DATA RF_RecvData;
TR_SEND_DATA RF_SendData;
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
  RF_RecvData.Packet          = (u8)(RecvBuf[0]);
  RF_RecvData.Time.Min        = (u8)(RecvBuf[1]);
  RF_RecvData.Time.Sec        = (u8)(RecvBuf[2]);
  RF_RecvData.Time.mSec       = (u8)(RecvBuf[3]);

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
  SendBuf[0]  = (u8)(RF_SendData.Packet);
  SendBuf[1]  = (u8)(RF_SendData.Time.Min);
  SendBuf[2]  = (u8)(RF_SendData.Time.Sec);
  SendBuf[3]  = (u8)(RF_SendData.Time.mSec);

  KeyBoard_ReadKEY();

  SendBuf[4]  = (u8)(KEY_RP);
  SendBuf[5]  = (u8)(KEY_RR);
  SendBuf[6]  = (u8)(KEY_RL);
  SendBuf[7]  = (u8)(KEY_LP);
  SendBuf[8]  = (u8)(KEY_LR);
  SendBuf[9]  = (u8)(KEY_LL);
  SendBuf[10] = (u8)(KEY_PP);
  SendBuf[11] = (u8)(KEY_PR);
  SendBuf[12] = (u8)(KEY_PL);
  SendBuf[13] = (u8)(KEY_S1);
  SendBuf[14] = (u8)(KEY_S2);
  SendBuf[15] = (u8)(KEY_S3);

  KeyBoard_ReadADC();

  RF_SendData.Ctrl.ThrB  = (s16)(JS_RZ*2.44140625f);
  RF_SendData.Ctrl.ThrS  = (s16)(JS_LY*2.44140625f-5000);
  RF_SendData.Ctrl.Pitch = (s16)(JS_RY);
  RF_SendData.Ctrl.Roll  = (s16)(JS_RX);
  RF_SendData.Ctrl.Yaw   = (s16)(JS_LX);
  RF_SendData.Ctrl.Corr  = (s16)(JS_LZ*0.244140625f);

  RF_SendData.Cmd     = (u8)(0);
  RF_SendData.Data[0] = (u8)(0);
  RF_SendData.Data[1] = (u8)(0);
  RF_SendData.Data[2] = (u8)(0);

  SendBuf[16] = (u8)(Byte8H((u16)RF_SendData.Ctrl.ThrB));
  SendBuf[17] = (u8)(Byte8L((u16)RF_SendData.Ctrl.ThrB));
  SendBuf[18] = (u8)(Byte8H((u16)RF_SendData.Ctrl.ThrS));
  SendBuf[19] = (u8)(Byte8L((u16)RF_SendData.Ctrl.ThrS));
  SendBuf[20] = (u8)(Byte8H((u16)RF_SendData.Ctrl.Pitch));
  SendBuf[21] = (u8)(Byte8L((u16)RF_SendData.Ctrl.Pitch));
  SendBuf[22] = (u8)(Byte8H((u16)RF_SendData.Ctrl.Roll));
  SendBuf[23] = (u8)(Byte8L((u16)RF_SendData.Ctrl.Roll));
  SendBuf[24] = (u8)(Byte8H((u16)RF_SendData.Ctrl.Yaw));
  SendBuf[25] = (u8)(Byte8L((u16)RF_SendData.Ctrl.Yaw));
  SendBuf[26] = (u8)(Byte8H((u16)RF_SendData.Ctrl.Corr));
  SendBuf[27] = (u8)(Byte8L((u16)RF_SendData.Ctrl.Corr));
  SendBuf[28] = (u8)(RF_SendData.Cmd);
  SendBuf[29] = (u8)(RF_SendData.Data[0]);
  SendBuf[30] = (u8)(RF_SendData.Data[1]);
  SendBuf[31] = (u8)(RF_SendData.Data[2]);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
