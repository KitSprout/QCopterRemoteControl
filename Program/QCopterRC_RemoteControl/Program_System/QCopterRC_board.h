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

//#define DEF_KEY_RP  PAI(1)
//#define DEF_KEY_RR  PBI(2)
//#define DEF_KEY_RL  PAI(0)
//#define DEF_KEY_LP  PAI(8)
//#define DEF_KEY_LR  PDI(6)
//#define DEF_KEY_LL  PDI(3)
//#define DEF_KEY_PP  PEI(1)
//#define DEF_KEY_PR  PEI(0)
//#define DEF_KEY_PL  PEI(2)
//#define DEF_KEY_S1  PEI(3)
//#define DEF_KEY_S2  PEI(4)
//#define DEF_KEY_S3  PEI(5)

/* Joystick ADC Value */
#define Joystick_RX  ADC_AveTr[0]
#define Joystick_RY  ADC_AveTr[1]
#define Joystick_RZ  ADC_AveTr[4]
#define Joystick_LX  ADC_AveTr[2]
#define Joystick_LY  ADC_AveTr[3]
#define Joystick_LZ  ADC_AveTr[5]

//#define PRESS_ON   (1)
//#define PRESS_OFF  (0)
//#define PRESS_LONG (2)

//#define KEY_RP    (KeyBD.K_RP.Read)
//#define KEY_RR    (KeyBD.K_RR.Read)
//#define KEY_RL    (KeyBD.K_RL.Read)
//#define KEY_LP    (KeyBD.K_LP.Read)
//#define KEY_LR    (KeyBD.K_LR.Read)
//#define KEY_LL    (KeyBD.K_LL.Read)
//#define KEY_PP    (KeyBD.K_PP.Read)
//#define KEY_PR    (KeyBD.K_PR.Read)
//#define KEY_PL    (KeyBD.K_PL.Read)
//#define KEY_S1    (KeyBD.K_S1.Read)
//#define KEY_S2    (KeyBD.K_S2.Read)
//#define KEY_S3    (KeyBD.K_S3.Read)

//#define KEY_RP_T  (KeyBD.K_RP.Time)
//#define KEY_RR_T  (KeyBD.K_RR.Time)
//#define KEY_RL_T  (KeyBD.K_RL.Time)
//#define KEY_LP_T  (KeyBD.K_LP.Time)
//#define KEY_LR_T  (KeyBD.K_LR.Time)
//#define KEY_LL_T  (KeyBD.K_LL.Time)
//#define KEY_PP_T  (KeyBD.K_PP.Time)
//#define KEY_PR_T  (KeyBD.K_PR.Time)
//#define KEY_PL_T  (KeyBD.K_PL.Time)
//#define KEY_S1_T  (KeyBD.K_S1.Time)
//#define KEY_S2_T  (KeyBD.K_S2.Time)
//#define KEY_S3_T  (KeyBD.K_S3.Time)

//#define JS_RX     ((u16)(KeyBD.J_RX.Read))
//#define JS_RY     ((u16)(KeyBD.J_RY.Read))
//#define JS_RZ     ((u16)(KeyBD.J_RZ.Read))
//#define JS_LX     ((u16)(KeyBD.J_LX.Read))
//#define JS_LY     ((u16)(KeyBD.J_LY.Read))
//#define JS_LZ     ((u16)(KeyBD.J_LZ.Read))

//#define JS_RX_MAX ((u16)(KeyBD.J_RX.Max))
//#define JS_RX_MED ((u16)(KeyBD.J_RX.Med))
//#define JS_RX_MIN ((u16)(KeyBD.J_RX.Max))
//#define JS_RY_MAX ((u16)(KeyBD.J_RY.Max))
//#define JS_RY_MED ((u16)(KeyBD.J_RY.Med))
//#define JS_RY_MIN ((u16)(KeyBD.J_RY.Max))
//#define JS_RZ_MAX ((u16)(KeyBD.J_RZ.Max))
//#define JS_RZ_MED ((u16)(KeyBD.J_RZ.Med))
//#define JS_RZ_MIN ((u16)(KeyBD.J_RZ.Max))
//#define JS_LX_MAX ((u16)(KeyBD.J_LX.Max))
//#define JS_LX_MED ((u16)(KeyBD.J_LX.Med))
//#define JS_LX_MIN ((u16)(KeyBD.J_LX.Max))
//#define JS_LY_MAX ((u16)(KeyBD.J_LY.Max))
//#define JS_LY_MED ((u16)(KeyBD.J_LY.Med))
//#define JS_LY_MIN ((u16)(KeyBD.J_LY.Max))
//#define JS_LZ_MAX ((u16)(KeyBD.J_LZ.Max))
//#define JS_LZ_MED ((u16)(KeyBD.J_LZ.Med))
//#define JS_LZ_MIN ((u16)(KeyBD.J_LZ.Max))

typedef struct {
  u8 Read;
  u8 Time;
} BUTTON_ST;
typedef struct {
  u16 Read;
  u16 Max;
  u16 Med;
  u16 Min;
} JOYSTICK_ST;
typedef struct {
  BUTTON_ST K_RP;
  BUTTON_ST K_RR;
  BUTTON_ST K_RL;
  BUTTON_ST K_LP;
  BUTTON_ST K_LR;
  BUTTON_ST K_LL;
  BUTTON_ST K_PP;
  BUTTON_ST K_PR;
  BUTTON_ST K_PL;
  BUTTON_ST K_S1;
  BUTTON_ST K_S2;
  BUTTON_ST K_S3;
  JOYSTICK_ST J_RX;
  JOYSTICK_ST J_RY;
  JOYSTICK_ST J_RZ;
  JOYSTICK_ST J_LX;
  JOYSTICK_ST J_LY;
  JOYSTICK_ST J_LZ;
} KEYBOARD_ST;
/*====================================================================================================*/
/*====================================================================================================*/
void LED_Config( void );
void KEY_Config( void );
void KeyBoard_Read( void );
/*====================================================================================================*/
/*====================================================================================================*/
extern KEYBOARD_ST KeyBD;
/*====================================================================================================*/
/*====================================================================================================*/
#endif
