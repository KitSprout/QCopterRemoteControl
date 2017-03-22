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

//#define KS_HW_UART_HAL_LIBRARY

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

/* -------- ADC DMA */
#define JS_MAX_CHANNEL                5
#define JS_MAX_SAMPLEBUF              8

#define JS_ADCx                       ADC1
#define JS_ADCx_CLK_ENABLE()          __HAL_RCC_ADC1_CLK_ENABLE()
#define JS_ADCx_DMA_CLK_ENABLE()      __HAL_RCC_DMA2_CLK_ENABLE()
#define JS_ADCx_DMA_CHANNEL           DMA_CHANNEL_0
#define JS_ADCx_DMA_STREAM            DMA2_Stream0
#define JS_ADCx_DMA_IRQn              DMA2_Stream0_IRQn
#define JS_ADCx_DMA_IRQn_PREEMPT      0x0F
#define JS_ADCx_DMA_IRQn_SUB          0x0F

#define JS_ADCx_FORCE_RESET()         __HAL_RCC_ADC_FORCE_RESET()
#define JS_ADCx_RELEASE_RESET()       __HAL_RCC_ADC_RELEASE_RESET()
#define JS_ADCx_SAMPLETIME            ADC_SAMPLETIME_480CYCLES

#define JS_ADCx_RX_RANK               1
#define JS_ADCx_RX_CHANNEL            ADC_CHANNEL_8
#define JS_ADCx_RX_CHANNEL_PIN        GPIO_PIN_0
#define JS_ADCx_RX_CHANNEL_GPIO_PORT  GPIOB

#define JS_ADCx_RY_RANK               2
#define JS_ADCx_RY_CHANNEL            ADC_CHANNEL_9
#define JS_ADCx_RY_CHANNEL_PIN        GPIO_PIN_1
#define JS_ADCx_RY_CHANNEL_GPIO_PORT  GPIOB

#define JS_ADCx_LX_RANK               3
#define JS_ADCx_LX_CHANNEL            ADC_CHANNEL_1
#define JS_ADCx_LX_CHANNEL_PIN        GPIO_PIN_1
#define JS_ADCx_LX_CHANNEL_GPIO_PORT  GPIOA

#define JS_ADCx_LY_RANK               4
#define JS_ADCx_LY_CHANNEL            ADC_CHANNEL_0
#define JS_ADCx_LY_CHANNEL_PIN        GPIO_PIN_0
#define JS_ADCx_LY_CHANNEL_GPIO_PORT  GPIOA

#define JS_ADCx_BAT_RANK              5
#define JS_ADCx_BAT_CHANNEL           ADC_CHANNEL_2
#define JS_ADCx_BAT_CHANNEL_PIN       GPIO_PIN_2
#define JS_ADCx_BAT_CHANNEL_GPIO_PORT GPIOA

/* -------- UART Serial */
#define SERIAL_MAX_TXBUF              16
#define SERIAL_MAX_RXBUF              16

#define SERIAL_UARTx                  USART1
#define SERIAL_UARTx_CLK_ENABLE()     __HAL_RCC_USART1_CLK_ENABLE()
#define SERIAL_UARTx_IRQn             USART1_IRQn
#define SERIAL_UARTx_IRQn_PREEMPT     0x0F
#define SERIAL_UARTx_IRQn_SUB         1

#define SERIAL_UARTx_FORCE_RESET()    __HAL_RCC_USART1_FORCE_RESET()
#define SERIAL_UARTx_RELEASE_RESET()  __HAL_RCC_USART1_RELEASE_RESET()

#define SERIAL_TX_PIN                 GPIO_PIN_9
#define SERIAL_TX_GPIO_PORT           GPIOA
#define SERIAL_TX_AF                  GPIO_AF7_USART1

#define SERIAL_RX_PIN                 GPIO_PIN_10
#define SERIAL_RX_GPIO_PORT           GPIOA
#define SERIAL_RX_AF                  GPIO_AF7_USART1

#define SERIAL_BAUDRATE               115200
#define SERIAL_BYTESIZE               UART_WORDLENGTH_8B
#define SERIAL_STOPBITS               UART_STOPBITS_1
#define SERIAL_PARITY                 UART_PARITY_NONE
#define SERIAL_HARDWARECTRL           UART_HWCONTROL_NONE
#define SERIAL_MODE                   UART_MODE_TX_RX
#define SERIAL_OVERSAMPLE             UART_OVERSAMPLING_16

/* Exported functions ----------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
