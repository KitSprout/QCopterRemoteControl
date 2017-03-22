/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    main.c
  * @author  KitSprout
  * @date    16-Mar-2017
  * @brief   
  * 
  */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "modules\serial.h"
#include "modules\nrf24l01.h"
#include "modules\ssd1351.h"
#include "stm32f4xx_bsp.h"

/** @addtogroup STM32_Program
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
#define __NRF24L01_TX_IRQ__
#define TX_LENS 10

/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
extern NRF_DataTypeDef nrf;

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  uint8_t txCount = 0;
  uint8_t rxCount = 0;

  HAL_Init();
  BSP_GPIO_Config();
  BSP_UART_SERIAL_Config(NULL);
  BSP_SPI_NRF24_Config();
  BSP_SPI_OLED_Config();

#ifdef	__NRF24L01_TX_IRQ__
  uint8_t status;
  char displayStr[] = "TX DEMO";
  OLED_PutStr(CENTER(FONT16, displayStr), LINE(FONT16, 1), &FONT16, displayStr, WHITE, BLACK);
//  NRF24_SetMode(NRF_Mode_TX);
  nrf.txBuff[0] = 'K';
  nrf.txBuff[1] = 'i';
  nrf.txBuff[2] = 't';
  nrf.txBuff[3] = 'S';
  nrf.txBuff[4] = 'p';
  nrf.txBuff[5] = 'r';
  nrf.txBuff[6] = 'o';
  nrf.txBuff[7] = 'u';
  nrf.txBuff[8] = 't';
  nrf.txLens = TX_LENS;
  nrf.irqStatus = ENABLE;

	while (1) {
    LED_B_Toggle();
//    delay_ms(50);
    if (nrf.txLens != 0) {
      status = NRF24_TxPacketIRQ();
    }

    if ((nrf.txFlag == NRF_STA_TX_DS) && (nrf.txLens == 0)) {
      LED_G_Toggle();
      nrf.txLens = TX_LENS;
      nrf.txBuff[TX_LENS - 1] = 0;
      printf("[TXD] %s, lens = %03d, count = %03d\r\n", nrf.txBuff, nrf.txLens, txCount);
      OLED_PutStr(CENTER(FONT16, "KitSprout"), LINE(FONT16, 3), &FONT16, (char *)nrf.txBuff, WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 5), &FONT16, S_DEC, 3, nrf.txLens, WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 6), &FONT16, S_DEC, 3, txCount, WHITE, BLACK);
      nrf.txBuff[TX_LENS - 1] = txCount++;
    }
    else if (nrf.txFlag == NRF_STA_MAX_RT) {
      nrf.txLens = TX_LENS;
      printf("[MRT] %02X, lens = %3d, state = %3d\r\n", nrf.txFlag, nrf.txLens, status);
    }
    else {
      printf("[ELS] %02X, lens = %3d, state = %3d\r\n", nrf.txFlag, nrf.txLens, status);
    }
	}
	
#else
  char displayStr[] = "RX DEMO";
  OLED_PutStr(CENTER(FONT16, displayStr), LINE(FONT16, 1), &FONT16, displayStr, WHITE, BLACK);
	NRF24_SetMode(NRF_Mode_RX);
  nrf.irqStatus = ENABLE;

  while (1) {
    LED_B_Toggle();
//    delay_ms(50);
    if ((nrf.rxFlag == NRF_STA_RX_DR) && (nrf.rxLens != 0)) {
      LED_G_Toggle();
      rxCount = nrf.rxBuff[TX_LENS - 1];
      nrf.rxBuff[TX_LENS - 1] = 0;
      printf("[RXD] %s, lens = %03d, count = %03d\r\n", nrf.rxBuff, nrf.rxLens, rxCount);
      OLED_PutStr(CENTER(FONT16, "KitSprout"), LINE(FONT16, 3), &FONT16, (char *)nrf.rxBuff, WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 5), &FONT16, S_DEC, 3, nrf.rxLens, WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 6), &FONT16, S_DEC, 3, rxCount, WHITE, BLACK);
      nrf.rxLens = 0;
    }
  }

#endif

}

/*************************************** END OF FILE ****************************************/
