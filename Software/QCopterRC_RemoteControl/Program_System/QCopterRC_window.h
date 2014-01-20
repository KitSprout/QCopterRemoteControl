/* #include "QCopterRC_window.h" */

#ifndef __QCOPTERRC_WINDOW_H
#define __QCOPTERRC_WINDOW_H

#include "stm32f4xx.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define Window_PosX 2
#define Window_PosY 2
#define Window_W 476
#define Window_H 294

#define Window_SelMenu_1	4
#define Window_SelMenu_2	72
#define Window_SelMenu_3	140
#define Window_SelMenu_4	208
#define Window_SelMenu_5	276
#define Window_SelMenu_6	344
#define Window_SelMenu_7	412

#define Window_MenuName_1 ((u8*)"CTRL")
#define Window_MenuName_2 ((u8*)"TRACK")
#define Window_MenuName_3 ((u8*)"WAVE")
#define Window_MenuName_4 ((u8*)"GPS")
#define Window_MenuName_5 ((u8*)"IMAGE")
#define Window_MenuName_6 ((u8*)"TEST")
#define Window_MenuName_7 ((u8*)"CONF")
/*=====================================================================================================*/
/*=====================================================================================================*/
typedef __IO enum {
  WINDOW_OUT_L = 0,
  WINDOW_CTRL,
  WINDOW_TRACK,
  WINDOW_WAVE,
  WINDOW_GPS,
  WINDOW_IMAGE,
  WINDOW_TEST,
  WINDOW_CONF,
  WINDOW_OUT_R
} WINDOW_MENU;
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
typedef __IO enum {
  TEST_OUT_L = 0,
  TEST_KEYBOARD,
  TEST_TRANSINFO,
  TEST_THROTTLE,
  TEST_FONT,
  TEST_AHRS,
  TEST_COLOR,
  TEST_OUT_R
} TEST_SEL;
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_Init( void );
void UserInterface_Update( WINDOW_MENU MenuSel );
void UserInterface_MoveSel( WINDOW_MENU MenuSel );

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
static void MenuWave_WaveFrom_Init( void );
static void MenuWave_WaveFrom( WAVEFORM_SEL WaveForm_Sel );
static void MenuTest_KeyBoard_Init( void );
static void MenuTest_KeyBoard( void );
static void MenuTest_TransInfo_Init( void );
static void MenuTest_TransInfo( void );
static void MenuTest_AHRS_Init( void );
static void MenuTest_AHRS( void );
static void MenuTest_Color_Init( void );
static void MenuTest_Item_Init( TEST_SEL Test_Sel );
static void MenuTest_Item( TEST_SEL Test_Sel );

static void Window_DrawMenu( void );
static void Window_SelMenu( u16 CoordiX, u32 SColor, u32 BColor );
static void Window_DrawFixPixel( u16 CoordiX, u16 CoordiY, u32 Color );

static void Window_Clear( u32 Color );
static void Window_DrawPixel( u16 CoordiX, u16 CoordiY, u16 Color );
static void Window_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color );
static void Window_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color );
static void Window_DrawRectangle( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color );
static void Window_DrawRectangleFill( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color );
static void Window_DrawCircle( u16 CoordiX, u16 CoordiY, u16 Radius, u16 Color );
static void Window_DrawPicture( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, uc8 *Pic );
static void Window_PutStr( u16 CoordiX, u16 CoordiY, u8 *ChWord, u8 FontStyle, u16 FontColor, u16 BackColor );
static void Window_PutNum( u16 CoordiX, u16 CoordiY, u8 Type, u8 Length, u32 NumData, u8 FontStyle, u16 FontColor, u16 BackColor );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
