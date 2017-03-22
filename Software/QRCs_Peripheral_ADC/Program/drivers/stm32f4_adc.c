/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    stm32f4_adc.c
  * @author  KitSprout
  * @date    22-Mar-2017
  * @brief   
  * 
  */

/* Includes --------------------------------------------------------------------------------*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"

/** @addtogroup STM32_Driver
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
static ADC_HandleTypeDef AdcHandle;
static __IO uint16_t AdcConvBuf[JS_MAX_SAMPLEBUF][JS_MAX_CHANNEL] = {0};

AdcHandle_st hAdc1 = {
  .handle    = &AdcHandle,
  .convValue = (uint16_t*)AdcConvBuf,
};

/* Private function prototypes -------------------------------------------------------------*/

/* MSP functions ---------------------------------------------------------------------------*/

void HAL_ADC_MspInit( ADC_HandleTypeDef *hadc )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  static DMA_HandleTypeDef hadcDma;

  if (hadc->Instance == JS_ADCx) {

    /* ADC and DMA Clk ***********************************************************/
    JS_ADCx_CLK_ENABLE();
    JS_ADCx_DMA_CLK_ENABLE();

    /* ADC Pin *******************************************************************/
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    GPIO_InitStruct.Pin  = JS_ADCx_RX_CHANNEL_PIN;
    HAL_GPIO_Init(JS_ADCx_RX_CHANNEL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  = JS_ADCx_RY_CHANNEL_PIN;
    HAL_GPIO_Init(JS_ADCx_RY_CHANNEL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  = JS_ADCx_LX_CHANNEL_PIN;
    HAL_GPIO_Init(JS_ADCx_LX_CHANNEL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  = JS_ADCx_LY_CHANNEL_PIN;
    HAL_GPIO_Init(JS_ADCx_LY_CHANNEL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  = JS_ADCx_BAT_CHANNEL_PIN;
    HAL_GPIO_Init(JS_ADCx_BAT_CHANNEL_GPIO_PORT, &GPIO_InitStruct);

    /* DMA Init ******************************************************************/
    hadcDma.Instance                 = JS_ADCx_DMA_STREAM;
    hadcDma.Init.Channel             = JS_ADCx_DMA_CHANNEL;
    hadcDma.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hadcDma.Init.PeriphInc           = DMA_PINC_DISABLE;
    hadcDma.Init.MemInc              = DMA_MINC_ENABLE;
    hadcDma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hadcDma.Init.MemDataAlignment    = DMA_PDATAALIGN_HALFWORD;
    hadcDma.Init.Mode                = DMA_CIRCULAR;
    hadcDma.Init.Priority            = DMA_PRIORITY_HIGH;
    hadcDma.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    hadcDma.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_HALFFULL;
    hadcDma.Init.MemBurst            = DMA_MBURST_SINGLE;
    hadcDma.Init.PeriphBurst         = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&hadcDma);
    __HAL_LINKDMA(hadc, DMA_Handle, hadcDma);

    /* DMA IT ********************************************************************/
    HAL_NVIC_SetPriority(JS_ADCx_DMA_IRQn, JS_ADCx_DMA_IRQn_PREEMPT, JS_ADCx_DMA_IRQn_SUB);
    HAL_NVIC_EnableIRQ(JS_ADCx_DMA_IRQn);
  }
}

/**
  * @brief ADC MSP De-Initialization
  */
void HAL_ADC_MspDeInit( ADC_HandleTypeDef *hadc )
{
  if (hadc->Instance == JS_ADCx) {
    JS_ADCx_FORCE_RESET();
    JS_ADCx_RELEASE_RESET();
    HAL_GPIO_DeInit(JS_ADCx_RX_CHANNEL_GPIO_PORT, JS_ADCx_RX_CHANNEL_PIN);
    HAL_GPIO_DeInit(JS_ADCx_RY_CHANNEL_GPIO_PORT, JS_ADCx_RY_CHANNEL_PIN);
    HAL_GPIO_DeInit(JS_ADCx_LX_CHANNEL_GPIO_PORT, JS_ADCx_LX_CHANNEL_PIN);
    HAL_GPIO_DeInit(JS_ADCx_LY_CHANNEL_GPIO_PORT, JS_ADCx_LY_CHANNEL_PIN);
    HAL_GPIO_DeInit(JS_ADCx_BAT_CHANNEL_GPIO_PORT, JS_ADCx_BAT_CHANNEL_PIN);
  }
}

/**
  * @brief  Regular conversion complete callback in non blocking mode 
  */
void HAL_ADC_ConvCpltCallback( ADC_HandleTypeDef* hadc )
{
  if (hadc->Instance == JS_ADCx) {
    // ...
  }
}

/**
  * @brief  Regular conversion half DMA transfer callback in non blocking mode 
  */
void HAL_ADC_ConvHalfCpltCallback( ADC_HandleTypeDef* hadc )
{
  if (hadc->Instance == JS_ADCx) {
    // ...
  }
}

/**
  * @brief  Analog watchdog callback in non blocking mode 
  */
void HAL_ADC_LevelOutOfWindowCallback( ADC_HandleTypeDef* hadc )
{
  if (hadc->Instance == JS_ADCx) {
    // ...
  }
}

/**
  * @brief  Error ADC callback.
  */
void HAL_ADC_ErrorCallback( ADC_HandleTypeDef *hadc )
{
  if (hadc->Instance == JS_ADCx) {
    // ...
  }
}

/**
  * @brief  Injected conversion complete callback in non blocking mode 
  */
void HAL_ADCEx_InjectedConvCpltCallback( ADC_HandleTypeDef* hadc )
{
  if (hadc->Instance == JS_ADCx) {
    // ...
  }
}

/* Private functions -----------------------------------------------------------------------*/

/**
  * @brief  ADC_Config
  */
void ADC_Config( void )
{
  ADC_ChannelConfTypeDef ADC_ChannelConfStruct;

  /* ADC Init ******************************************************************/
  AdcHandle.Instance                   = JS_ADCx;
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;
  AdcHandle.Init.ScanConvMode          = ENABLE;
  AdcHandle.Init.ContinuousConvMode    = ENABLE;
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;
  AdcHandle.Init.NbrOfDiscConversion   = 0;
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  AdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  AdcHandle.Init.NbrOfConversion       = JS_MAX_CHANNEL;
  AdcHandle.Init.DMAContinuousRequests = ENABLE;
  AdcHandle.Init.EOCSelection          = DISABLE;
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
    while (1) { ; }

  /* ADC Channel Init **********************************************************/
  ADC_ChannelConfStruct.Channel      = JS_ADCx_RX_CHANNEL;
  ADC_ChannelConfStruct.Rank         = JS_ADCx_RX_RANK;
  ADC_ChannelConfStruct.SamplingTime = JS_ADCx_SAMPLETIME;
  ADC_ChannelConfStruct.Offset       = 0;
  if (HAL_ADC_ConfigChannel(&AdcHandle, &ADC_ChannelConfStruct) != HAL_OK)
    while (1) { ; }

  ADC_ChannelConfStruct.Channel      = JS_ADCx_RY_CHANNEL;
  ADC_ChannelConfStruct.Rank         = JS_ADCx_RY_RANK;
  ADC_ChannelConfStruct.SamplingTime = JS_ADCx_SAMPLETIME;
  ADC_ChannelConfStruct.Offset       = 0;
  if (HAL_ADC_ConfigChannel(&AdcHandle, &ADC_ChannelConfStruct) != HAL_OK)
    while (1) { ; }

  ADC_ChannelConfStruct.Channel      = JS_ADCx_LX_CHANNEL;
  ADC_ChannelConfStruct.Rank         = JS_ADCx_LX_RANK;
  ADC_ChannelConfStruct.SamplingTime = JS_ADCx_SAMPLETIME;
  ADC_ChannelConfStruct.Offset       = 0;
  if (HAL_ADC_ConfigChannel(&AdcHandle, &ADC_ChannelConfStruct) != HAL_OK)
    while (1) { ; }

  ADC_ChannelConfStruct.Channel      = JS_ADCx_LY_CHANNEL;
  ADC_ChannelConfStruct.Rank         = JS_ADCx_LY_RANK;
  ADC_ChannelConfStruct.SamplingTime = JS_ADCx_SAMPLETIME;
  ADC_ChannelConfStruct.Offset       = 0;
  if (HAL_ADC_ConfigChannel(&AdcHandle, &ADC_ChannelConfStruct) != HAL_OK)
    while (1) { ; }

  ADC_ChannelConfStruct.Channel      = JS_ADCx_BAT_CHANNEL;
  ADC_ChannelConfStruct.Rank         = JS_ADCx_BAT_RANK;
  ADC_ChannelConfStruct.SamplingTime = JS_ADCx_SAMPLETIME;
  ADC_ChannelConfStruct.Offset       = 0;
  if (HAL_ADC_ConfigChannel(&AdcHandle, &ADC_ChannelConfStruct) != HAL_OK)
    while (1) { ; }

  /* ADC Start *****************************************************************/
  if (HAL_ADC_Start_DMA(&AdcHandle, (uint32_t*)AdcConvBuf, JS_MAX_CHANNEL * JS_MAX_SAMPLEBUF) != HAL_OK)
    while (1) { ; }
}

uint16_t ADC_GetValue( uint8_t index )
{
  return ((uint16_t)(AdcConvBuf[0][index]));
}

void ADC_GetAveValue( uint16_t *aveAdc )
{
  uint32_t tmp;
  for (uint8_t i = 0; i < JS_MAX_CHANNEL; i++) {
    tmp = 0;
    for (uint8_t j = 0; j < JS_MAX_SAMPLEBUF; j++) {
      tmp += AdcConvBuf[j][i];
    }
    aveAdc[i] = tmp >> 3;
  }
}

/*************************************** END OF FILE ****************************************/
