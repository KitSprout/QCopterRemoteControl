/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
static u16 ADC_DMA_BufR[ADC_Sample][ADC_Channel] = {0};
static u16 ADC_DMA_BufL[ADC_Sample][ADC_Channel] = {0};
static u16 ADC_DMA_BufZ[ADC_Sample][ADC_Channel] = {0};
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : ADC_Config
**功能 : ADC 配置
**輸入 : None
**輸出 : None
**使用 : ADC_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void ADC_Config( void )
{
  DMA_InitTypeDef DMA_InitStruct;
  ADC_InitTypeDef ADC_InitStruct;
  ADC_CommonInitTypeDef ADC_CommonInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  /* ADC Clk Init *************************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC2 | RCC_APB2Periph_ADC3, ENABLE);

  /* ADC_RZ PB0  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  /* ADC_LX PC0  */ /* ADC_LZ PC1  */ /* ADC_LY PC2  */ /* ADC_RY PC3  */ /* ADC_RX PC4  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* ADC1 DMA Stream0 Channel_0 Init ******************************************/
  DMA_InitStruct.DMA_Channel = DMA_Channel_0;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)ADC1_DR_ADDRESS;               // Peripheral address
  DMA_InitStruct.DMA_Memory0BaseAddr = (u32)&ADC_DMA_BufR;                    // Memory address
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;                        // Peripheral to Memory
  DMA_InitStruct.DMA_BufferSize = ADC_Channel*ADC_Sample;                     // Memory Buffer Size
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               // Peripheral address 遞增 Disable
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                        // Memory address 遞增 Enable
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    // Peripheral Data Size 16bit
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            // Memory Data Size 16bit
  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                                // 循環模式 Enable
  DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;                          // ADC DMA通道 普通優先級
  DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;                         // DMA FIFO Disable
  DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStruct);
  DMA_Cmd(DMA2_Stream0, ENABLE);

  /* ADC2 DMA Stream3 Channel_1 Init ******************************************/
  DMA_InitStruct.DMA_Channel = DMA_Channel_1;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)ADC2_DR_ADDRESS;               // Peripheral address
  DMA_InitStruct.DMA_Memory0BaseAddr = (u32)&ADC_DMA_BufZ;                    // Memory address
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;                        // Peripheral to Memory
  DMA_InitStruct.DMA_BufferSize = ADC_Channel*ADC_Sample;                     // Memory Buffer Size
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               // Peripheral address 遞增 Disable
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                        // Memory address 遞增 Enable
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    // Peripheral Data Size 16bit
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            // Memory Data Size 16bit
  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                                // 循環模式 Enable
  DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;                          // ADC DMA通道 普通優先級
  DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;                         // DMA FIFO Disable
  DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream3, &DMA_InitStruct);
  DMA_Cmd(DMA2_Stream3, ENABLE);

  /* ADC3 DMA Stream1 Channel_2 Init ******************************************/
  DMA_InitStruct.DMA_Channel = DMA_Channel_2;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)ADC3_DR_ADDRESS;               // Peripheral address
  DMA_InitStruct.DMA_Memory0BaseAddr = (u32)&ADC_DMA_BufL;                    // Memory address
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;                        // Peripheral to Memory
  DMA_InitStruct.DMA_BufferSize = ADC_Channel*ADC_Sample;                     // Memory Buffer Size
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               // Peripheral address 遞增 Disable
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                        // Memory address 遞增 Enable
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    // Peripheral Data Size 16bit
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            // Memory Data Size 16bit
  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                                // 循環模式 Enable
  DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;                          // ADC DMA通道 普通優先級
  DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;                         // DMA FIFO Disable
  DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream1, &DMA_InitStruct);
  DMA_Cmd(DMA2_Stream1, ENABLE);

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;                       // 獨立模式
  ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div2;                    // 預分頻4
  ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;        // ADC DMA Mode Disable
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;  // 轉換延遲時間
  ADC_CommonInit(&ADC_CommonInitStruct);

  /* ADC1 Init ****************************************************************/
  ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;                         // 解析度 12bit
  ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                   // 掃描模式
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                             // 連續轉換模式
  ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    // 外部觸發 Disable
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                         // ADC數據右對齊
  ADC_InitStruct.ADC_NbrOfConversion = ADC_Channel;                           // 轉換ADC通道數目
  ADC_Init(ADC1, &ADC_InitStruct);

  /* ADC2 Init ****************************************************************/
  ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;                         // 解析度 12bit
  ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                   // 掃描模式
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                             // 連續轉換模式
  ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    // 外部觸發 Disable
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                         // ADC數據右對齊
  ADC_InitStruct.ADC_NbrOfConversion = ADC_Channel;                           // 轉換ADC通道數目
  ADC_Init(ADC2, &ADC_InitStruct);

  /* ADC3 Init ****************************************************************/
  ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;                         // 解析度 12bit
  ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                   // 掃描模式
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                             // 連續轉換模式
  ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;    // 外部觸發 Disable
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                         // ADC數據右對齊
  ADC_InitStruct.ADC_NbrOfConversion = ADC_Channel;                           // 轉換ADC通道數目
  ADC_Init(ADC3, &ADC_InitStruct);

  /* ADC1 Regular Config ******************************************************/
  ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 1, ADC_SampleTime_28Cycles); // ADC_RX
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 2, ADC_SampleTime_28Cycles); // ADC_RY

  /* ADC2 Regular Config ******************************************************/
  ADC_RegularChannelConfig(ADC2, ADC_Channel_8,  1, ADC_SampleTime_28Cycles); // ADC_RZ
  ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 2, ADC_SampleTime_28Cycles); // ADC_LZ

  /* ADC3 Regular Config ******************************************************/
  ADC_RegularChannelConfig(ADC3, ADC_Channel_10, 1, ADC_SampleTime_28Cycles); // ADC_LX
  ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2, ADC_SampleTime_28Cycles); // ADC_LY

  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
  ADC_DMARequestAfterLastTransferCmd(ADC2, ENABLE);
  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
  ADC_DMACmd(ADC1, ENABLE);
  ADC_DMACmd(ADC2, ENABLE);
  ADC_DMACmd(ADC3, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  ADC_Cmd(ADC2, ENABLE);
  ADC_Cmd(ADC3, ENABLE);
  ADC_SoftwareStartConv(ADC1);
  ADC_SoftwareStartConv(ADC2);
  ADC_SoftwareStartConv(ADC3);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : ADC_Average
**功能 : 將 ADC 轉換後的資料取平均
**輸入 : ADC_AveTr
**輸出 : None
**使用 : ADC_Average(ADC_AveTr);
**=====================================================================================================*/
/*=====================================================================================================*/
void ADC_Average( u16* pADC_AveTr )
{
  u8 i = 0, j = 0;
  u32 ADC_DMA_TmpR[ADC_Channel] = {0};
  u32 ADC_DMA_TmpL[ADC_Channel] = {0};
  u32 ADC_DMA_TmpZ[ADC_Channel] = {0};

  for(i=0; i<ADC_Channel; i++) {
    for(j=0; j<ADC_Sample; j++) {
      ADC_DMA_TmpR[i] += ADC_DMA_BufR[j][i];
      ADC_DMA_TmpL[i] += ADC_DMA_BufL[j][i];
      ADC_DMA_TmpZ[i] += ADC_DMA_BufZ[j][i];
    }
    pADC_AveTr[i]   = (u16)(ADC_DMA_TmpR[i] / ADC_Sample);
    pADC_AveTr[i+2] = (u16)(ADC_DMA_TmpL[i] / ADC_Sample);
    pADC_AveTr[i+4] = (u16)(ADC_DMA_TmpZ[i] / ADC_Sample);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
