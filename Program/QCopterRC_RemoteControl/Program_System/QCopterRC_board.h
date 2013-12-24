/* #include "QCopterRC_board.h" */

#ifndef __QCOPTER_BOARD_H
#define __QCOPTER_BOARD_H

#include "stm32f4xx.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
/* LED Define */
#define LED_R   PCO(15)
#define LED_G   PCO(14)
#define LED_B   PCO(13)
#define LED_Y   PEO(6)

/* KEY Define */
#define KEY_RP  PAI(1)
#define KEY_RR  PBI(2)
#define KEY_RL  PAI(0)

#define KEY_LP  PAI(8)
#define KEY_LR  PDI(6)
#define KEY_LL  PDI(3)

#define KEY_PP  PEI(1)
#define KEY_PR  PEI(0)
#define KEY_PL  PEI(2)

#define KEY_S1  PEI(3)
#define KEY_S2  PEI(4)
#define KEY_S3  PEI(5)

/* Joystick ADC Value */
#define Joystick_X_Max  7670
#define Joystick_X_Med  3640
#define Joystick_X_Min  60
#define Joystick_Y_Max  7670
#define Joystick_Y_Med  3670
#define Joystick_Y_Min  100
#define Joystick_Z_Max  0
#define Joystick_Z_Med  0
#define Joystick_Z_Min  0
/*====================================================================================================*/
/*====================================================================================================*/
void LED_Config( void );
void KEY_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
