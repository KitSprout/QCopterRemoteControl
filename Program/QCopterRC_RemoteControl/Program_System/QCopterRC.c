/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"
#include "stm32f4_sdio.h"
#include "QCopterRC.h"
#include "QCopterRC_board.h"
#include "QCopterRC_transport.h"
#include "QCopterRC_windows.h"
#include "module_rs232.h"
#include "module_nrf24l01.h"
#include "module_r61581.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void System_Init( void )
{
  u8 Sta = ERROR;

	SystemInit();

  LED_Config();
  KEY_Config();
  ADC_Config();
  RS232_Config();
  nRF24L01_Config();
  R61581_Config();

  Delay_10ms(5);

  /* nRF Check */
  while(Sta != SUCCESS)
    Sta = nRF_Check();

  R61581_Init();

  UserInterface_Init();

//  #define Axis_X 60
//  #define Axis_Y 96
//  LCD_PutStr(Axis_X, Axis_Y+16*0, (u8*)" SD Init ... ", ASCII1608, WHITE, BLACK);
//  while(SD_Init() != SD_OK) {
//    LCD_PutStr(Axis_X+8*13, Axis_Y+16*0, (u8*)"Failed!!", ASCII1608, WHITE, BLACK);
//    while(1) {
//      LED_R = ~LED_R;
//      Delay_100ms(2);
//    }
//  }
//  LCD_PutStr(Axis_X+8*13, Axis_Y+16*0, (u8*)"OK!!", ASCII1608, WHITE, BLACK);

//  LCD_PutStr(Axis_X,      Axis_Y+16*2, (u8*)"---- SD Init Info -----", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*3, (u8*)" Capacity : ", ASCII1608, WHITE, BLACK);
//  LCD_PutNum(Axis_X+8*12, Axis_Y+16*3, Type_D, 5, SDCardInfo.CardCapacity>>20, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*17, Axis_Y+16*3, (u8*)" MB", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*4, (u8*)" CardBlockSize : ", ASCII1608, WHITE, BLACK);
//  LCD_PutNum(Axis_X+8*17, Axis_Y+16*4, Type_D, 5, SDCardInfo.CardBlockSize, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*22, Axis_Y+16*4, (u8*)" ", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*5, (u8*)" CardType : ", ASCII1608, WHITE, BLACK);
//  LCD_PutNum(Axis_X+8*12, Axis_Y+16*5, Type_D, 5, SDCardInfo.CardType, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*17, Axis_Y+16*5, (u8*)" ", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*6, (u8*)" RCA : ", ASCII1608, WHITE, BLACK);
//  LCD_PutNum(Axis_X+8*7,  Axis_Y+16*6, Type_D, 5, SDCardInfo.RCA, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*12, Axis_Y+16*6, (u8*)" ", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*7, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);

  Delay_10ms(5);

  UserInterface_MoveSel(WINDOWS_CTRL);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  static FSM_MODE FSM_State = FSM_TX;
  static WINDOWS_MENU WindowsMeun_Sel = WINDOWS_CTRL;

  /* QCopterRC Init */
  System_Init();

//  /* Systick Config */
//  if(SysTick_Config(SystemCoreClock/100)) {  // 100 Hz
//    while(1);
//  }

//  while(1) {
//    KeyBoard_Read();
//    LCD_PutNum(10, 10+16*0,  Type_D, 5, KEY_RP, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*1,  Type_D, 5, KEY_RR, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*2,  Type_D, 5, KEY_RL, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*3,  Type_D, 5, KEY_LP, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*4,  Type_D, 5, KEY_LR, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*5,  Type_D, 5, KEY_LL, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*6,  Type_D, 5, KEY_PP, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*7,  Type_D, 5, KEY_PR, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*8,  Type_D, 5, KEY_PL, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*9,  Type_D, 5, KEY_S1, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*10, Type_D, 5, KEY_S2, WHITE, BLACK);
//    LCD_PutNum(10, 10+16*11, Type_D, 5, KEY_S3, WHITE, BLACK);
//  }
  /* Final State Machine */
  while(1) {
    LED_G = !LED_G;

    switch(FSM_State) {

      /************************** FSM TX **************************************/
      case FSM_TX:
        // FSM_TX
        nRF_TX_Mode();
        nRF_Tx_Data(TxBuf);
        // FSM_TX End
        FSM_State = FSM_RX;
        break;

      /************************** FSM RX **************************************/
      case FSM_RX:
        // FSM_RX
        nRF_RX_Mode();
        // FSM_RX End
        FSM_State = FSM_CTRL;
        break;

      /************************** FSM CTRL ************************************/
      case FSM_CTRL:
        // FSM_CTRL
        
        // FSM_CTRL End
        FSM_State = FSM_TFT;
        break;

      /************************** FSM TFT *************************************/
      case FSM_TFT:
        // FSM_TFT
        #define DeBounce 120
        if(KEY_PR == 0) {
          WindowsMeun_Sel++;
          if(WindowsMeun_Sel == WINDOWS_OUT_R)
            WindowsMeun_Sel = (WINDOWS_MENU)(WINDOWS_OUT_L+1);
          UserInterface_MoveSel(WindowsMeun_Sel);
          Delay_1ms(DeBounce);
        }
        if(KEY_PL == 0) {
          WindowsMeun_Sel--;
          if(WindowsMeun_Sel == WINDOWS_OUT_L)
            WindowsMeun_Sel = (WINDOWS_MENU)(WINDOWS_OUT_R-1);
          UserInterface_MoveSel(WindowsMeun_Sel);
          Delay_1ms(DeBounce);
        }
        UserInterface_Update(WindowsMeun_Sel);
        // FSM_TFT End
        FSM_State = FSM_UART;
        break;

      /************************** FSM UART ************************************/
      case FSM_UART:
        // FSM_UART
        
        // FSM_UART End
        FSM_State = FSM_TX;
        break;
    }
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
