/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "module_otm8009.h"
#include "module_fontlib.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LCD_RST PCO(7)      // Reset
#define LCD_LIG TIM3->CCR1	// Back Light

static void LCD_BLigConfig( void );

u32 ReadID = {0};    //TEST
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : OTM8009_Config
**功能 : OTM8009 設定 & 配置
**輸入 : None
**輸出 : None
**使用 : OTM8009_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void OTM8009_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  FSMC_NORSRAMInitTypeDef FSMC_InitStruct;
  FSMC_NORSRAMTimingInitTypeDef TimingInitStruct; 

  /* FSMC Clk Init *************************************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC |
                         RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

  /* FSMC AF *************************************************************/
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource0,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource1,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource4,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource5,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource7,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource8,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9,  GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FSMC);

	/* TFT_RST PC7  */
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

  LCD_BLigConfig();

  /* FSMC_D0  PD14 */	/* FSMC_D1  PD15 */	/* FSMC_D2  PD0  */	/* FSMC_D3  PD1  */
  /* FSMC_D4  PE7  */	/* FSMC_D5  PE8  */	/* FSMC_D6  PE9  */	/* FSMC_D7  PE10 */
  /* FSMC_D8  PE11 */	/* FSMC_D9  PE12 */	/* FSMC_D10 PE13 */	/* FSMC_D11 PE14 */
  /* FSMC_D12 PE15 */	/* FSMC_D13 PD8  */	/* FSMC_D14 PD9  */	/* FSMC_D15 PD10 */
  /* FSMC_RD  PD4  */	/* FSMC_WR  PD5  */	/* FSMC_CS  PD7  */	/* FSMC_RS  PD11 */
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_7  |
                              GPIO_Pin_8  |	GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 |
                              GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 |
                              GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  TimingInitStruct.FSMC_AddressSetupTime = 0x05;
  TimingInitStruct.FSMC_AddressHoldTime = 0x05;
  TimingInitStruct.FSMC_DataSetupTime = 0x05;
  TimingInitStruct.FSMC_BusTurnAroundDuration = 0x00;
  TimingInitStruct.FSMC_CLKDivision = 0x005;
  TimingInitStruct.FSMC_DataLatency = 0x00;
  TimingInitStruct.FSMC_AccessMode = FSMC_AccessMode_B;

  FSMC_InitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_InitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_InitStruct.FSMC_MemoryType =FSMC_MemoryType_NOR;
  FSMC_InitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_InitStruct.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
  FSMC_InitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_InitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_InitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_InitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_InitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_InitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_InitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_InitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_InitStruct.FSMC_ReadWriteTimingStruct = &TimingInitStruct;
  FSMC_InitStruct.FSMC_WriteTimingStruct = &TimingInitStruct;

  FSMC_NORSRAMInit(&FSMC_InitStruct);
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_BLigConfig
**功能 : 背光 IO 配置
**輸入 : None
**輸出 : None
**使用 : LCD_BLigConfig();
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_BLigConfig( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);

  /* TFT_LIG PC6 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  TIM_DeInit(TIM3);

  /************************** PWM Output **************************************/
  /* 設定 TIM3 Time Base */
  TIM_TimeBaseStruct.TIM_Period = (u16)(256-1);               // 週期
  TIM_TimeBaseStruct.TIM_Prescaler = (u16)(0);                // 除頻
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;    // 上數
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);

  /* 設定 TIM3 OC */
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              // 配置為 PWM1 模式
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  // 致能 OC
  TIM_OCInitStruct.TIM_Pulse = 0;                             // 設置跳變值
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;      // 當計數值小於跳變值時為高電平
  TIM_OC1Init(TIM3, &TIM_OCInitStruct);                       // 初始化 TIM3 OC1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);           // 致能 TIM3 OC1 預裝載

  /* 啟動 */
  TIM_ARRPreloadConfig(TIM3, ENABLE);                         // 致能 TIM3 重載寄存器ARR
  TIM_Cmd(TIM3, ENABLE);                                      // 致能 TIM3

  LCD_LIG = 0;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_WriteCmd
**功能 : Write Command or Address
**輸入 : WriteCmd
**輸出 : None
**使用 : LCD_WriteCmd(0x0000);
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_WriteCmd( u16 WriteCmd )
{
  LCD_REG = WriteCmd;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_WriteData
**功能 : Write Data
**輸入 : WriteData
**輸出 : None
**使用 : LCD_WriteData(0x0000);
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_WriteData( u16 WriteData )
{
  LCD_RAM = WriteData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_ReadData
**功能 : Read Data
**輸入 : ReadData
**輸出 : None
**使用 : ReadData = LCD_ReadData();
**=====================================================================================================*/
/*=====================================================================================================*/
static u16 LCD_ReadData( void )
{
  return LCD_RAM;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_WriteReg
**功能 : Write Register
**輸入 : WriteAddr, WriteData
**輸出 : None
**使用 : LCD_WriteReg(0x0000, 0x0000);
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_WriteReg( u16 WriteAddr, u16 WriteData )
{
  LCD_REG = WriteAddr;
  LCD_RAM = WriteData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_ReadReg
**功能 : Read Register
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : ReadData = LCD_ReadReg(0x0000);
**=====================================================================================================*/
/*=====================================================================================================*/
//static u16 LCD_ReadReg( u16 ReadAddr )
//{
//  LCD_REG = ReadAddr;
//  return LCD_RAM;
//}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : OTM8009_Init
**功能 : OTM8009 Init
**輸入 : None
**輸出 : None
**使用 : OTM8009_Init();
**=====================================================================================================*/
/*=====================================================================================================*/
u32 OTM8009_Init( void )
{
  u16 tmp[8] = {0};
  u32 ReadID = 0;

  //  Hardware Reset
	LCD_RST = 0;
	Delay_1ms(15);
	LCD_RST = 1;
	Delay_1ms(50);

  // Check
  LCD_WriteCmd(0xA100);
  tmp[0] = LCD_ReadData(); // default 0x00
  tmp[1] = LCD_ReadData(); // default 0x01
  tmp[2] = LCD_ReadData(); // default 0x8B
  tmp[3] = LCD_ReadData(); // default 0x80
  tmp[4] = LCD_ReadData(); // default 0x09
  tmp[5] = LCD_ReadData(); // default 0xFF
  ReadID = Byte32(u32, tmp[1], tmp[2], tmp[3], tmp[4]);
  if( (tmp[0]!=0x00) || (tmp[5]!=0xFF) || (ReadID!=OTM8009_ID) )
    return ERROR;

  LCD_WriteReg(0xFF00, 0x80);
  LCD_WriteReg(0xFF01, 0x09);
  LCD_WriteReg(0xFF02, 0x01);
  LCD_WriteReg(0xFF80, 0x80);
  LCD_WriteReg(0xFF81, 0x09);
  LCD_WriteReg(0xFF82, 0x01);

  LCD_WriteReg(0xC0B4, 0x50);
  LCD_WriteReg(0xC489, 0x08);
  LCD_WriteReg(0xC0A3, 0x00);
  LCD_WriteReg(0xC582, 0xA3);
  LCD_WriteReg(0xC590, 0x96);
  LCD_WriteReg(0xC591, 0x87);
  LCD_WriteReg(0xC800, 0x73);
  LCD_WriteReg(0xC801, 0x71);

  LCD_WriteReg(0xD900, 0x6A);
  Delay_10us(20);

  LCD_WriteReg(0xE100, 0x09);
  LCD_WriteReg(0xE101, 0x0A);
  LCD_WriteReg(0xE102, 0x0E);
  LCD_WriteReg(0xE103, 0x0D);
  LCD_WriteReg(0xE104, 0x07);
  LCD_WriteReg(0xE105, 0x18);
  LCD_WriteReg(0xE106, 0x0D);
  LCD_WriteReg(0xE107, 0x0D);
  LCD_WriteReg(0xE108, 0x01);
  LCD_WriteReg(0xE109, 0x04);
  LCD_WriteReg(0xE10A, 0x05);
  LCD_WriteReg(0xE10B, 0x06);
  LCD_WriteReg(0xE10C, 0x0D);
  LCD_WriteReg(0xE10D, 0x22);
  LCD_WriteReg(0xE10E, 0x20);
  LCD_WriteReg(0xE10F, 0x05);

  LCD_WriteReg(0xE200, 0x09);
  LCD_WriteReg(0xE201, 0x0A);
  LCD_WriteReg(0xE202, 0x0E);
  LCD_WriteReg(0xE203, 0x0D);
  LCD_WriteReg(0xE204, 0x07);
  LCD_WriteReg(0xE205, 0x18);
  LCD_WriteReg(0xE206, 0x0D);
  LCD_WriteReg(0xE207, 0x0D);
  LCD_WriteReg(0xE208, 0x01);
  LCD_WriteReg(0xE209, 0x04);
  LCD_WriteReg(0xE20A, 0x05);
  LCD_WriteReg(0xE20B, 0x06);
  LCD_WriteReg(0xE20C, 0x0D);
  LCD_WriteReg(0xE20D, 0x22);
  LCD_WriteReg(0xE20E, 0x20);
  LCD_WriteReg(0xE20F, 0x05);

  LCD_WriteReg(0xC181, 0x66);

  LCD_WriteReg(0xC1A1, 0x08);
  LCD_WriteReg(0xC0A3, 0x1B);
  LCD_WriteReg(0xC481, 0x83);
  LCD_WriteReg(0xC592, 0x01);
  LCD_WriteReg(0xC5B1, 0xA9);

  LCD_WriteReg(0xCE80, 0x85);
  LCD_WriteReg(0xCE81, 0x03);
  LCD_WriteReg(0xCE82, 0x00);
  LCD_WriteReg(0xCE83, 0x84);
  LCD_WriteReg(0xCE84, 0x03);
  LCD_WriteReg(0xCE85, 0x00);

  LCD_WriteReg(0xCE86, 0x83);

  LCD_WriteReg(0xCE87, 0x03);
  LCD_WriteReg(0xCE88, 0x00);
  LCD_WriteReg(0xCE89, 0x82);
  LCD_WriteReg(0xCE8A, 0x03);
  LCD_WriteReg(0xCE8B, 0x00);

  LCD_WriteReg(0xCEA0, 0x38);
  LCD_WriteReg(0xCEA1, 0x02);
  LCD_WriteReg(0xCEA2, 0x03);
  LCD_WriteReg(0xCEA3, 0x21);
  LCD_WriteReg(0xCEA4, 0x00);
  LCD_WriteReg(0xCEA5, 0x00);
  LCD_WriteReg(0xCEA6, 0x00);
  LCD_WriteReg(0xCEA7, 0x38);
  LCD_WriteReg(0xCEA8, 0x01);
  LCD_WriteReg(0xCEA9, 0x03);
  LCD_WriteReg(0xCEAA, 0x22);
  LCD_WriteReg(0xCEAB, 0x00);
  LCD_WriteReg(0xCEAC, 0x00);
  LCD_WriteReg(0xCEAD, 0x00);

  LCD_WriteReg(0xCEB0, 0x38);
  LCD_WriteReg(0xCEB1, 0x00);
  LCD_WriteReg(0xCEB2, 0x03);
  LCD_WriteReg(0xCEB3, 0x23);
  LCD_WriteReg(0xCEB4, 0x00);
  LCD_WriteReg(0xCEB5, 0x00);
  LCD_WriteReg(0xCEB6, 0x00);
  LCD_WriteReg(0xCEB7, 0x30);
  LCD_WriteReg(0xCEB8, 0x00);
  LCD_WriteReg(0xCEB9, 0x03);
  LCD_WriteReg(0xCEBA, 0x24);
  LCD_WriteReg(0xCEBB, 0x00);
  LCD_WriteReg(0xCEBC, 0x00);
  LCD_WriteReg(0xCEBD, 0x00);

  LCD_WriteReg(0xCEC0, 0x30);
  LCD_WriteReg(0xCEC1, 0x01);
  LCD_WriteReg(0xCEC2, 0x03);
  LCD_WriteReg(0xCEC3, 0x25);
  LCD_WriteReg(0xCEC4, 0x00);
  LCD_WriteReg(0xCEC5, 0x00);
  LCD_WriteReg(0xCEC6, 0x00);
  LCD_WriteReg(0xCEC7, 0x30);
  LCD_WriteReg(0xCEC8, 0x02);
  LCD_WriteReg(0xCEC9, 0x03);
  LCD_WriteReg(0xCECA, 0x26);
  LCD_WriteReg(0xCECB, 0x00);
  LCD_WriteReg(0xCECC, 0x00);
  LCD_WriteReg(0xCECD, 0x00);

  LCD_WriteReg(0xCED0, 0x30);
  LCD_WriteReg(0xCED1, 0x03);
  LCD_WriteReg(0xCED2, 0x03);
  LCD_WriteReg(0xCED3, 0x27);
  LCD_WriteReg(0xCED4, 0x00);
  LCD_WriteReg(0xCED5, 0x00);
  LCD_WriteReg(0xCED6, 0x00);
  LCD_WriteReg(0xCED7, 0x30);
  LCD_WriteReg(0xCED8, 0x04);
  LCD_WriteReg(0xCED9, 0x03);
  LCD_WriteReg(0xCEDA, 0x28);
  LCD_WriteReg(0xCEDB, 0x00);
  LCD_WriteReg(0xCEDC, 0x00);
  LCD_WriteReg(0xCEDD, 0x00);

  LCD_WriteReg(0xCFC0, 0x00);
  LCD_WriteReg(0xCFC1, 0x00);
  LCD_WriteReg(0xCFC2, 0x00);
  LCD_WriteReg(0xCFC3, 0x00);
  LCD_WriteReg(0xCFC4, 0x00);
  LCD_WriteReg(0xCFC5, 0x00);
  LCD_WriteReg(0xCFC6, 0x00);
  LCD_WriteReg(0xCFC7, 0x00);
  LCD_WriteReg(0xCFC8, 0x00);
  LCD_WriteReg(0xCFC9, 0x00);

  LCD_WriteReg(0xCFD0, 0x00);

  LCD_WriteReg(0xCBC0, 0x00);
  LCD_WriteReg(0xCBC1, 0x00);
  LCD_WriteReg(0xCBC2, 0x00);
  LCD_WriteReg(0xCBC3, 0x00);
  LCD_WriteReg(0xCBC4, 0x04);
  LCD_WriteReg(0xCBC5, 0x04);
  LCD_WriteReg(0xCBC6, 0x04);
  LCD_WriteReg(0xCBC7, 0x04);
  LCD_WriteReg(0xCBC8, 0x04);
  LCD_WriteReg(0xCBC9, 0x04);
  LCD_WriteReg(0xCBCA, 0x00);
  LCD_WriteReg(0xCBCB, 0x00);
  LCD_WriteReg(0xCBCC, 0x00);
  LCD_WriteReg(0xCBCD, 0x00);
  LCD_WriteReg(0xCBCE, 0x00);

  LCD_WriteReg(0xCBD0, 0x00);
  LCD_WriteReg(0xCBD1, 0x00);
  LCD_WriteReg(0xCBD2, 0x00);
  LCD_WriteReg(0xCBD3, 0x00);
  LCD_WriteReg(0xCBD4, 0x00);
  LCD_WriteReg(0xCBD5, 0x00);
  LCD_WriteReg(0xCBD6, 0x00);
  LCD_WriteReg(0xCBD7, 0x00);
  LCD_WriteReg(0xCBD8, 0x00);
  LCD_WriteReg(0xCBD9, 0x04);
  LCD_WriteReg(0xCBDA, 0x04);
  LCD_WriteReg(0xCBDB, 0x04);
  LCD_WriteReg(0xCBDC, 0x04);
  LCD_WriteReg(0xCBDD, 0x04);
  LCD_WriteReg(0xCBDE, 0x04);

  LCD_WriteReg(0xCBE0, 0x00);
  LCD_WriteReg(0xCBE1, 0x00);
  LCD_WriteReg(0xCBE2, 0x00);
  LCD_WriteReg(0xCBE3, 0x00);
  LCD_WriteReg(0xCBE4, 0x00);
  LCD_WriteReg(0xCBE5, 0x00);
  LCD_WriteReg(0xCBE6, 0x00);
  LCD_WriteReg(0xCBE7, 0x00);
  LCD_WriteReg(0xCBE8, 0x00);
  LCD_WriteReg(0xCBE9, 0x00);

  LCD_WriteReg(0xCC80, 0x00);
  LCD_WriteReg(0xCC81, 0x00);
  LCD_WriteReg(0xCC82, 0x00);
  LCD_WriteReg(0xCC83, 0x00);
  LCD_WriteReg(0xCC84, 0x0C);
  LCD_WriteReg(0xCC85, 0x0A);
  LCD_WriteReg(0xCC86, 0x10);
  LCD_WriteReg(0xCC87, 0x0E);
  LCD_WriteReg(0xCC88, 0x03);
  LCD_WriteReg(0xCC89, 0x04);

  LCD_WriteReg(0xCC90, 0x00);
  LCD_WriteReg(0xCC91, 0x00);
  LCD_WriteReg(0xCC92, 0x00);
  LCD_WriteReg(0xCC93, 0x00);
  LCD_WriteReg(0xCC94, 0x00);
  LCD_WriteReg(0xCC95, 0x00);
  LCD_WriteReg(0xCC96, 0x00);
  LCD_WriteReg(0xCC97, 0x00);
  LCD_WriteReg(0xCC98, 0x00);
  LCD_WriteReg(0xCC99, 0x00);
  LCD_WriteReg(0xCC9A, 0x00);
  LCD_WriteReg(0xCC9B, 0x00);
  LCD_WriteReg(0xCC9C, 0x00);
  LCD_WriteReg(0xCC9D, 0x00);
  LCD_WriteReg(0xCC9E, 0x0B);

  LCD_WriteReg(0xCCA0, 0x09);
  LCD_WriteReg(0xCCA1, 0x0F);
  LCD_WriteReg(0xCCA2, 0x0D);
  LCD_WriteReg(0xCCA3, 0x01);
  LCD_WriteReg(0xCCA4, 0x02);
  LCD_WriteReg(0xCCA5, 0x00);
  LCD_WriteReg(0xCCA6, 0x00);
  LCD_WriteReg(0xCCA7, 0x00);
  LCD_WriteReg(0xCCA8, 0x00);
  LCD_WriteReg(0xCCA9, 0x00);
  LCD_WriteReg(0xCCAA, 0x00);
  LCD_WriteReg(0xCCAB, 0x00);
  LCD_WriteReg(0xCCAC, 0x00);
  LCD_WriteReg(0xCCAD, 0x00);
  LCD_WriteReg(0xCCAE, 0x00);

  LCD_WriteReg(0xCCB0, 0x00);
  LCD_WriteReg(0xCCB1, 0x00);
  LCD_WriteReg(0xCCB2, 0x00);
  LCD_WriteReg(0xCCB3, 0x00);
  LCD_WriteReg(0xCCB4, 0x0D);
  LCD_WriteReg(0xCCB5, 0x0F);
  LCD_WriteReg(0xCCB6, 0x09);
  LCD_WriteReg(0xCCB7, 0x0B);
  LCD_WriteReg(0xCCB8, 0x02);
  LCD_WriteReg(0xCCB9, 0x01);

  LCD_WriteReg(0xCCC0, 0x00);
  LCD_WriteReg(0xCCC1, 0x00);
  LCD_WriteReg(0xCCC2, 0x00);
  LCD_WriteReg(0xCCC3, 0x00);
  LCD_WriteReg(0xCCC4, 0x00);
  LCD_WriteReg(0xCCC5, 0x00);
  LCD_WriteReg(0xCCC6, 0x00);
  LCD_WriteReg(0xCCC7, 0x00);
  LCD_WriteReg(0xCCC8, 0x00);
  LCD_WriteReg(0xCCC9, 0x00);
  LCD_WriteReg(0xCCCA, 0x00);
  LCD_WriteReg(0xCCCB, 0x00);
  LCD_WriteReg(0xCCCC, 0x00);
  LCD_WriteReg(0xCCCD, 0x00);
  LCD_WriteReg(0xCCCE, 0x0E);

  LCD_WriteReg(0xCCD0, 0x10);
  LCD_WriteReg(0xCCD1, 0x0A);
  LCD_WriteReg(0xCCD2, 0x0C);
  LCD_WriteReg(0xCCD3, 0x04);
  LCD_WriteReg(0xCCD4, 0x03);
  LCD_WriteReg(0xCCD5, 0x00);
  LCD_WriteReg(0xCCD6, 0x00);
  LCD_WriteReg(0xCCD7, 0x00);
  LCD_WriteReg(0xCCD8, 0x00);
  LCD_WriteReg(0xCCD9, 0x00);
  LCD_WriteReg(0xCCDA, 0x00);
  LCD_WriteReg(0xCCDB, 0x00);
  LCD_WriteReg(0xCCDC, 0x00);
  LCD_WriteReg(0xCCDD, 0x00);
  LCD_WriteReg(0xCCDE, 0x00);

  LCD_WriteReg(0x3500, 0x00);
  LCD_WriteReg(0x3A00, 0x55);
  LCD_WriteReg(0x3600, 0xA0);

  LCD_WriteCmd(0x1100);
  Delay_1ms(1);

  LCD_WriteCmd(0x2900);
  Delay_1ms(1);

  LCD_WriteReg(0x2A00, 0x00);
  LCD_WriteReg(0x2A01, 0x00);
  LCD_WriteReg(0x2A02, 0x01);
  LCD_WriteReg(0x2A03, 0xDF);
  LCD_WriteReg(0x2B00, 0x00);
  LCD_WriteReg(0x2B01, 0x00);
  LCD_WriteReg(0x2B02, 0x03);
  LCD_WriteReg(0x2B03, 0x1F);

  LCD_WriteCmd(0x2C00);
  Delay_1ms(1);

  LCD_Clear(WHITE);
  LCD_TestColoBar();
  LCD_SetBackLight(BLIGHT_DEFAULT);
  Delay_1ms(5);

  return SUCCESS;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_Clear
**功能 : Clear Windows
**輸入 : Color
**輸出 : None
**使用 : LCD_Clear(BLACK);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_Clear( u16 Color )
{
  u32 Point = LCD_W*LCD_H;

  LCD_SetWindow(0, 0, LCD_W-1, LCD_H-1);

	while(Point--)
		LCD_WriteData(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_SetCursor
**功能 : Set Cursor
**輸入 : CoordiX, CoordiY
**輸出 : None
**使用 : LCD_SetCursor(StartX, StartY);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_SetCursor( u16 CoordiX, u16 CoordiY )
{
  LCD_WriteReg(0x2A00, Byte8H(CoordiX));
  LCD_WriteReg(0x2A01, Byte8L(CoordiX));
  LCD_WriteReg(0x2B00, Byte8H(CoordiY));
  LCD_WriteReg(0x2B01, Byte8L(CoordiY));

	LCD_WriteCmd(0x2C00);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_SetWindow
**功能 : Set Window
**輸入 : StartX, StartY, EndX, EndY
**輸出 : None
**使用 : LCD_SetWindow(X0, Y0, X1, Y1);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_SetWindow( u16 StartX, u16 StartY, u16 EndX, u16 EndY )
{
  LCD_WriteReg(0x2A00, Byte8H(StartX));
  LCD_WriteReg(0x2A01, Byte8L(StartX));
  LCD_WriteReg(0x2A02, Byte8H(EndX));
  LCD_WriteReg(0x2A03, Byte8L(EndX));

  LCD_WriteReg(0x2B00, Byte8H(StartY));
  LCD_WriteReg(0x2B01, Byte8L(StartY));
  LCD_WriteReg(0x2B02, Byte8H(EndY));
  LCD_WriteReg(0x2B03, Byte8L(EndY));

	LCD_WriteCmd(0x2C00);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_SetBackLight
**功能 : Set LCD BackLight
**輸入 : BackLight
**輸出 : None
**使用 : LCD_SetBackLight(BLIGHT_DEFAULT);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_SetBackLight( u16 BackLight )
{
	if(BackLight <= 0)
    LCD_LIG = BLIGHT_MIN;
	else if (BackLight >= BLIGHT_MAX)
    LCD_LIG = BLIGHT_MAX;
  else
    LCD_LIG = BackLight;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawPixel
**功能 : Draw a Pixel
**輸入 : CoordiX, CoordiY, Color
**輸出 : None
**使用 : LCD_DrawPixel(CoordiX, CoordiY, Color);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawPixel( u16 CoordiX, u16 CoordiY, u16 Color )
{
  LCD_SetWindow(CoordiX, CoordiY, CoordiX, CoordiY);
  LCD_WriteData(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawLineX
**功能 : Draw X-Axis Line
**輸入 : CoordiX, CoordiY, Length, Color
**輸出 : None
**使用 : LCD_DrawLine(CoordiX, CoordiY, Length, Color);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
{
  LCD_SetWindow(CoordiX, CoordiY, CoordiX+Length-1, CoordiY);

  while(Length--)
    LCD_WriteData(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawLineY
**功能 : Draw Y-Axis Line
**輸入 : CoordiX, CoordiY, Length, Color
**輸出 : None
**使用 : LCD_DrawLine(CoordiX, CoordiY, Length, Color);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
{
  LCD_SetWindow(CoordiX, CoordiY, CoordiX, CoordiY+Length-1);

  while(Length--)
    LCD_WriteData(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawRectangle
**功能 : Draw Rectangle
**輸入 : CoordiX, CoordiY, Length, Width, Color
**輸出 : None
**使用 : LCD_DrawRectangle(CoordiX, CoordiY, Width, Height, Color)
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawRectangle( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color )
{
  LCD_DrawLineX(CoordiX,         CoordiY,          Width,   Color);
  LCD_DrawLineX(CoordiX,         CoordiY+Height-1, Width,   Color);
  LCD_DrawLineY(CoordiX,         CoordiY,          Height,  Color);
  LCD_DrawLineY(CoordiX+Width-1, CoordiY,          Height,  Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawRectangleFill
**功能 : Draw Rectangle
**輸入 : CoordiX, CoordiY, Length, Width, Color
**輸出 : None
**使用 : LCD_DrawRectangleFill(CoordiX, CoordiY, Width, Height, Color);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawRectangleFill( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color )
{
  u32 Point = Width*Height;

  LCD_SetWindow(CoordiX, CoordiY, CoordiX+Width-1, CoordiY+Height-1);

  while(Point--)
    LCD_WriteData(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawCircle
**功能 : Draw Circle
**輸入 : CoordiX, CoordiY, Radius, Color
**輸出 : None
**使用 : LCD_DrawCircle(CoordiX, CoordiY, Radius, Color);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawCircle( u16 CoordiX, u16 CoordiY, u16 Radius, u16 Color )
{
	int a,b;
	int di;

	a=0;
	b=Radius;
	di=3-(Radius<<1);

	while(a<=b) {
		LCD_DrawPixel(CoordiX-b, CoordiY-a, Color); //3
		LCD_DrawPixel(CoordiX+b, CoordiY-a, Color); //0
		LCD_DrawPixel(CoordiX-a, CoordiY+b, Color); //1
		LCD_DrawPixel(CoordiX-b, CoordiY-a, Color); //7
		LCD_DrawPixel(CoordiX-a, CoordiY-b, Color); //2
		LCD_DrawPixel(CoordiX+b, CoordiY+a, Color); //4
		LCD_DrawPixel(CoordiX+a, CoordiY-b, Color); //5
		LCD_DrawPixel(CoordiX+a, CoordiY+b, Color); //6
		LCD_DrawPixel(CoordiX-b, CoordiY+a, Color);
		a++;
		// 使用Bresenham算法畫圓
		if(di<0)
			di += 4*a+6;
		else {
			di+=10+4*(a-b);
			b--;
		}
		LCD_DrawPixel(CoordiX+a, CoordiY+b, Color);
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawPicture
**功能 : Draw Picture
**輸入 : CoordiX, CoordiY, Length, Width, Pic
**輸出 : None
**使用 : LCD_DrawPicture(CoordiX, CoordiY, Width, Height, Pic);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawPicture( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, uc8 *Pic )
{
  u16* readPixel = (u16*)Pic;
  u32 i = 0, j = Height*Width;

  LCD_SetWindow(CoordiX, CoordiY, CoordiX+Width-1, CoordiY+Height-1);

  for(i=0; i<j; i++)
    LCD_WriteData(readPixel[i]);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_PutChar1206
**功能 : Put Char
**輸入 : CoordiX, CoordiY, ChWord, FontColor, BackColor
**輸出 : None
**使用 : LCD_PutChar1206(x, y, "C", WHITE, BLACK)
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_PutChar1206( u16 CoordiX, u16 CoordiY, u8* ChWord, u16 FontColor, u16 BackColor )
{
	u8 Tmp_Char = 0;
	u16 i = 0, j = 0;

	for(i=0; i<12; i++) {
		Tmp_Char = ASCII_12x6[*ChWord-32][i];
		for(j=0; j<6; j++) {
			if(((Tmp_Char>>j)&0x01) == 0x01)
				LCD_DrawPixel(CoordiX+j, CoordiY+i, FontColor);	// 字符顏色
			else
				LCD_DrawPixel(CoordiX+j, CoordiY+i, BackColor);	// 背景顏色
		}
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_PutChar1608
**功能 : Put Char
**輸入 : CoordiX, CoordiY, ChWord, FontColor, BackColor
**輸出 : None
**使用 : LCD_PutChar1608(x, y, "C", WHITE, BLACK)
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_PutChar1608( u16 CoordiX, u16 CoordiY, u8* ChWord, u16 FontColor, u16 BackColor )
{
	u8 Tmp_Char = 0;
	u16 i = 0, j = 0;

	for(i=0; i<16; i++) {
		Tmp_Char = ASCII_16x8[*ChWord-32][i];
		for(j=0; j<8; j++) {
			if(((Tmp_Char>>(7-j))&0x01) == 0x01)
				LCD_DrawPixel(CoordiX+j, CoordiY+i, FontColor);	// 字符顏色
			else
				LCD_DrawPixel(CoordiX+j, CoordiY+i, BackColor);	// 背景顏色
		}
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_PutChar1608_
**功能 : Put Char
**輸入 : CoordiX, CoordiY, ChWord, FontColor, BackColor
**輸出 : None
**使用 : LCD_PutChar1608(x, y, "C", WHITE, BLACK)
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_PutChar1608_( u16 CoordiX, u16 CoordiY, u8* ChWord, u16 FontColor, u16 BackColor )
{
	u8 Tmp_Char = 0;
	u16 i = 0, j = 0;

	for(i=0; i<16; i++) {
		Tmp_Char = ASCII_16x8_[*ChWord-32][i];
		for(j=0; j<8; j++) {
			if(((Tmp_Char>>j)&0x01) == 0x01)
				LCD_DrawPixel(CoordiX+j, CoordiY+i, FontColor);	// 字符顏色
			else
				LCD_DrawPixel(CoordiX+j, CoordiY+i, BackColor);	// 背景顏色
		}
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_PutStr
**功能 : Put String
**輸入 : CoordiX, CoordiY, ChWord, FontStyle, FontColor, BackColor
**輸出 : None
**使用 : LCD_PutStr(10, 10, (u8*)"Hello World !!!", ASCII1608, WHITE, BLACK);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_PutStr( u16 CoordiX, u16 CoordiY, u8 *ChWord, u8 FontStyle, u16 FontColor, u16 BackColor )
{
	u16 OffsetX = 0;

	switch(FontStyle) {
		case ASCII1206:
			while(*ChWord) {
				LCD_PutChar1206(CoordiX+OffsetX, CoordiY, ChWord, FontColor, BackColor);
				ChWord++;
				OffsetX += 6;
			}
			break;
		case ASCII1608:
			while(*ChWord) {
				LCD_PutChar1608(CoordiX+OffsetX, CoordiY, ChWord, FontColor, BackColor);
				ChWord++;
				OffsetX += 8;
			}
			break;
		case ASCII1608_:
			while(*ChWord) {
				LCD_PutChar1608_(CoordiX+OffsetX, CoordiY, ChWord, FontColor, BackColor);
				ChWord++;
				OffsetX += 8;
			}
			break;
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_PutNum
**功能 : Put Number
**輸入 : CoordiX, CoordiY, Type, Length, NumData, FontColor, BackColor
**輸出 : None
**使用 : LCD_PutNum(CoordiX, CoordiY, Type_D, Length, NumData, WHITE, BLACK);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_PutNum( u16 CoordiX, u16 CoordiY, u8 Type, u8 Length, u32 NumData, u16 FontColor, u16 BackColor )
{
	u8 TmpNumber[16] = {0};

	Str_NumToChar(Type, Length, TmpNumber, NumData);
	LCD_PutStr(CoordiX, CoordiY, TmpNumber, ASCII1608, FontColor, BackColor);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_TestColoBar
**功能 : Draw Color Bar
**輸入 : None
**輸出 : None
**使用 : LCD_TestColoBar();
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_TestColoBar( void )
{
  u32 i = 0, j = 0;
  u16 drawColor[20] = {
    WHITE,
    RED,
    GREEN,
    BLUE,
    MAGENTA,
    GRED,
    GBLUE,
    BRED,
    BROWN,
    BRRED,
    CYAN,
    GRAY,
    YELLOW,
    DARKBLUE,
    LIGHTBLUE,
    GRAYBLUE,
    LIGHTGREEN,
    LGRAY,
    LGRAYBLUE,
    LBBLUE
  };

	LCD_SetWindow(0, 0, LCD_W-1, LCD_H-1);

  for(i=0; i<20; i++) {
    j = 24*LCD_W; // LCD_H/20 = 480/20 = 24
    while(j--)
      LCD_WriteData(drawColor[i]);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
