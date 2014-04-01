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
#define KEY_ON   (1)
#define KEY_OFF  (0)
#define KEY_LONG (2)

#define DEF_KEY_RP  PAI(1)
#define DEF_KEY_RR  PAI(0)
#define DEF_KEY_RL  PBI(2)
#define DEF_KEY_LP  PAI(8)
#define DEF_KEY_LR  PDI(6)
#define DEF_KEY_LL  PDI(3)
#define DEF_KEY_PP  PEI(1)
#define DEF_KEY_PR  PEI(0)
#define DEF_KEY_PL  PEI(2)
#define DEF_KEY_S1  PEI(3)
#define DEF_KEY_S2  PEI(4)
#define DEF_KEY_S3  PEI(5)

#define KEY_RP    (KeyBD.K_RP.KeyRead)
#define KEY_RR    (KeyBD.K_RR.KeyRead)
#define KEY_RL    (KeyBD.K_RL.KeyRead)
#define KEY_LP    (KeyBD.K_LP.KeyRead)
#define KEY_LR    (KeyBD.K_LR.KeyRead)
#define KEY_LL    (KeyBD.K_LL.KeyRead)
#define KEY_PP    (KeyBD.K_PP.KeyRead)
#define KEY_PR    (KeyBD.K_PR.KeyRead)
#define KEY_PL    (KeyBD.K_PL.KeyRead)
#define KEY_S1    (KeyBD.K_S1.KeyRead)
#define KEY_S2    (KeyBD.K_S2.KeyRead)
#define KEY_S3    (KeyBD.K_S3.KeyRead)

#define KEY_RP_T  (KeyBD.K_RP.PressTime)
#define KEY_RR_T  (KeyBD.K_RR.PressTime)
#define KEY_RL_T  (KeyBD.K_RL.PressTime)
#define KEY_LP_T  (KeyBD.K_LP.PressTime)
#define KEY_LR_T  (KeyBD.K_LR.PressTime)
#define KEY_LL_T  (KeyBD.K_LL.PressTime)
#define KEY_PP_T  (KeyBD.K_PP.PressTime)
#define KEY_PR_T  (KeyBD.K_PR.PressTime)
#define KEY_PL_T  (KeyBD.K_PL.PressTime)
#define KEY_S1_T  (KeyBD.K_S1.PressTime)
#define KEY_S2_T  (KeyBD.K_S2.PressTime)
#define KEY_S3_T  (KeyBD.K_S3.PressTime)

/* Joystick ADC Value */
#define JS_RX     (KeyBD.J_RX.ReadADC)
#define JS_RY     (KeyBD.J_RY.ReadADC)
#define JS_RZ     (KeyBD.J_RZ.ReadADC)
#define JS_LX     (KeyBD.J_LX.ReadADC)
#define JS_LY     (KeyBD.J_LY.ReadADC)
#define JS_LZ     (KeyBD.J_LZ.ReadADC)

#define JS_RX_MAX (KeyBD.J_RX.Max)
#define JS_RX_MED (KeyBD.J_RX.Med)
#define JS_RX_MIN (KeyBD.J_RX.Max)
#define JS_RY_MAX (KeyBD.J_RY.Max)
#define JS_RY_MED (KeyBD.J_RY.Med)
#define JS_RY_MIN (KeyBD.J_RY.Max)
#define JS_RZ_MAX (KeyBD.J_RZ.Max)
#define JS_RZ_MED (KeyBD.J_RZ.Med)
#define JS_RZ_MIN (KeyBD.J_RZ.Max)
#define JS_LX_MAX (KeyBD.J_LX.Max)
#define JS_LX_MED (KeyBD.J_LX.Med)
#define JS_LX_MIN (KeyBD.J_LX.Max)
#define JS_LY_MAX (KeyBD.J_LY.Max)
#define JS_LY_MED (KeyBD.J_LY.Med)
#define JS_LY_MIN (KeyBD.J_LY.Max)
#define JS_LZ_MAX (KeyBD.J_LZ.Max)
#define JS_LZ_MED (KeyBD.J_LZ.Med)
#define JS_LZ_MIN (KeyBD.J_LZ.Max)

typedef struct {
  u8 KeyRead;
  u8 PressTime;
} Button_TypeDef;
typedef struct {
  u16 ReadADC;
  u16 Max;
  u16 Med;
  u16 Min;
} Joystick_TypeDef;
typedef struct {
  Button_TypeDef K_RP;
  Button_TypeDef K_RR;
  Button_TypeDef K_RL;
  Button_TypeDef K_LP;
  Button_TypeDef K_LR;
  Button_TypeDef K_LL;
  Button_TypeDef K_PP;
  Button_TypeDef K_PR;
  Button_TypeDef K_PL;
  Button_TypeDef K_S1;
  Button_TypeDef K_S2;
  Button_TypeDef K_S3;
  Joystick_TypeDef J_RX;
  Joystick_TypeDef J_RY;
  Joystick_TypeDef J_RZ;
  Joystick_TypeDef J_LX;
  Joystick_TypeDef J_LY;
  Joystick_TypeDef J_LZ;
} KeyBoard_TypeDef;
/*====================================================================================================*/
/*====================================================================================================*/
void LED_Config( void );
void KEY_Config( void );
void KeyBoard_ReadKEY( void );
void KeyBoard_ReadADC( void );
/*====================================================================================================*/
/*====================================================================================================*/
extern KeyBoard_TypeDef KeyBD;
/*====================================================================================================*/
/*====================================================================================================*/
#endif
