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
#include "stm32f4xx_bsp.h"

/** @addtogroup STM32_Program
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  HAL_Init();
  BSP_GPIO_Config();

  LED_R_Reset();
  LED_G_Reset();
  LED_B_Reset();

  while (1) {
    LED_R_Reset();
    LED_G_Reset();
    LED_B_Reset();
    delay_ms(100);
    LED_R_Set();
    LED_G_Set();
    LED_B_Set();
    delay_ms(100);

    while (KEY_S1_Read()) {
      LED_R_Toggle();
      delay_ms(50);
      LED_R_Toggle();
      delay_ms(50);
    }
    while (KEY_S2_Read()) {
      LED_G_Toggle();
      delay_ms(50);
      LED_G_Toggle();
      delay_ms(50);
    }
    while (KEY_PL_Read()) {
      LED_R_Toggle();
      delay_ms(100);
      LED_R_Toggle();
      delay_ms(100);
    }
    while (KEY_PP_Read()) {
      LED_G_Toggle();
      delay_ms(100);
      LED_G_Toggle();
      delay_ms(100);
    }
    while (KEY_PR_Read()) {
      LED_B_Toggle();
      delay_ms(100);
      LED_B_Toggle();
      delay_ms(100);
    }
    while (KEY_JR_Read()) {
      LED_B_Toggle();
      delay_ms(50);
      LED_B_Toggle();
      delay_ms(50);
    }
    while (KEY_JL_Read()) {
      LED_R_Toggle();
      delay_ms(50);
      LED_R_Toggle();
      delay_ms(50);
    }
  }
}

/*************************************** END OF FILE ****************************************/
