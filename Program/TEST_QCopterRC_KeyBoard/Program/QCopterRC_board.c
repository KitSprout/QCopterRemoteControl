/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"
#include "QCopterRC_board.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
KEYBOARD_ST KeyBD;
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LED_Config
**功能 : LED 配置
**輸入 : None
**輸出 : None
**使用 : LED_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
static void LED_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* LED Clk Init *************************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);

  /* LED_R PC13 */  /* LED_G PC14 */  /* LED_B PC15 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* LED_Y PE6 */ 
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
  LED_Y = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : KEY_Config
**功能 : KEY 配置
**輸入 : None
**輸出 : None
**使用 : KEY_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
static void KEY_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* KEY Clk Init *************************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
                         RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

  /* KEY_LL PA0 */  /* KEY_LP PA1 */  /* KEY_RP PA8 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* KEY_LR PB2 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* KEY_RL PD3 */  /* KEY_RR PD6 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* KEY_PR PE0 */  /* KEY_PP PE1 */  /* KEY_PL PE2 */
  /* KEY_S1 PE3 */  /* KEY_S2 PE4 */  /* KEY_S3 PE5 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
                             GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStruct);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : KeyBoard_Config
**功能 : 鍵盤配置
**輸入 : None
**輸出 : None
**使用 : KeyBoard_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void KeyBoard_Config( void )
{
  LED_Config();
  KEY_Config();
  ADC_Config();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : KeyBoard_Read
**功能 : 輸入按鍵讀取
**輸入 : None
**輸出 : None
**使用 : KeyBoard_Read();
**=====================================================================================================*/
/*=====================================================================================================*/
void KeyBoard_Read( void )
{
  u16 ADC_AveTr[6] = {0};

  KEY_RP = !DEF_KEY_RP;
  KEY_RR = !DEF_KEY_RR;
  KEY_RL = !DEF_KEY_RL;
  KEY_LP = !DEF_KEY_LP;
  KEY_LR = !DEF_KEY_LR;
  KEY_LL = !DEF_KEY_LL;
  KEY_PP = !DEF_KEY_PP;
  KEY_PR = !DEF_KEY_PR;
  KEY_PL = !DEF_KEY_PL;
  KEY_S1 =  DEF_KEY_S1;
  KEY_S2 =  DEF_KEY_S2;
  KEY_S3 =  DEF_KEY_S3;

  ADC_Average(ADC_AveTr);
  JS_RX = ADC_AveTr[0];
  JS_RY = ADC_AveTr[1];
  JS_RZ = ADC_AveTr[4];
  JS_LX = ADC_AveTr[2];
  JS_LY = ADC_AveTr[3];
  JS_LZ = ADC_AveTr[5];
}
/*=====================================================================================================*/
/*=====================================================================================================*/
