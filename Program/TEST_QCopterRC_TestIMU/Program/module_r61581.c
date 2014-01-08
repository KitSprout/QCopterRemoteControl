/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "module_r61581.h"
#include "module_fontlib.h"
#include "algorithm_mathUnit.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LCD_RST PCO(7)      // Reset
#define LCD_LIG TIM3->CCR1	// Back Light
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : R61581_Config
**功能 : RA8875 設定 & 配置
**輸入 : None
**輸出 : None
**使用 : RA8875_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void R61581_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  FSMC_NORSRAMInitTypeDef FSMC_InitStruct;
  FSMC_NORSRAMTimingInitTypeDef ReadWrite_TimingInitStruct; 
	FSMC_NORSRAMTimingInitTypeDef Write_TimingInitStruct;

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

  R61581_BLigConfig();

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

  ReadWrite_TimingInitStruct.FSMC_AddressSetupTime = 0x01;
  ReadWrite_TimingInitStruct.FSMC_AddressHoldTime = 0x00;
  ReadWrite_TimingInitStruct.FSMC_DataSetupTime = 0x0f;
  ReadWrite_TimingInitStruct.FSMC_BusTurnAroundDuration = 0x00;
  ReadWrite_TimingInitStruct.FSMC_CLKDivision = 0x00;
  ReadWrite_TimingInitStruct.FSMC_DataLatency = 0x00;
  ReadWrite_TimingInitStruct.FSMC_AccessMode = FSMC_AccessMode_A;

  Write_TimingInitStruct.FSMC_AddressSetupTime = 0x01;
  Write_TimingInitStruct.FSMC_AddressHoldTime = 0x00;
  Write_TimingInitStruct.FSMC_DataSetupTime = 0x02;
  Write_TimingInitStruct.FSMC_BusTurnAroundDuration = 0x00;
  Write_TimingInitStruct.FSMC_CLKDivision = 0x00;
  Write_TimingInitStruct.FSMC_DataLatency = 0x00;
  Write_TimingInitStruct.FSMC_AccessMode = FSMC_AccessMode_A;

  FSMC_InitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_InitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_InitStruct.FSMC_MemoryType =FSMC_MemoryType_SRAM;
  FSMC_InitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_InitStruct.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
  FSMC_InitStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_InitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_InitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_InitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_InitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_InitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_InitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
  FSMC_InitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_InitStruct.FSMC_ReadWriteTimingStruct = &ReadWrite_TimingInitStruct;
  FSMC_InitStruct.FSMC_WriteTimingStruct = &Write_TimingInitStruct;

  FSMC_NORSRAMInit(&FSMC_InitStruct);
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : R61581_BLigConfig
**功能 : 背光 IO 配置
**輸入 : None
**輸出 : None
**使用 : R61581_BLigConfig();
**=====================================================================================================*/
/*=====================================================================================================*/
void R61581_BLigConfig( void )
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
  TIM_ARRPreloadConfig(TIM3, ENABLE);                         // 致能 TIM3 重載寄存器 ARR
  TIM_Cmd(TIM3, ENABLE);                                      // 致能 TIM3

  LCD_LIG = 0;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_WriteCmd
**功能 : Write Command or Address
**輸入 : WriteCmd
**輸出 : None
**使用 : 
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
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_WriteData( u16 WriteData )
{
  LCD_RAM = WriteData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_WriteReg
**功能 : Write Register
**輸入 : WriteAddr, WriteData
**輸出 : None
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_WriteReg( u16 WriteAddr, u16 WriteData )
{
  LCD_REG = WriteAddr;
  LCD_RAM = WriteData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_WriteColor
**功能 : Write Color
**輸入 : Color
**輸出 : None
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_WriteColor( u16 Color )
{
  LCD_RAM = Color;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : R61581_Init
**功能 : R61581 Init
**輸入 : None
**輸出 : None
**使用 : R61581_Init();
**=====================================================================================================*/
/*=====================================================================================================*/
void R61581_Init( void )
{
  // Reset
	LCD_RST = 0;
	Delay_1ms(15);
	LCD_RST = 1;
	Delay_1ms(5);

  Delay_1ms(50);
  LCD_WriteReg(0x00, 0x01);
  Delay_1ms(50);

  LCD_WriteCmd(0xB0);   // {setc, [107], W, 0x000B0}
  LCD_WriteData(0x00);  // {setp, [104], W, 0x00000}

  LCD_WriteCmd(0xB3);
  LCD_WriteData(0x02);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);

  LCD_WriteCmd(0xB4);
  LCD_WriteData(0x00);

  LCD_WriteCmd(0xC0);
  LCD_WriteData(0x13);  //
  LCD_WriteData(0x3B);  // 480
  LCD_WriteData(0x00);
  LCD_WriteData(0x03);  // 02
  LCD_WriteData(0x00);
  LCD_WriteData(0x01);
  LCD_WriteData(0x00);
  LCD_WriteData(0x43);

  LCD_WriteCmd(0xC1);
  LCD_WriteData(0x08);  // 08
  LCD_WriteData(0x10);  // CLOCK//0x12
  LCD_WriteData(0x08);
  LCD_WriteData(0x08);

  LCD_WriteCmd(0xC4);
  LCD_WriteData(0x11);
  LCD_WriteData(0x07);
  LCD_WriteData(0x03);
  LCD_WriteData(0x03);

  // Gamma For 3.5inch
  LCD_WriteCmd(0xC8);   // Gamma setting
  LCD_WriteData(0x00);
  LCD_WriteData(0x25);
  LCD_WriteData(0x21);
  LCD_WriteData(0x05);
  LCD_WriteData(0x00);
  LCD_WriteData(0x0A);
  LCD_WriteData(0x65);
  LCD_WriteData(0x25);
  LCD_WriteData(0x77);
  LCD_WriteData(0x50);
  LCD_WriteData(0x0F);
  LCD_WriteData(0x00);

  LCD_WriteCmd(0x2A);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);
  LCD_WriteData(0x01);
  LCD_WriteData(0x3F);  // 320

  LCD_WriteCmd(0x2B);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);
  LCD_WriteData(0x01);
  LCD_WriteData(0xDF);  // 480

  LCD_WriteCmd(0x35);
  LCD_WriteData(0x00);

  LCD_WriteCmd(0x36);
  LCD_WriteData(0x31);

  LCD_WriteCmd(0x3A);
  LCD_WriteData(0x55);

  LCD_WriteCmd(0x44);
  LCD_WriteData(0x00);
  LCD_WriteData(0x01);
  LCD_WriteCmd(0x2C);
  LCD_WriteCmd(0x11);

  Delay_1ms(150);

  LCD_WriteCmd(0xD0);
  LCD_WriteData(0x07);
  LCD_WriteData(0x07);
  LCD_WriteData(0x1E);
  LCD_WriteData(0x03);  // LCD_WriteData(0x0703);

  LCD_WriteCmd(0xD1);
  LCD_WriteData(0x03);
  LCD_WriteData(0x52);  // VCM
  LCD_WriteData(0x10);  // VDV

  LCD_WriteCmd(0xD2);
  LCD_WriteData(0x03);
  LCD_WriteData(0x24);

  LCD_WriteCmd(0xB0);   // {setc, [107], W, 0x000B0}
  LCD_WriteData(0x00);  // {setp, [104], W, 0x00000}

  LCD_WriteCmd(0x29);

  Delay_1ms(10);

  LCD_WriteReg(0x36, 0x31);

  LCD_Clear(BLACK);
  LCD_SetBackLight(BLIGHT_DEFAULT);
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
  u32 Area = LCD_W*LCD_H;

  LCD_SetWindow(0, 0, LCD_W-1, LCD_H-1);

	while(Area--)
		LCD_WriteColor(Color);
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
	LCD_WriteCmd(0x2A);
  LCD_WriteData(Byte8H(CoordiX));
	LCD_WriteData(Byte8L(CoordiX));
	LCD_WriteCmd(0x2B);
  LCD_WriteData(Byte8H(CoordiY));
	LCD_WriteData(Byte8L(CoordiY));
	LCD_WriteCmd(0x2C);
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
	LCD_WriteCmd(0x2A);
  LCD_WriteData(Byte8H(StartX));
	LCD_WriteData(Byte8L(StartX));
  LCD_WriteData(Byte8H(EndX));
	LCD_WriteData(Byte8L(EndX));
	LCD_WriteCmd(0x2B);
  LCD_WriteData(Byte8H(StartY));
	LCD_WriteData(Byte8L(StartY));
  LCD_WriteData(Byte8H(EndY));
	LCD_WriteData(Byte8L(EndY));
	LCD_WriteCmd(0x2C);
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
  LCD_SetCursor(CoordiX, CoordiY);
  LCD_WriteColor(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawLine
**功能 : Draw Line
**輸入 : StartX, StartY, EndX, EndY, Color
**輸出 : None
**使用 : LCD_DrawLine(StartX, StartY, EndX, EndY, Color)
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawLine( u16 StartX, u16 StartY, u16 EndX, u16 EndY, u32 Color )
{
	u16 i;
	s16 DeltaX, DeltaY;
	double Slope;

	DeltaX = EndX - StartX;
	DeltaY = EndY - StartY;

	// 計算 Slope
	if(DeltaX == 0)
		Slope = 0;
	else
		Slope = (double)DeltaY/(double)DeltaX;

	DeltaX = fabs(DeltaX);
	DeltaY = fabs(DeltaY);

	// 畫線
	if(EndX<StartX) {
		if(Slope<0) {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					LCD_DrawPixel(EndX+i, EndY+(s16)(((double)i*Slope)-0.5), Color);
			}
			else {
				for(i=0; i<=DeltaY; i++)
					LCD_DrawPixel(EndX-(s16)(((double)i/Slope)-0.5), EndY-i, Color);
			}
		}
		else {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					LCD_DrawPixel(EndX+i, EndY+(s16)(((double)i*Slope)+0.5), Color);
			}
			else {
				for(i=0; i<=DeltaY; i++)
					LCD_DrawPixel(EndX+(s16)(((double)i/Slope)+0.5), EndY+i, Color);
			}
		}
	}
	else if(EndX==StartX) {
		if(EndY>StartY) {
			for(i=0; i<=DeltaY; i++)
				LCD_DrawPixel(StartX, StartY+i, Color);
		}
		else {
			for(i=0; i<=DeltaY; i++)
				LCD_DrawPixel(EndX, EndY+i, Color);
		}
	}
	else {
		if(Slope<0) {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					LCD_DrawPixel(StartX+i, StartY+(s16)(((double)i*Slope)-0.5), Color);
			}
			else {
				for(i=0; i<=DeltaY; i++)
					LCD_DrawPixel(StartX-(s16)(((double)i/Slope)-0.5), StartY-i, Color);
			}
		}
		else {
			if(DeltaX>DeltaY) {
				for(i=0; i<=DeltaX; i++)
					LCD_DrawPixel(StartX+i, StartY+(s16)(((double)i*Slope)+0.5), Color);
			}
			else {
				for(i=0; i<=DeltaY; i++)
					LCD_DrawPixel(StartX+(s16)(((double)i/Slope)+0.5), StartY+i, Color);
			}
		}
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawLineX
**功能 : Draw X-Axis Line
**輸入 : CoordiX, CoordiY, Length, Color
**輸出 : None
**使用 : LCD_DrawLineX(CoordiX, CoordiY, Length, Color)
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
{
  LCD_SetWindow(CoordiX, CoordiY, CoordiX+Length-1, CoordiY);

  while(Length--)
    LCD_WriteColor(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawLineY
**功能 : Draw Y-Axis Line
**輸入 : CoordiX, CoordiY, Length, Color
**輸出 : None
**使用 : LCD_DrawLineY(CoordiX, CoordiY, Length, Color)
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
{
  LCD_SetWindow(CoordiX, CoordiY, CoordiX, CoordiY+Length-1);

  while(Length--)
    LCD_WriteColor(Color);
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
  LCD_DrawLineX(CoordiX,         CoordiY,          Width,    Color);
  LCD_DrawLineX(CoordiX,         CoordiY+Height-1, Width,    Color);
  LCD_DrawLineY(CoordiX,         CoordiY+1,        Height-2, Color);
  LCD_DrawLineY(CoordiX+Width-1, CoordiY+1,        Height-2, Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawRectangleFill
**功能 : Draw Rectangle
**輸入 : CoordiX, CoordiY, Length, Width, Color
**輸出 : None
**使用 : LCD_DrawRectangleFill(CoordiX, CoordiY, Width, Height, Color)
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_DrawRectangleFill( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color )
{
  u32 Area = Width*Height;

  LCD_SetWindow(CoordiX, CoordiY, CoordiX+Width-1, CoordiY+Height-1);

	while(Area--)
		LCD_WriteColor(Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_DrawCircle
**功能 : Draw Circle
**輸入 : CoordiX, CoordiY, Radius, Color
**輸出 : None
**使用 : LCD_DrawCircle(CoordiX, CoordiY, Radius, Color)
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
    LCD_WriteColor(readPixel[i]);
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
void LCD_PutChar1206( u16 CoordiX, u16 CoordiY, u8* ChWord, u16 FontColor, u16 BackColor )
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
void LCD_PutChar1608( u16 CoordiX, u16 CoordiY, u8* ChWord, u16 FontColor, u16 BackColor )
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
void LCD_PutChar1608_( u16 CoordiX, u16 CoordiY, u8* ChWord, u16 FontColor, u16 BackColor )
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
**輸入 : CoordiX, CoordiY, ChWord, Font
**輸出 : None
**使用 : LCD_PutStr(10, 10, (u8*)"TFT LCD TEST ... ", FontSyle, FontColor, BackColor);
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
**輸入 : oordiX, CoordiY, Type, Length, NumData, FontColor, BackColor
**輸出 : None
**使用 : LCD_PutNum(CoordiX, CoordiY, Type_D, Length, NumData, u8 FontStyle, u16 FontColor, u16 BackColor);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_PutNum( u16 CoordiX, u16 CoordiY, u8 Type, u8 Length, u32 NumData, u8 FontStyle, u16 FontColor, u16 BackColor )
{
	u8 TmpNumber[16] = {0};

	Str_NumToChar(Type, Length, TmpNumber, NumData);
	LCD_PutStr(CoordiX, CoordiY, TmpNumber, FontStyle, FontColor, BackColor);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_TestColoBar
**功能 : Draw Color Bar
**輸入 : None
**輸出 : None
**使用 : LCD_TestColoBar(0, 0, 480, 320);
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_TestColoBar( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height )
{
  #define ColorNum 20

  u16 drawColor[ColorNum] = {
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
  u32 i = 0, j = 0;
  u16 barH = (u16)((Height*Width)/ColorNum);

	LCD_SetWindow(CoordiX, CoordiY, CoordiX + Width-1, CoordiY + Height-1);

  for(i=0; i<ColorNum; i++) {
    j = barH;
    while(j--)
      LCD_WriteColor(drawColor[i]);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
