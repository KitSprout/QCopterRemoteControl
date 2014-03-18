/*==============================================================================================*/
/*==============================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_spi.h"
#include "module_mpu6500.h"
/*==============================================================================================*/
/*==============================================================================================*/
#define IMU_CSM   PAO(4)
/*==============================================================================================*/
/*==============================================================================================*
**函數 : MPU6500_Config
**功能 : 初始化 MPU6500
**輸入 : None
**輸出 : None
**使用 : MPU6500_Config();
**==============================================================================================*/
/*==============================================================================================*/
void MPU6500_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* Clk Init *************************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

  /* CSM PA4  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* SCK PA5  */	/* SDO PA6  */	/* SDI PA7  */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  IMU_CSM = 1;

  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // 雙線全雙工
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // 主模式
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // 數據大小8位
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                          // 時鐘極性，空閒時為低
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // 第1個邊沿有效，上升沿為采樣時刻
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // NSS信號由軟件產生
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;   // 8分頻，9MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // 高位在前
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(IMU_SPI, &SPI_InitStruct);

  SPI_Cmd(IMU_SPI, ENABLE);
}
/*==============================================================================================*/
/*==============================================================================================*
**函數 : MPU6500_Init
**功能 : 初始化MPU6500
**輸入 : None
**輸出 : None
**使用 : MPU6500_Init()
**==============================================================================================*/
/*==============================================================================================*/
void MPU6500_Init( void )
{
}
/*==============================================================================================*/
/*==============================================================================================*
**函數 : MPU6500_ReadReg
**功能 : 讀暫存器
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : MPU6500_ReadReg(MPU6500_WHO_AM_I);
**==============================================================================================*/
/*==============================================================================================*/
static u8 MPU6500_ReadReg( u8 ReadAddr )
{
  u8 ReadData;

  IMU_CSM = 0;
  SPI_WriteByte(IMU_SPI, ReadAddr);
  ReadData = SPI_ReadByte(IMU_SPI);
  IMU_CSM = 1;

  return ReadData;
}
/*==============================================================================================*/
/*==============================================================================================*
**函數 : MPU6500_ReadID
**功能 : 讀裝置 ID
**輸入 : None
**輸出 : DeviceID
**使用 : DeviceID = MPU6500_ReadID();
**==============================================================================================*/
/*==============================================================================================*/
u8 MPU6500_ReadID( void )
{
  u8 DeviceID = 0x00;

  DeviceID = MPU6500_ReadReg(MPU6500_WHO_AM_I);

  return DeviceID;
}
/*==============================================================================================*/
/*==============================================================================================*/
