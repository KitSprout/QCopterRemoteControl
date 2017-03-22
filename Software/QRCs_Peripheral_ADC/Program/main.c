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
#include "drivers\stm32f4_adc.h"
#include "modules\serial.h"
#include "stm32f4xx_bsp.h"

/** @addtogroup STM32_Program
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
static uint16_t aveAdc[JS_MAX_CHANNEL] = {0};
static int16_t  joyStick[JS_MAX_CHANNEL] = {0};

/* Private function prototypes -------------------------------------------------------------*/
void convAdcInfo( void );

/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  HAL_Init();
  BSP_GPIO_Config();
  BSP_ADC_Config();
  BSP_UART_SERIAL_Config(NULL);

  while (1) {
    ADC_GetAveValue(aveAdc);
    convAdcInfo();
    printf("RX = %4d, RY = %4d, LX = %4d, LY = %4d, BAT = %4d\r\n", joyStick[0], joyStick[1], joyStick[2], joyStick[3], joyStick[4]);
    LED_G_Toggle();
    delay_ms(200);
  }
}

void convAdcInfo( void )
{
  joyStick[0] = 1024 - (aveAdc[0] >> 1);
  joyStick[1] = (aveAdc[1] >> 1) - 1024;
  joyStick[2] = (aveAdc[2] >> 1) - 1024;
  joyStick[3] = 2048 - (aveAdc[3] >> 1);
  joyStick[4] = aveAdc[4] * (3300.0f / 2048);
}

/*************************************** END OF FILE ****************************************/
