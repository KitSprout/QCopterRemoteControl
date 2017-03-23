/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    boardConfig.h
  * @author  KitSprout
  * @date    16-Mar-2017
  * @brief   
  * 
  */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __BOARDCONFIG_H
#define __BOARDCONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
/* Exported types --------------------------------------------------------------------------*/
/* Exported constants ----------------------------------------------------------------------*/

#define KS_HW_BOARD_NAME              "QCopterRCs"
#define KS_HW_MCU_NAME                "STM32F411CE"

#define KS_HW_CLOCK_SOUCE_HSE
//#define KS_HW_USE_CLOCK_SOUCE_HSI

/* -------- LED and KEY */
#define LED_R_PIN                     GPIO_PIN_15
#define LED_R_GPIO_PORT               GPIOC
#define LED_R_Set()                   __GPIO_SET(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Reset()                 __GPIO_RST(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Toggle()                __GPIO_TOG(LED_R_GPIO_PORT, LED_R_PIN)

#define LED_G_PIN                     GPIO_PIN_14
#define LED_G_GPIO_PORT               GPIOC
#define LED_G_Set()                   __GPIO_SET(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Reset()                 __GPIO_RST(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Toggle()                __GPIO_TOG(LED_G_GPIO_PORT, LED_G_PIN)

#define LED_B_PIN                     GPIO_PIN_13
#define LED_B_GPIO_PORT               GPIOC
#define LED_B_Set()                   __GPIO_SET(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Reset()                 __GPIO_RST(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Toggle()                __GPIO_TOG(LED_B_GPIO_PORT, LED_B_PIN)

#define KEY_S1_PIN                    GPIO_PIN_11
#define KEY_S1_GPIO_PORT              GPIOA
#define KEY_S1_Read()                 (__GPIO_READ(KEY_S1_GPIO_PORT, KEY_S1_PIN) != KEY_S1_PIN)

#define KEY_S2_PIN                    GPIO_PIN_8
#define KEY_S2_GPIO_PORT              GPIOA
#define KEY_S2_Read()                 (__GPIO_READ(KEY_S2_GPIO_PORT, KEY_S2_PIN) != KEY_S2_PIN)

#define KEY_PL_PIN                    GPIO_PIN_9
#define KEY_PL_GPIO_PORT              GPIOB
#define KEY_PL_Read()                 (__GPIO_READ(KEY_PL_GPIO_PORT, KEY_PL_PIN) != KEY_PL_PIN)

#define KEY_PP_PIN                    GPIO_PIN_8
#define KEY_PP_GPIO_PORT              GPIOB
#define KEY_PP_Read()                 (__GPIO_READ(KEY_PP_GPIO_PORT, KEY_PP_PIN) != KEY_PP_PIN)

#define KEY_PR_PIN                    GPIO_PIN_12
#define KEY_PR_GPIO_PORT              GPIOA
#define KEY_PR_Read()                 (__GPIO_READ(KEY_PR_GPIO_PORT, KEY_PR_PIN) != KEY_PR_PIN)

#define KEY_JR_PIN                    GPIO_PIN_2
#define KEY_JR_GPIO_PORT              GPIOB
#define KEY_JR_Read()                 (__GPIO_READ(KEY_JR_GPIO_PORT, KEY_JR_PIN) != KEY_JR_PIN)

#define KEY_JL_PIN                    GPIO_PIN_3
#define KEY_JL_GPIO_PORT              GPIOA
#define KEY_JL_Read()                 (__GPIO_READ(KEY_JL_GPIO_PORT, KEY_JL_PIN) != KEY_JL_PIN)

/* -------- TIM Timer */
#define TIMER2                        TIM2
#define TIMER2_CLK_ENABLE()           __HAL_RCC_TIM2_CLK_ENABLE()
#define TIMER2_IRQn                   TIM2_IRQn
#define TIMER2_TIMx_IRQn_PREEMPT      0x0F
#define TIMER2_TIMx_IRQn_SUB          1

#define TIMER3                        TIM3
#define TIMER3_CLK_ENABLE()           __HAL_RCC_TIM3_CLK_ENABLE()
#define TIMER3_IRQn                   TIM3_IRQn
#define TIMER3_TIMx_IRQn_PREEMPT      0x0F
#define TIMER3_TIMx_IRQn_SUB          1

#define TIMER4                        TIM4
#define TIMER4_CLK_ENABLE()           __HAL_RCC_TIM4_CLK_ENABLE()
#define TIMER4_IRQn                   TIM4_IRQn
#define TIMER4_TIMx_IRQn_PREEMPT      0x0F
#define TIMER4_TIMx_IRQn_SUB          1

/* Exported functions ----------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
