/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    stm32f4_exti.c
  * @author  KitSprout
  * @date    16-Mar-2017
  * @brief   
  * 
  */

/* Includes --------------------------------------------------------------------------------*/
#include "stm32f4_system.h"
#include "stm32f4_exti.h"

/** @addtogroup STM32_Driver
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
pFunc ECBF_EXTIx_KEY_JR = NULL;

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
  * @brief  EXTIx_KEY_Config
  */
void EXTIx_KEY_JR_Config( pFunc event )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  ECBF_EXTIx_KEY_JR = event;

  /* GPIO Pin ******************************************************************/
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin  = KEY_JR_PIN;
  HAL_GPIO_Init(KEY_JR_GPIO_PORT, &GPIO_InitStruct);

  /* EXTI IT *******************************************************************/
  HAL_NVIC_SetPriority(KEY_JR_EXTIx_IRQ, KEY_JR_EXTIx_IRQn_PREEMPT, KEY_JR_EXTIx_IRQn_SUB);
  HAL_NVIC_EnableIRQ(KEY_JR_EXTIx_IRQ);
}

/*************************************** END OF FILE ****************************************/
