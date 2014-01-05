/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"
#include "QCopterRC_board.h"
#include "QCopterRC_transport.h"
#include "QCopterRC_windows.h"
#include "system_waveForm.h"
#include "module_r61581.h"
#include "algorithm_mathUnit.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
WaveForm_Struct WaveForm;
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_Init( void )
{
  WaveFormInit(&WaveForm);
  Windows_DrawMenu();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_MoveSel( WINDOWS_MENU MenuSel )
{
  switch(MenuSel) {
    case WINDOWS_CTRL:
      Windows_Clear(BLACK);
      Windows_SelMenu(Windows_SelMenu_1, WHITE, BLACK);
      MenuCtrl_Throttle_Init();
      MenuCtrl_Connection_Init();
      MenuCtrl_Mode_Init();
      MenuCtrl_WorkTime_Init();
      MenuCtrl_Power_Init();
      break;
    case WINDOWS_TRACK:
      Windows_Clear(BLACK);
      Windows_SelMenu(Windows_SelMenu_2, WHITE, BLACK);
      MenuTrack_Info_Init();
      break;
    case WINDOWS_WAVE:
      Windows_Clear(BLACK);
      Windows_SelMenu(Windows_SelMenu_3, WHITE, BLACK);
      MenuWave_WaveFrom_Init();
      break;
    case WINDOWS_GPS:
      Windows_Clear(BLUE);
      Windows_SelMenu(Windows_SelMenu_4, WHITE, BLACK);
      break;
    case WINDOWS_IMAGE:
      Windows_Clear(RED);
      Windows_SelMenu(Windows_SelMenu_5, WHITE, BLACK);
      break;
    case WINDOWS_TEST:
      Windows_Clear(BLACK);
      Windows_SelMenu(Windows_SelMenu_6, WHITE, BLACK);
      MenuTest_KeyBoard_Init();
      break;
    case WINDOWS_CONF:
      Windows_Clear(YELLOW);
      Windows_SelMenu(Windows_SelMenu_7, WHITE, BLACK);
      break;
    default:
    // ERROR
    break;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_Update( WINDOWS_MENU MenuSel )
{
  u16 tempReadADC = 0;

  static WAVEFORM_SEL WaveForm_Sel = WAVEFORM_TEST;

  switch(MenuSel) {

    /************************** FSM CTRL **************************************/
    case WINDOWS_CTRL:    // 主控介面
      MenuCtrl_Power();
      MenuCtrl_Throttle();
//      MenuCtrl_WorkTime();
      MenuCtrl_Connection();
      break;

    /************************** FSM TRACK *************************************/
    case WINDOWS_TRACK:   // 3D 追蹤
      MenuTrack_Info();
      break;

    /************************** FSM WAVE **************************************/
    case WINDOWS_WAVE:    // 示波器
      #define DeBounce 120
      if(KEY_S3 == KEY_ON) {
        WaveForm_Sel++;
        if(WaveForm_Sel == WAVEFORM_OUT_R)
          WaveForm_Sel = (WAVEFORM_SEL)(WAVEFORM_OUT_L+1);
        Delay_1ms(DeBounce);
      }
      if(KEY_S1 == KEY_ON) {
        WaveForm_Sel--;
        if(WaveForm_Sel == WAVEFORM_OUT_L)
          WaveForm_Sel = (WAVEFORM_SEL)(WAVEFORM_OUT_R-1);
        Delay_1ms(DeBounce);
      }
      if(KEY_RR == KEY_ON) {
        KeyBoard_ReadADC();
        tempReadADC = (u16)(JS_LZ>>4);
        if(tempReadADC>256)
          tempReadADC = 500;
        if(tempReadADC<1)
          tempReadADC = 1;
        WaveForm.Scale[0] = tempReadADC;
        WaveForm.Scale[1] = tempReadADC;
        WaveForm.Scale[2] = tempReadADC;
        WaveForm.Scale[3] = tempReadADC;
      }
      MenuWave_WaveFrom(WaveForm_Sel);
      break;

    /************************** FSM GPS ***************************************/
    case WINDOWS_GPS:     // GPS 定位

      break;

    /************************** FSM IMAGE *************************************/
    case WINDOWS_IMAGE:   // 影像

      break;

    /************************** FSM TEST **************************************/
    case WINDOWS_TEST:    // 保留
      MenuTest_KeyBoard();
      break;

    /************************** FSM CONF **************************************/
    case WINDOWS_CONF:    // 設定

      break;

    /************************** default ***************************************/
    default:
      // ERROR
      break;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 馬達 Motor */
// MAX_LW = {40,221}
//#define Motor_X0	434
#define Throttle_X0	435
#define Throttle_Y0	25
static void MenuCtrl_Throttle_Init( void )
{
	Windows_PutStr(Throttle_X0+16, Throttle_Y0+252, (u8*)".", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Throttle_X0+32, Throttle_Y0+252, (u8*)"%", ASCII1608, WHITE, BLACK);
}
static void MenuCtrl_Throttle( void )
{
  u8 i = 0;
	u16 TempThr = 0;
  u16 TempThr_H = 0, TempThr_L = 0;

  TempThr   = (u16)(RF_SendData.Ctrl.ThrB/10.0f);
	TempThr_H = (u16)(TempThr/10);
	TempThr_L = (u16)(TempThr%10);

Delay_1ms(10);

  if(TempThr < 1000 || TempThr >0) {
    Windows_PutNum(Throttle_X0,    Throttle_Y0+252, Type_D, 2, TempThr_H, ASCII1608, WHITE, BLACK);
    Windows_PutNum(Throttle_X0+24, Throttle_Y0+252, Type_D, 1, TempThr_L, ASCII1608, WHITE, BLACK);
  }
	else if(TempThr >= 1000)
    Windows_PutStr(Throttle_X0, Throttle_Y0+252, (u8*)"99.9%", ASCII1608, WHITE, BLACK);
	else
    Windows_PutStr(Throttle_X0, Throttle_Y0+252, (u8*)"00.0%", ASCII1608, WHITE, BLACK);

  TempThr_H = (u16)(RF_RecvData.Thr.CH1/200);
	for(i=0; i<50; i++) {
		if((i%5)==0) {
			if(i<=TempThr_H && i>40)
				Windows_DrawRectangleFill(Throttle_X0, Throttle_Y0+247-i*5, 32, 3, RED);
			else if(i<=(TempThr_H))
				Windows_DrawRectangleFill(Throttle_X0, Throttle_Y0+247-i*5, 32, 3, GREEN);
			else
				Windows_DrawRectangleFill(Throttle_X0, Throttle_Y0+247-i*5, 32, 3, 0x9000);
		}
		else {
			if(i<=TempThr_H && i>40)
				Windows_DrawRectangleFill(Throttle_X0+12, Throttle_Y0+247-i*5, 20, 3, RED);
			else if(i<=(TempThr_H))
				Windows_DrawRectangleFill(Throttle_X0+12, Throttle_Y0+247-i*5, 20, 3, GREEN);
			else
				Windows_DrawRectangleFill(Throttle_X0+12, Throttle_Y0+247-i*5, 20, 3, 0x9000);
		}
	}

	for(i=0; i<50; i++) {
		if(i<=(TempThr/20))
			Windows_DrawRectangleFill(Throttle_X0+35, Throttle_Y0+247-i*5, 3, 3, RED);
		else
			Windows_DrawRectangleFill(Throttle_X0+35, Throttle_Y0+247-i*5, 3, 3, 0x9000);
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 連線狀況 Connection */
// MAX_LW = {21,15}
#define Connect_X0	10
#define Connect_Y0	7
static void MenuCtrl_Connection_Init( void )
{
	Windows_DrawRectangleFill(Connect_X0,    Connect_Y0+10, 5, 5,  WHITE);
	Windows_DrawRectangleFill(Connect_X0+8,  Connect_Y0+5,  5, 10, WHITE);
	Windows_DrawRectangleFill(Connect_X0+16, Connect_Y0,    5, 15, WHITE);
}
static void MenuCtrl_Connection( void )
{
//  /* Check Connection */
//  #define NoSignal 4  // 1 sec
//  if(((Time_Sec-RecvTime_Sec)>NoSignal) || ((Time_Sec-RecvTime_Sec)<-NoSignal)) {
//    Windows_DrawRectangleFill(Connect_X0,    Connect_Y0+10, 5, 5,  WHITE);
//    Windows_DrawRectangleFill(Connect_X0+8,  Connect_Y0+5,  5, 10, WHITE);
//    Windows_DrawRectangleFill(Connect_X0+16, Connect_Y0,    5, 15, WHITE);
//  }
//  else {
//    Windows_DrawRectangleFill(Connect_X0,    Connect_Y0+10, 5, 5,  GREEN);
//    Windows_DrawRectangleFill(Connect_X0+8,  Connect_Y0+5,  5, 10, GREEN);
//    Windows_DrawRectangleFill(Connect_X0+16, Connect_Y0,    5, 15, GREEN);
//  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 模式 Mode */
// MAX_LW = {104,20}
#define Mode_X0	46
#define Mode_Y0	2
static void MenuCtrl_Mode_Init( void )
{
	Windows_DrawRectangle(Mode_X0,     Mode_Y0,   20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+1,   Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+28,  Mode_Y0,   20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+29,  Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+56,  Mode_Y0,   20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+57,  Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+84,  Mode_Y0,   20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+85,  Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+112, Mode_Y0,   20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+113, Mode_Y0+1, 18, 18, WHITE);
	Windows_PutStr(Mode_X0+6,   Mode_Y0+2, (u8*)"F", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+34,  Mode_Y0+2, (u8*)"A", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+62,  Mode_Y0+2, (u8*)"G", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+90,  Mode_Y0+2, (u8*)"C", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+118, Mode_Y0+2, (u8*)"L", ASCII1608, WHITE, BLACK);
}
//static void MenuCtrl_Mode( void )
//{
//  
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 運行時間 WorkTime */
// MAX_LW = {40,16}
#define Time_X0	195
#define Time_Y0	4
static void MenuCtrl_WorkTime_Init( void )
{
	Windows_PutStr(Time_X0+16, Time_Y0, (u8*)":", ASCII1608, WHITE, BLACK);
}
//static void MenuCtrl_WorkTime( void )
//{
//  Windows_PutNum(Time_X0,    Time_Y0, Type_D, 2, Time_Min, WHITE, BLACK);
//  Windows_PutNum(Time_X0+24, Time_Y0, Type_D, 2, Time_Sec, WHITE, BLACK);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 電池電量 BatteryPower */
#define Power_X0	439
#define Power_Y0	2
static void MenuCtrl_Power_Init( void )
{
	Windows_DrawRectangleFill(Power_X0+3, Power_Y0,   31, 20, WHITE);
	Windows_DrawRectangleFill(Power_X0,   Power_Y0+6,  3,  8, WHITE);
	Windows_DrawRectangleFill(Power_X0+7, Power_Y0+3, 23, 14, BLACK);
}
static void MenuCtrl_Power( void )
{
	Windows_DrawRectangleFill(Power_X0+9,  Power_Y0+5, 5, 10, GREEN);
	Windows_DrawRectangleFill(Power_X0+16, Power_Y0+5, 5, 10, GREEN);
	Windows_DrawRectangleFill(Power_X0+23, Power_Y0+5, 5, 10, GREEN);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
#define Info_X	15
#define Info_Y	25
static void MenuTrack_Info_Init( void )
{
  Windows_PutStr(Info_X+8*0,  Info_Y+16*0,  (u8*)"Packet  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*1,  (u8*)"T.Min   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*2,  (u8*)"T.Sec   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*3,  (u8*)"T.mSec  : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*0,  Info_Y+16*5,  (u8*)"PID.KP  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*6,  (u8*)"PID.KI  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*7,  (u8*)"PID.KD  : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*0,  Info_Y+16*9,  (u8*)"Thr.CH1 : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*10, (u8*)"Thr.CH2 : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*11, (u8*)"Thr.CH3 : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*12, (u8*)"Thr.CH4 : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*13, (u8*)"Thr.CH5 : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*0,  Info_Y+16*14, (u8*)"Thr.CH6 : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*18, Info_Y+16*0,  (u8*)"Bat.Vol : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*1,  (u8*)"Bat.Cur : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*2,  (u8*)"Bat.Cap : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*18, Info_Y+16*4,  (u8*)"Acc.X   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*5,  (u8*)"Acc.Y   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*6,  (u8*)"Acc.Z   : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*18, Info_Y+16*8,  (u8*)"Gyr.X   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*9,  (u8*)"Gyr.Y   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*10, (u8*)"Gyr.Z   : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*18, Info_Y+16*12, (u8*)"Mag.X   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*13, (u8*)"Mag.Y   : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*18, Info_Y+16*14, (u8*)"Mag.Z   : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*36, Info_Y+16*0,  (u8*)"Ang.X  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*1,  (u8*)"Ang.Y  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*2,  (u8*)"Ang.Z  : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*36, Info_Y+16*4,  (u8*)"Vel.X  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*5,  (u8*)"Vel.Y  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*6,  (u8*)"Vel.Z  : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*36, Info_Y+16*8,  (u8*)"Pos.X  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*9,  (u8*)"Pos.Y  : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*10, (u8*)"Pos.Z  : ", ASCII1608, WHITE, BLACK);

  Windows_PutStr(Info_X+8*36, Info_Y+16*12, (u8*)"Baro.T : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*13, (u8*)"Baro.P : ", ASCII1608, WHITE, BLACK);
  Windows_PutStr(Info_X+8*36, Info_Y+16*14, (u8*)"Baro.H : ", ASCII1608, WHITE, BLACK);
}
static void MenuTrack_Info( void )
{
  Windows_PutNum(Info_X+8*10, Info_Y+16*0,  Type_I, 5, RF_RecvData.Packet,      ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*1,  Type_I, 5, RF_RecvData.Time.Min,    ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*2,  Type_I, 5, RF_RecvData.Time.Sec,    ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*3,  Type_I, 5, RF_RecvData.Time.mSec,   ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*10, Info_Y+16*5,  Type_I, 5, RF_RecvData.PID.KP,      ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*6,  Type_I, 5, RF_RecvData.PID.KI,      ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*7,  Type_I, 5, RF_RecvData.PID.KD,      ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*10, Info_Y+16*9,  Type_I, 5, RF_RecvData.Thr.CH1,     ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*10, Type_I, 5, RF_RecvData.Thr.CH2,     ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*11, Type_I, 5, RF_RecvData.Thr.CH3,     ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*12, Type_I, 5, RF_RecvData.Thr.CH4,     ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*13, Type_I, 5, RF_RecvData.Thr.CH5,     ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*10, Info_Y+16*14, Type_I, 5, RF_RecvData.Thr.CH6,     ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*28, Info_Y+16*0,  Type_I, 5, RF_RecvData.Batery.Vol,  ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*1,  Type_I, 5, RF_RecvData.Batery.Cur,  ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*2,  Type_I, 5, RF_RecvData.Batery.Cap,  ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*28, Info_Y+16*4,  Type_I, 5, RF_RecvData.Acc.X,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*5,  Type_I, 5, RF_RecvData.Acc.Y,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*6,  Type_I, 5, RF_RecvData.Acc.Z,       ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*28, Info_Y+16*8,  Type_I, 5, RF_RecvData.Gyr.X,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*9,  Type_I, 5, RF_RecvData.Gyr.Y,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*10, Type_I, 5, RF_RecvData.Gyr.Z,       ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*28, Info_Y+16*12, Type_I, 5, RF_RecvData.Mag.X,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*13, Type_I, 5, RF_RecvData.Mag.Y,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*28, Info_Y+16*14, Type_I, 5, RF_RecvData.Mag.Z,       ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*45, Info_Y+16*0,  Type_I, 5, RF_RecvData.Ang.X,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*1,  Type_I, 5, RF_RecvData.Ang.Y,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*2,  Type_I, 5, RF_RecvData.Ang.Z,       ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*45, Info_Y+16*4,  Type_I, 5, RF_RecvData.Vel.X,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*5,  Type_I, 5, RF_RecvData.Vel.Y,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*6,  Type_I, 5, RF_RecvData.Vel.Z,       ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*45, Info_Y+16*8,  Type_I, 5, RF_RecvData.Pos.X,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*9,  Type_I, 5, RF_RecvData.Pos.Y,       ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*10, Type_I, 5, RF_RecvData.Pos.Z,       ASCII1608, WHITE, BLACK);

  Windows_PutNum(Info_X+8*45, Info_Y+16*12, Type_I, 5, RF_RecvData.Baro.Temp,   ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*13, Type_I, 9, RF_RecvData.Baro.Press,  ASCII1608, WHITE, BLACK);
  Windows_PutNum(Info_X+8*45, Info_Y+16*14, Type_I, 9, RF_RecvData.Baro.Height, ASCII1608, WHITE, BLACK);

//RF_RecvData.GPS.Lon     = (u32)Byte32(0, RecvBuf[22], RecvBuf[23], RecvBuf[24]);
//RF_RecvData.GPS.Lat     = (u32)Byte32(0, RecvBuf[25], RecvBuf[26], RecvBuf[27]);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 示波器 WaveForm */
#define WaveFromNum_X 409
#define WaveFromNum_Y 10
static void MenuWave_WaveFrom_Init( void )
{
  Windows_PutStr(WaveFromNum_X+4,  WaveFromNum_Y,      (u8*)"<     >", ASCII1608, WHITE,  BLACK);
  Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y+8*4,  (u8*)" CH1 ",   ASCII1608, RED,    BLACK);
  Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y+8*9,  (u8*)" CH2 ",   ASCII1608, GREEN,  BLACK);
  Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y+8*14, (u8*)" CH3 ",   ASCII1608, BLUE,   BLACK);
  Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y+8*19, (u8*)" CH4 ",   ASCII1608, YELLOW, BLACK);
  Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y+8*27, (u8*)"Scale",   ASCII1608, WHITE,  BLACK);
}
static void MenuWave_WaveFrom( WAVEFORM_SEL WaveForm_Sel )
{
  static s32 Sita = 0;

  switch(WaveForm_Sel) {
    case WAVEFORM_ACC:
      WaveForm.Data[0] = RF_RecvData.Acc.X;
      WaveForm.Data[1] = RF_RecvData.Acc.Y;
      WaveForm.Data[2] = RF_RecvData.Acc.Z;
      WaveForm.Data[3] = 0;
      Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y, (u8*)" ACC ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_GYR:
      WaveForm.Data[0] = RF_RecvData.Gyr.X;
      WaveForm.Data[1] = RF_RecvData.Gyr.Y;
      WaveForm.Data[2] = RF_RecvData.Gyr.Z;
      WaveForm.Data[3] = 0;
      Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y, (u8*)" GYR ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_MAG:
      WaveForm.Data[0] = RF_RecvData.Mag.X;
      WaveForm.Data[1] = RF_RecvData.Mag.Y;
      WaveForm.Data[2] = RF_RecvData.Mag.Z;
      WaveForm.Data[3] = 0;
      Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y, (u8*)" MAG ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_ANG:
      WaveForm.Data[0] = RF_RecvData.Ang.X;
      WaveForm.Data[1] = RF_RecvData.Ang.Y;
      WaveForm.Data[2] = RF_RecvData.Ang.Z;
      WaveForm.Data[3] = 0;
      Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y, (u8*)" ANG ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_THR:
      WaveForm.Data[0] = RF_RecvData.Thr.CH1;
      WaveForm.Data[1] = RF_RecvData.Thr.CH2;
      WaveForm.Data[2] = RF_RecvData.Thr.CH3;
      WaveForm.Data[3] = RF_RecvData.Thr.CH4;
      Windows_PutStr(WaveFromNum_X+12, WaveFromNum_Y, (u8*)" THR ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_TEST:
      Sita++;
      if(Sita == 360) Sita = 0;
      WaveForm.Data[0] = sinf(toRad(Sita))*10000;
      WaveForm.Data[1] = sinf(toRad(Sita-90))*7500;
      WaveForm.Data[2] = sinf(toRad(Sita-180))*5000;
      WaveForm.Data[3] = sinf(toRad(Sita-270))*2500;
      Windows_PutStr(WaveFromNum_X+16, WaveFromNum_Y, (u8*)"TEST", ASCII1608, WHITE, BLACK);
      break;
    default:

      break;
  }
  Windows_PutNum(WaveFromNum_X+8,  WaveFromNum_Y+8*6,  Type_I, 5, WaveForm.Data[0],  ASCII1608, RED,    BLACK);
  Windows_PutNum(WaveFromNum_X+8,  WaveFromNum_Y+8*11, Type_I, 5, WaveForm.Data[1],  ASCII1608, GREEN,  BLACK);
  Windows_PutNum(WaveFromNum_X+8,  WaveFromNum_Y+8*16, Type_I, 5, WaveForm.Data[2],  ASCII1608, BLUE,   BLACK);
  Windows_PutNum(WaveFromNum_X+8,  WaveFromNum_Y+8*21, Type_I, 5, WaveForm.Data[3],  ASCII1608, YELLOW, BLACK);
  Windows_PutNum(WaveFromNum_X+12, WaveFromNum_Y+8*29, Type_D, 5, WaveForm.Scale[0], ASCII1608, WHITE,  BLACK);

  WaveFormPrint(&WaveForm);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 鍵盤測試 Test KeyBoard*/
void MoveCirR( u16 CoordiX, u16 CoordiY, u16 Radius, u16 LineColor, u16 BackColor )
{
  static u32 clearColor = 0;
  static u16 tmpRadius = 0;
  static u16 tmpCoordiX = 0, tmpCoordiY = 0;

  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);
  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);

  tmpRadius = Radius;
  clearColor = BackColor;
  tmpCoordiX = CoordiX;
  tmpCoordiY = CoordiY;

  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
}
void MoveCirL( u16 CoordiX, u16 CoordiY, u16 Radius, u16 LineColor, u16 BackColor )
{
  static u32 clearColor = 0;
  static u16 tmpRadius = 0;
  static u16 tmpCoordiX = 0, tmpCoordiY = 0;

  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);
  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);

  tmpRadius = Radius;
  clearColor = BackColor;
  tmpCoordiX = CoordiX;
  tmpCoordiY = CoordiY;

  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
}
static void MenuTest_KeyBoard_Init( void )
{
  #define Axis_CIR_X 118
  #define Axis_CIR_Y 220
  LCD_DrawCircle(Axis_CIR_X,     Axis_CIR_Y-100, 102, WHITE);
  LCD_DrawCircle(Axis_CIR_X,     Axis_CIR_Y-100, 101, WHITE);
  LCD_DrawCircle(Axis_CIR_X+240, Axis_CIR_Y-100, 102, WHITE);
  LCD_DrawCircle(Axis_CIR_X+240, Axis_CIR_Y-100, 101, WHITE);

  #define Axis_KEY_X 20
  #define Axis_KEY_Y 240
  LCD_PutStr(Axis_KEY_X+8*35, Axis_KEY_Y+16*0, (u8*)"LX:", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_KEY_X+8*35, Axis_KEY_Y+16*1, (u8*)"LY:", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_KEY_X+8*35, Axis_KEY_Y+16*2, (u8*)"LZ:", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_KEY_X+8*47, Axis_KEY_Y+16*0, (u8*)"RX:", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_KEY_X+8*47, Axis_KEY_Y+16*1, (u8*)"RY:", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_KEY_X+8*47, Axis_KEY_Y+16*2, (u8*)"RZ:", ASCII1608, WHITE, BLACK);
}
static void MenuTest_KeyBoard( void )
{
  KeyBoard_ReadADC();

  if(KEY_LP == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*0, (u8*)"KEY_LP", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*0, (u8*)"KEY_LP", ASCII1608, WHITE, BLACK);
  if(KEY_LR == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*1, (u8*)"KEY_LR", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*1, (u8*)"KEY_LR", ASCII1608, WHITE, BLACK);
  if(KEY_LL == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*2, (u8*)"KEY_LL", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*2, (u8*)"KEY_LL", ASCII1608, WHITE, BLACK);

  if(KEY_PP == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*0, (u8*)"KEY_PP", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*0, (u8*)"KEY_PP", ASCII1608, WHITE, BLACK);
  if(KEY_PR == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*1, (u8*)"KEY_PR", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*1, (u8*)"KEY_PR", ASCII1608, WHITE, BLACK);
  if(KEY_PL == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*2, (u8*)"KEY_PL", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*2, (u8*)"KEY_PL", ASCII1608, WHITE, BLACK);

  if(KEY_S1 == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*0, (u8*)"KEY_S1", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*0, (u8*)"KEY_S1", ASCII1608, WHITE, BLACK);
  if(KEY_S2 == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*1, (u8*)"KEY_S2", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*1, (u8*)"KEY_S2", ASCII1608, WHITE, BLACK);
  if(KEY_S3 == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*2, (u8*)"KEY_S3", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*2, (u8*)"KEY_S3", ASCII1608, WHITE, BLACK);

  if(KEY_RP == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*0, (u8*)"KEY_RP", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*0, (u8*)"KEY_RP", ASCII1608, WHITE, BLACK);
  if(KEY_RR == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*1, (u8*)"KEY_RR", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*1, (u8*)"KEY_RR", ASCII1608, WHITE, BLACK);
  if(KEY_RL == KEY_ON)  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*2, (u8*)"KEY_RL", ASCII1608, GREEN, BLACK);
  else                  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*2, (u8*)"KEY_RL", ASCII1608, WHITE, BLACK);

  LCD_PutNum(Axis_KEY_X+8*38, Axis_KEY_Y+16*0, Type_D, 5, JS_LX, ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_KEY_X+8*38, Axis_KEY_Y+16*1, Type_D, 5, JS_LY, ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_KEY_X+8*38, Axis_KEY_Y+16*2, Type_D, 5, JS_LZ, ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_KEY_X+8*50, Axis_KEY_Y+16*0, Type_D, 5, JS_RX, ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_KEY_X+8*50, Axis_KEY_Y+16*1, Type_D, 5, JS_RY, ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_KEY_X+8*50, Axis_KEY_Y+16*2, Type_D, 5, JS_RZ, ASCII1608, WHITE, BLACK);

  MoveCirL(Axis_CIR_X+(JS_LX*0.0244140625f-50),       (Axis_CIR_Y-100)+(50-JS_LY*0.0244140625f), 25, GREEN, BLACK);
  MoveCirR((Axis_CIR_X+240)+(JS_RX*0.0244140625f-50), (Axis_CIR_Y-100)+(50-JS_RY*0.0244140625f), 25, GREEN, BLACK);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
#define MenuButton_W 64
#define MenuButton_H 20
#define MenuButton_HelfW 32
#define MenuButton_HelfH 10
static void Windows_DrawMenuButton( u16 CoordiX, u16 CoordiY, u8* MenuStr, u32 Color )
{
  u8 strPosX = MenuButton_HelfW-(u8)((Str_LenOfStr(MenuStr)/2.0f)*8);
  u8 strPosY = MenuButton_HelfH-8;

  LCD_DrawRectangle(CoordiX,   CoordiY,   MenuButton_W,   MenuButton_H,   Color);
  LCD_DrawRectangle(CoordiX+1, CoordiY+1, MenuButton_W-2, MenuButton_H-2, Color);

  LCD_PutStr(CoordiX+strPosX, CoordiY+strPosY, MenuStr, ASCII1608, WHITE, BLACK);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
static void Windows_DrawFixPixel( u16 CoordiX, u16 CoordiY, u32 Color )
{
  LCD_DrawRectangleFill(CoordiX, CoordiY, 2, 2, Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
#define MenuButton_Pos 296  // Menu_H = 24
static void Windows_DrawMenu( void )
{
  LCD_DrawRectangle(Window_PosX-2, Window_PosY-2, Window_W+4, Window_H+4, WHITE);
  LCD_DrawRectangle(Window_PosX-1, Window_PosX-1, Window_W+2, Window_H+2, WHITE);

  Windows_DrawMenuButton(Windows_SelMenu_1, MenuButton_Pos+4, Windows_MenuName_1, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_2, MenuButton_Pos+4, Windows_MenuName_2, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_3, MenuButton_Pos+4, Windows_MenuName_3, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_4, MenuButton_Pos+4, Windows_MenuName_4, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_5, MenuButton_Pos+4, Windows_MenuName_5, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_6, MenuButton_Pos+4, Windows_MenuName_6, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_7, MenuButton_Pos+4, Windows_MenuName_7, WHITE);

  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos,   MenuButton_W-4, BLACK);
  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos+1, MenuButton_W-4, BLACK);
  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos+4, MenuButton_W-4, BLACK);
  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos+5, MenuButton_W-4, BLACK);

  Windows_DrawFixPixel(Windows_SelMenu_1,                MenuButton_Pos+2, WHITE);
  Windows_DrawFixPixel(Windows_SelMenu_1+MenuButton_W-2, MenuButton_Pos+2, WHITE);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
static void Windows_SelMenu( u16 CoordiX, u32 SColor, u32 BColor )
{
  static u16 SelMenu[2] = {0};
  static u16 Tmp_CoordiX = 4;

  SelMenu[0] = (CoordiX-4)/68;

  LCD_DrawRectangle(Window_PosX-2, Window_PosY-2, Window_W+4, Window_H+4, WHITE);
  LCD_DrawRectangle(Window_PosX-1, Window_PosX-1, Window_W+2, Window_H+2, WHITE);

  LCD_DrawLineX(Window_PosX+Tmp_CoordiX, MenuButton_Pos+4, MenuButton_W-4, SColor);
  LCD_DrawLineX(Window_PosX+Tmp_CoordiX, MenuButton_Pos+5, MenuButton_W-4, SColor);
  LCD_DrawLineX(Window_PosX+CoordiX,     MenuButton_Pos,   MenuButton_W-4, BColor);
  LCD_DrawLineX(Window_PosX+CoordiX,     MenuButton_Pos+1, MenuButton_W-4, BColor);
  LCD_DrawLineX(Window_PosX+CoordiX,     MenuButton_Pos+4, MenuButton_W-4, BColor);
  LCD_DrawLineX(Window_PosX+CoordiX,     MenuButton_Pos+5, MenuButton_W-4, BColor);

  Windows_DrawFixPixel(Tmp_CoordiX,                MenuButton_Pos+2, BColor);
  Windows_DrawFixPixel(Tmp_CoordiX+MenuButton_W-2, MenuButton_Pos+2, BColor);
  Windows_DrawFixPixel(CoordiX,                    MenuButton_Pos+2, SColor);
  Windows_DrawFixPixel(CoordiX+MenuButton_W-2,     MenuButton_Pos+2, SColor);

  Tmp_CoordiX = CoordiX;
  SelMenu[1] = SelMenu[0];
}
/*=====================================================================================================*/
/*=====================================================================================================*/
static void Windows_Clear( u32 Color )
{
  LCD_DrawRectangleFill(Window_PosX, Window_PosY, Window_W, Window_H, Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
//static void Windows_DrawPixel( u16 CoordiX, u16 CoordiY, u16 Color )
//{
//  LCD_DrawPixel(Window_PosX+CoordiX, Window_PosY+CoordiY, Color);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
//static void Windows_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
//{
//  LCD_DrawLineX(Window_PosX+CoordiX, Window_PosY+CoordiY, Length, Color);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
//static void Windows_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
//{
//  LCD_DrawLineY(Window_PosX+CoordiX, Window_PosY+CoordiY, Length, Color);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
static void Windows_DrawRectangle( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color )
{
  LCD_DrawRectangle(Window_PosX+CoordiX, Window_PosY+CoordiY, Width, Height, Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
static void Windows_DrawRectangleFill( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color )
{
  LCD_DrawRectangleFill(Window_PosX+CoordiX, Window_PosY+CoordiY, Width, Height, Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
//static void Windows_DrawCircle( u16 CoordiX, u16 CoordiY, u16 Radius, u16 Color )
//{
//  LCD_DrawCircle(Window_PosX+CoordiX, Window_PosY+CoordiY, Radius, Color);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
//static void Windows_DrawPicture( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, uc8 *Pic )
//{
//  LCD_DrawPicture(Window_PosX+CoordiX, Window_PosX+CoordiY, Width, Height, Pic);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
static void Windows_PutStr( u16 CoordiX, u16 CoordiY, u8 *ChWord, u8 FontStyle, u16 FontColor, u16 BackColor )
{
  LCD_PutStr(Window_PosX+CoordiX, Window_PosY+CoordiY, ChWord, FontStyle, FontColor, BackColor);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
static void Windows_PutNum( u16 CoordiX, u16 CoordiY, u8 Type, u8 Length, u32 NumData, u8 FontStyle, u16 FontColor, u16 BackColor )
{
  LCD_PutNum(Window_PosX+CoordiX, Window_PosY+CoordiY, Type, Length, NumData, FontStyle, FontColor, BackColor);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
