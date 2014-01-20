/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "system_waveForm.h"
#include "module_nrf24l01.h"
#include "module_r61581.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
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

#define LED_R   PCO(15)
#define LED_G   PCO(14)
#define LED_B   PCO(13)
#define LED_Y   PEO(6)
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
#define FSM_Tx    0
#define FSM_Rx    1
#define FSM_WAVE  2

#define WaveFromNum_X 420
#define WaveFromNum_Y 10

WaveForm_Struct WaveForm;
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  u16 i = 0;
  u8 Sta = ERROR;
  u8 FSM_Sta = FSM_Tx;

	SystemInit();
	GPIO_Config();
  nRF24L01_Config();
  R61581_Config();
  R61581_Init();

  while(Sta != SUCCESS)
    Sta = nRF_Check();

	WaveForm.Channel = 3;
	WaveForm.WindowColor = WHITE;
	WaveForm.BackColor = BLACK;
	WaveForm.Data[0] = 0;
	WaveForm.Data[1] = 0;
	WaveForm.Data[2] = 0;
	WaveForm.Scale[0] = 100;
	WaveForm.Scale[1] = 100;
	WaveForm.Scale[2] = 100;
	WaveForm.PointColor[0] = RED;
	WaveForm.PointColor[1] = GREEN;
	WaveForm.PointColor[2] = BLUE;

  LCD_Clear(BLACK);

  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*0,  (u8*)"------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2,  (u8*)"  RF  ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*4,  (u8*)" WAVE ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*6,  (u8*)"------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*9,  (u8*)"Axis-X", ASCII1608, RED,   BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*14, (u8*)"Axis-Y", ASCII1608, GREEN, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*19, (u8*)"Axis-Z", ASCII1608, BLUE,  BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*24, (u8*)"------", ASCII1608, WHITE, BLACK);

  TxBuf[0][0] = i;

  while(1) {
    LED_R = !LED_R;
    switch(FSM_Sta) {

/************************** FSM Tx **************************************/
      case FSM_Tx:
        // FSM_Tx
        nRF_TX_Mode();
        nRF_Tx_Data(TxBuf[0]);
        // FSM_Tx End
        FSM_Sta = FSM_Rx;
        break;

/************************** FSM Rx **************************************/
      case FSM_Rx:
        // FSM_Rx
        LED_B = !LED_B;
        nRF_RX_Mode();
        // FSM_Rx End
        FSM_Sta = FSM_WAVE;
        break;

/************************** FSM WAVE ************************************/
      case FSM_WAVE:

        WaveForm.Data[0] = (s16)Byte16(RxBuf[0][21], RxBuf[0][20]);
        WaveForm.Data[1] = (s16)Byte16(RxBuf[0][23], RxBuf[0][22]);
        WaveForm.Data[2] = (s16)Byte16(RxBuf[0][25], RxBuf[0][24]);
        LCD_PutNum(WaveFromNum_X, WaveFromNum_Y+8*11, Type_I, 5, WaveForm.Data[0], RED,   BLACK);
        LCD_PutNum(WaveFromNum_X, WaveFromNum_Y+8*16, Type_I, 5, WaveForm.Data[1], GREEN, BLACK);
        LCD_PutNum(WaveFromNum_X, WaveFromNum_Y+8*21, Type_I, 5, WaveForm.Data[2], BLUE,  BLACK);

        WaveFormPrint(&WaveForm);

        FSM_Sta = FSM_Tx;
        break;
    }
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
