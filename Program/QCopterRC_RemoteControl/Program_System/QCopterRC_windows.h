/* #include "QCopterRC_windows.h" */

#ifndef __QCOPTERRC_WINDOWS_H
#define __QCOPTERRC_WINDOWS_H

#include "stm32f4xx.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define Window_PosX 2
#define Window_PosY 2
#define Window_W 476
#define Window_H 294

#define Windows_SelMenu_1	4
#define Windows_SelMenu_2	72
#define Windows_SelMenu_3	140
#define Windows_SelMenu_4	208
#define Windows_SelMenu_5	276
#define Windows_SelMenu_6	344
#define Windows_SelMenu_7	412

#define Windows_MenuName_1 ((u8*)"CTRL")
#define Windows_MenuName_2 ((u8*)"TRACK")
#define Windows_MenuName_3 ((u8*)"WAVE")
#define Windows_MenuName_4 ((u8*)"GPS")
#define Windows_MenuName_5 ((u8*)"IMAGE")
#define Windows_MenuName_6 ((u8*)"TEST")
#define Windows_MenuName_7 ((u8*)"CONF")
/*=====================================================================================================*/
/*=====================================================================================================*/
typedef __IO enum {
  WINDOWS_OUT_L = 0,
  WINDOWS_CTRL,
  WINDOWS_TRACK,
  WINDOWS_WAVE,
  WINDOWS_GPS,
  WINDOWS_IMAGE,
  WINDOWS_TEST,
  WINDOWS_CONF,
  WINDOWS_OUT_R
} WINDOWS_MENU;
typedef __IO enum {
  WAVEFORM_OUT_L = 0,
  WAVEFORM_ACC,
  WAVEFORM_GYR,
  WAVEFORM_MAG,
  WAVEFORM_ANG,
  WAVEFORM_THR,
  WAVEFORM_TEST,
  WAVEFORM_OUT_R
} WAVEFORM_SEL;
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_Init( void );
void UserInterface_Update( WINDOWS_MENU MenuSel );
void UserInterface_MoveSel( WINDOWS_MENU MenuSel );

static void MenuCtrl_Throttle_Init( void );
static void MenuCtrl_Throttle( void );
static void MenuCtrl_Connection_Init( void );
static void MenuCtrl_Connection( void );
static void MenuCtrl_Mode_Init( void );
static void MenuCtrl_Mode( void );
static void MenuCtrl_WorkTime_Init( void );
static void MenuCtrl_WorkTime( void );
static void MenuCtrl_Power_Init( void );
static void MenuCtrl_Power( void );
static void MenuTrack_Info_Init( void );
static void MenuTrack_Info( void );
static void MenuWave_WaveFrom_Init( void );
static void MenuWave_WaveFrom( WAVEFORM_SEL WaveForm_Sel );
static void MenuTest_KeyBoard_Init( void );
static void MenuTest_KeyBoard( void );

static void Windows_DrawMenu( void );
static void Windows_SelMenu( u16 CoordiX, u32 SColor, u32 BColor );

static void Windows_Clear( u32 Color );
static void Windows_DrawPixel( u16 CoordiX, u16 CoordiY, u16 Color );
static void Windows_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color );
static void Windows_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color );
static void Windows_DrawRectangle( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color );
static void Windows_DrawRectangleFill( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color );
static void Windows_DrawCircle( u16 CoordiX, u16 CoordiY, u16 Radius, u16 Color );
static void Windows_DrawPicture( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, uc8 *Pic );
static void Windows_PutStr( u16 CoordiX, u16 CoordiY, u8 *ChWord, u8 FontStyle, u16 FontColor, u16 BackColor );
static void Windows_PutNum( u16 CoordiX, u16 CoordiY, u8 Type, u8 Length, u32 NumData, u8 FontStyle, u16 FontColor, u16 BackColor );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
