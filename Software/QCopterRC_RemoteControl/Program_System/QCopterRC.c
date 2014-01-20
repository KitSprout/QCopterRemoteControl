/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"
#include "stm32f4_sdio.h"
#include "QCopterRC.h"
#include "QCopterRC_board.h"
#include "QCopterRC_transport.h"
#include "QCopterRC_window.h"
#include "module_rs232.h"
#include "module_nrf24l01.h"
#include "module_r61581.h"
#include "algorithm_string.h"
#include "algorithm_bitmap.h"

//#include "ff.h"
//#include "diskio.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
FSM_MODE FSM_State = FSM_TX;
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

  /* nRF Check */
  while(Sta != SUCCESS)
    Sta = nRF_Check();

  R61581_Init();
  UserInterface_Init();

//  #define Axis_X 30
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
//  LCD_PutNum(Axis_X+8*12, Axis_Y+16*3, Type_D, 5, SDCardInfo.CardCapacity>>20, ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*17, Axis_Y+16*3, (u8*)" MB", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*4, (u8*)" CardBlockSize : ", ASCII1608, WHITE, BLACK);
//  LCD_PutNum(Axis_X+8*17, Axis_Y+16*4, Type_D, 5, SDCardInfo.CardBlockSize, ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*22, Axis_Y+16*4, (u8*)" ", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*5, (u8*)" CardType : ", ASCII1608, WHITE, BLACK);
//  LCD_PutNum(Axis_X+8*12, Axis_Y+16*5, Type_D, 5, SDCardInfo.CardType, ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*17, Axis_Y+16*5, (u8*)" ", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*6, (u8*)" RCA : ", ASCII1608, WHITE, BLACK);
//  LCD_PutNum(Axis_X+8*7,  Axis_Y+16*6, Type_D, 5, SDCardInfo.RCA, ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X+8*12, Axis_Y+16*6, (u8*)" ", ASCII1608, WHITE, BLACK);
//  LCD_PutStr(Axis_X,      Axis_Y+16*7, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);

  UserInterface_MoveSel(WINDOW_CTRL);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  static WINDOW_MENU WindowsMeun_Sel = WINDOW_CTRL;

  /* QCopterRC Init */
  System_Init();

  /* Systick Config */
  if(SysTick_Config(SystemCoreClock/100)) {  // 100 Hz
    while(1);
  }

  /* Final State Machine */
  while(1) {
    LED_G = !LED_G;

    switch(FSM_State) {

      /************************** FSM TX **************************************/
      case FSM_TX:
        // FSM_TX
        Transport_Send(TxBuf);
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
        if(KEY_PR == KEY_ON) {
          WindowsMeun_Sel++;
          if(WindowsMeun_Sel == WINDOW_OUT_R)
            WindowsMeun_Sel = (WINDOW_MENU)(WINDOW_OUT_L+1);
          UserInterface_MoveSel(WindowsMeun_Sel);
          Delay_1ms(DeBounce);
        }
        if(KEY_PL == KEY_ON) {
          WindowsMeun_Sel--;
          if(WindowsMeun_Sel == WINDOW_OUT_L)
            WindowsMeun_Sel = (WINDOW_MENU)(WINDOW_OUT_R-1);
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
