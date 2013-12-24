/* #include "QCopterRC_userInterface.h" */

#ifndef __QCOPTERRC_USERINTERFAC_H
#define __QCOPTERRC_USERINTERFAC_H

#include "stm32f4xx.h"
#include "QCopterRC_windows.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_Init( void );
void UserInterface_Update( WINDOWS_MENU MenuSel );
void UserInterface_MoveSel( WINDOWS_MENU MenuSel );

static void MenuCtrl_Motor_Init( void );
//static void MenuCtrl_Motor( void );
static void MenuCtrl_Connection_Init( void );
//static void MenuCtrl_Connection( void );
static void MenuCtrl_Mode_Init( void );
static void MenuCtrl_Mode( void );
static void MenuCtrl_WorkTime_Init( void );
//static void MenuCtrl_WorkTime( void );
static void MenuCtrl_Power_Init( void );
static void MenuCtrl_Power( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
