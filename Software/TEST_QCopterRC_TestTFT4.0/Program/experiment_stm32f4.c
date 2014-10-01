/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "module_otm8009.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define KEY_RP  PAI(8)
#define KEY_RR  PDI(6)
#define KEY_RL  PDI(3)

#define KEY_LP  PAI(1)
#define KEY_LR  PBI(2)
#define KEY_LL  PAI(0)

#define KEY_PP  PEI(1)
#define KEY_PR  PEI(0)
#define KEY_PL  PEI(2)

#define KEY_S1  PEI(3)
#define KEY_S2  PEI(4)
#define KEY_S3  PEI(5)

#define LED_R   PCO(15)
#define LED_G   PCO(14)
#define LED_B   PCO(13)
#define LED_Y   PEO(6)
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
	SystemInit();
	GPIO_Config();
  OTM8009_Config();
  OTM8009_Init();

  LCD_TestColoBar();

  while(1) {
    LED_R = !LED_R;
    LED_G = !LED_G;
    LED_B = !LED_B;
    LED_Y = !LED_Y;
    Delay_100ms(1);
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | 
                         RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

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

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
  LED_Y = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
