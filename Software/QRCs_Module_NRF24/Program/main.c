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
#define __NRF24L01_IRQ__
//#define __NRF24L01_TX__
//#define __NRF24L01_RX__

#define TX_LENS 10

/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
static uint8_t rxCount = 0;
static uint8_t txCount = 0;

extern NRF_DataTypeDef nrf;

/* Private function prototypes -------------------------------------------------------------*/
void demo_tx( void );
void demo_rx( void );
void demo_txrx_irq( void );

void txIrqEvent( void );
void rxIrqEvent( void );

/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  HAL_Init();
  BSP_GPIO_Config();
  BSP_UART_SERIAL_Config(NULL);
  BSP_SPI_NRF24_Config();
  BSP_SPI_OLED_Config();

  nrf.txEventCallback = txIrqEvent;
  nrf.rxEventCallback = rxIrqEvent;

#if	defined(__NRF24L01_IRQ__)
  OLED_PutStr(CENTER(FONT16, "TRX DEMO"), LINE(FONT16, 1), &FONT16, "TRX DEMO", WHITE, BLACK);
  demo_txrx_irq();

#elif	defined(__NRF24L01_TX__)
  OLED_PutStr(CENTER(FONT16, "TX DEMO"), LINE(FONT16, 2), &FONT16, "TX DEMO", WHITE, BLACK);
  demo_tx();

#elif defined(__NRF24L01_RX__)
  OLED_PutStr(CENTER(FONT16, "RX DEMO"), LINE(FONT16, 2), &FONT16, "RX DEMO", WHITE, BLACK);
  demo_rx();

#else
#error "ERROR!!! NO DEFINE!!!"

#endif

}

void demo_txrx_irq( void )
{
  nrf.txBuff[0] = 'K';
  nrf.txBuff[1] = 'i';
  nrf.txBuff[2] = 't';
  nrf.txBuff[3] = 'S';
  nrf.txBuff[4] = 'p';
  nrf.txBuff[5] = 'r';
  nrf.txBuff[6] = 'o';
  nrf.txBuff[7] = 'u';
  nrf.txBuff[8] = 't';
  nrf.txBuff[9] = 0;
  nrf.txLens    = TX_LENS;
  nrf.irqStatus = DISABLE;

  while(1) {
    nrf.irqStatus = DISABLE;
    nrf.txBuff[9] = txCount;
    NRF24_TxPacketDef();
    NRF24_OperationMode(NRF_OPMODE_RX);
    nrf.irqStatus = ENABLE;

    
    if (nrf.txFlag == NRF_STA_TX_DS) {
      LED_G_Toggle();
      nrf.txFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "TXD"), LINE(FONT16, 3), &FONT16, "TXD", WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 4), &FONT16, S_DEC, 3, txCount, WHITE, BLACK);
      txCount++;
    }
    else if (nrf.txFlag == NRF_STA_MAX_RT) {
      nrf.txFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "MRT"), LINE(FONT16, 3), &FONT16, "MRT", WHITE, BLACK);
    }
    else {
      nrf.txFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "ELS"), LINE(FONT16, 3), &FONT16, "ELS", WHITE, BLACK);
    }

    if (nrf.rxFlag == NRF_STA_RX_DR) {
      LED_B_Toggle();
      nrf.rxFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "RXD"), LINE(FONT16, 5), &FONT16, "RXD", WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 6), &FONT16, S_DEC, 3, rxCount, WHITE, BLACK);
    }
    else {
      nrf.rxFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "ELS"), LINE(FONT16, 5), &FONT16, "ELS", WHITE, BLACK);
    }
  }
}

void demo_tx( void )
{
  nrf.txBuff[0] = 'K';
  nrf.txBuff[1] = 'i';
  nrf.txBuff[2] = 't';
  nrf.txBuff[3] = 'S';
  nrf.txBuff[4] = 'p';
  nrf.txBuff[5] = 'r';
  nrf.txBuff[6] = 'o';
  nrf.txBuff[7] = 'u';
  nrf.txBuff[8] = 't';
  nrf.txBuff[9] = 0;
  nrf.txLens    = TX_LENS;

  NRF24_OperationMode(NRF_OPMODE_STANDBY);

	while (1) {
    nrf.txBuff[9] = txCount;
    NRF24_TxPacketDef();
    NRF24_OperationMode(NRF_OPMODE_STANDBY);

    if (nrf.txFlag == NRF_STA_TX_DS) {
      LED_G_Toggle();
      nrf.txFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "TXD"), LINE(FONT16, 4), &FONT16, "TXD", WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 6), &FONT16, S_DEC, 3, txCount, WHITE, BLACK);
      txCount++;
    }
    else if (nrf.txFlag == NRF_STA_MAX_RT) {
      LED_B_Toggle();
      nrf.txFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "MRT"), LINE(FONT16, 4), &FONT16, "MRT", WHITE, BLACK);
    }
    else {
      LED_R_Toggle();
      nrf.txFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "ELS"), LINE(FONT16, 4), &FONT16, "ELS", WHITE, BLACK);
    }
  }
}

void demo_rx( void )
{
  NRF24_OperationMode(NRF_OPMODE_STANDBY);

  while (1) {
    NRF24_RxPacketDef();
    NRF24_OperationMode(NRF_OPMODE_STANDBY);

    if (nrf.rxFlag == NRF_STA_RX_DR) {
      LED_G_Toggle();
      nrf.txFlag = NRF_STA_NULL;
      rxCount = nrf.rxBuff[TX_LENS - 1];
      OLED_PutStr(CENTER(FONT16, "RXD"), LINE(FONT16, 4), &FONT16, "RXD", WHITE, BLACK);
      OLED_PutNum(CENTER(FONT16, "000"), LINE(FONT16, 6), &FONT16, S_DEC, 3, rxCount, WHITE, BLACK);
    }
    else if (nrf.rxFlag == NRF_STA_TIMUOUT) {
      LED_B_Toggle();
      nrf.rxFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "TOU"), LINE(FONT16, 4), &FONT16, "TIM", WHITE, BLACK);
    }
    else {
      LED_R_Toggle();
      nrf.txFlag = NRF_STA_NULL;
      OLED_PutStr(CENTER(FONT16, "ELS"), LINE(FONT16, 4), &FONT16, "ELS", WHITE, BLACK);
    }
  }
}

void txIrqEvent( void )
{

}

void rxIrqEvent( void )
{
  rxCount = nrf.rxBuff[TX_LENS - 1];
}

/*************************************** END OF FILE ****************************************/
