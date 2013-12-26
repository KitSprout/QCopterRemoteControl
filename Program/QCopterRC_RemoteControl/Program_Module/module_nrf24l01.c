/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_spi.h"
#include "module_nrf24l01.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define NRF_CSN   PAO(15) // PA15
#define NRF_CE    PBO(6)  // PB6
#define NRF_IRQ   PBI(7)  // PB7

#define LED_R   PCO(15)
#define LED_G   PCO(14)
#define LED_B   PCO(13)
#define LED_Y   PEO(6)
/*=====================================================================================================*/
/*=====================================================================================================*/
u8 TxBuf[TxBufSize] = {0};
u8 RxBuf[RxBufSize] = {0};

u8 TX_ADDRESS[TX_ADR_WIDTH] = { 0x34,0x43,0x10,0x10,0x01 };   // 定義一個靜態發送地址
u8 RX_ADDRESS[RX_ADR_WIDTH] = { 0x34,0x43,0x10,0x10,0x01 };
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF24L01_Config
**功能 : nRF24L01 配置 & 設定
**輸入 : None
**輸出 : None
**使用 : nRF24L01_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void nRF24L01_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI3);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI3);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn; //EXTI9_5_IRQn
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	/* CSN PA15 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	/* CE PB6 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	/* IRQ PB7 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
//  /* IRQ PB7 */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStruct);
	/* SCK PB3  */  /* MISO PB4  */  /* MOSI PB5  */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* IRQ EXTI */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7);
	EXTI_InitStruct.EXTI_Line = EXTI_Line7;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	NRF_CSN = 1;

  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // 雙線全雙工
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // 主模式
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // 數據大小8位
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;                           // 時鐘極性，空閒時為低
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;                         // 第1個邊沿有效，上升沿為采樣時刻
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // NSS信號由軟件產生
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;   // 8分頻，9MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // 高位在前
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(nRF_SPI, &SPI_InitStruct);
	SPI_Cmd(nRF_SPI, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_Recv_IRQ
**功能 : 接收資料中斷
**輸入 : None
**輸出 : None
**使用 : nRF_Recv_IRQ();
**=====================================================================================================*/
/*=====================================================================================================*/
void nRF_Recv_IRQ( void )
{
	u8 Sta = 0;

	NRF_CE = 0;
	Sta = nRF_ReadReg(STATUS);
	if(Sta&RX_DR) {
		nRF_WriteReg(NRF_WRITE+STATUS, Sta);
		nRF_ReadBuf(RD_RX_PLOAD, RxBuf, RX_PLOAD_WIDTH);
		nRF_WriteReg(FLUSH_RX, NOP);
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_WriteReg
**功能 : 寫暫存器
**輸入 : WriteAddr, WriteData
**輸出 : None
**使用 : nRF_WriteReg(NRF_WRITE+EN_AA, 0x01);
**=====================================================================================================*/
/*=====================================================================================================*/
void nRF_WriteReg( u8 WriteAddr, u8 WriteData )
{
  NRF_CE = 0;
  NRF_CSN = 0;
  SPI_WriteByte(nRF_SPI, WriteAddr);
  SPI_WriteByte(nRF_SPI, WriteData);
  NRF_CSN = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_ReadReg
**功能 : 讀暫存器
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : nRF_ReadReg(STATUS);
**=====================================================================================================*/
/*=====================================================================================================*/
u8 nRF_ReadReg( u8 ReadAddr )
{
  u8 ReadData;

  NRF_CE = 0;
  NRF_CSN = 0;
  SPI_WriteByte(nRF_SPI, ReadAddr);
  ReadData = SPI_ReadByte(nRF_SPI);
  NRF_CSN = 1;

  return ReadData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_WriteBuf
**功能 : 連續寫暫存器
**輸入 : WriteAddr, WriteBuf, Bytes
**輸出 : None
**使用 : nRF_WriteBuf(NRF_WRITE+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
**=====================================================================================================*/
/*=====================================================================================================*/
void nRF_WriteBuf( u8 WriteAddr, u8 *WriteBuf, u8 Bytes )
{
  u8 i;

  NRF_CE = 0;
  NRF_CSN = 0;

  SPI_WriteByte(nRF_SPI, WriteAddr);

  for(i=0; i<Bytes; i++)
    SPI_WriteByte(nRF_SPI, WriteBuf[i]);

  NRF_CSN = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_ReadBuf
**功能 : 連續讀暫存器
**輸入 : ReadAddr, ReadBuf, Bytes
**輸出 : None
**使用 : nRF_ReadBuf(TX_ADDR, CheckBuf, 5);
**=====================================================================================================*/
/*=====================================================================================================*/
void nRF_ReadBuf( u8 ReadAddr, u8 *ReadBuf, u8 Bytes )
{
  u8 i = 0;

  NRF_CE = 0;
  NRF_CSN = 0;

  SPI_WriteByte(nRF_SPI, ReadAddr);

  for(i=0; i<Bytes; i++)
    ReadBuf[i] = SPI_ReadByte(nRF_SPI);

  NRF_CSN = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_RX_Mode
**功能 : 轉成接收模式
**輸入 : None
**輸出 : None
**使用 : nRF_RX_Mode();
**=====================================================================================================*/
/*=====================================================================================================*/
void nRF_RX_Mode( void )
{
  NRF_CE = 0;
  nRF_WriteBuf(NRF_WRITE+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);   // 寫 RX 節點地址
  nRF_WriteReg(NRF_WRITE+EN_AA, 0x01);              // 使能通道0的自動應答
  nRF_WriteReg(NRF_WRITE+EN_RXADDR, 0x01);          // 使能通道0的接收地址
  nRF_WriteReg(NRF_WRITE+RF_CH, CHANAL);            // 設置 RF 通信頻率
  nRF_WriteReg(NRF_WRITE+RX_PW_P0, RX_PLOAD_WIDTH); // 選擇通道0的有效數據寬度
  nRF_WriteReg(NRF_WRITE+RF_SETUP, 0x0f);           // 設置 TX 發射參數, 0db增益, 2Mbps, 低噪聲增益開啟
  nRF_WriteReg(NRF_WRITE+CONFIG, 0x0f);             // 配置基本工作模式的參數; PWR_UP, EN_CRC, 16BIT_CRC, 接收模式
  NRF_CE = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_TX_Mode
**功能 : 轉成發射模式
**輸入 : None
**輸出 : None
**使用 : nRF_TX_Mode();
**=====================================================================================================*/
/*=====================================================================================================*/
void nRF_TX_Mode( void )
{
  NRF_CE = 0;
  nRF_WriteBuf(NRF_WRITE+TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 寫 TX 節點地址
  nRF_WriteBuf(NRF_WRITE+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH); // 設置 TX 節點地址, 主要為了使能ACK
  nRF_WriteReg(NRF_WRITE+EN_AA, 0x01);      // 使能通道0的自動應答
  nRF_WriteReg(NRF_WRITE+EN_RXADDR, 0x01);  // 使能通道0的接收地址
  nRF_WriteReg(NRF_WRITE+SETUP_RETR, 0x05); // 設置自動重發間隔時間: 250us + 86us; 最大自動重發次數: 5 次
  nRF_WriteReg(NRF_WRITE+RF_CH, CHANAL);    // 設置 RF 通道為CHANAL
  nRF_WriteReg(NRF_WRITE+RF_SETUP, 0x0f);   // 設置 TX 發射參數, 0db增益, 2Mbps, 低噪聲增益開啟
  nRF_WriteReg(NRF_WRITE+CONFIG, 0x0e);     // 配置基本工作模式的參數; PWR_UP, EN_CRC, 16BIT_CRC, 發射模式, 開啟所有中斷
  NRF_CE = 1;

  Delay_1us(12);  // CE 要拉高一段時間才進入發送模式
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_Check
**功能 : nRF24L01 檢測
**輸入 : None
**輸出 : Status
**使用 : Sta = nRF_Check();
**=====================================================================================================*/
/*=====================================================================================================*/
u8 nRF_Check( void )
{
  u8 i = 0;
  u8 SendBuf[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
  u8 RecvBuf[5] = {0};

  nRF_WriteBuf(NRF_WRITE+TX_ADDR, SendBuf, 5);
  nRF_ReadBuf(TX_ADDR, RecvBuf, 5);

  for(i=0; i<5; i++)
    if(RecvBuf[i]!=SendBuf[i])  break;

  return (i==5) ? SUCCESS : ERROR;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_Tx_Data
**功能 : 傳送資料
**輸入 : *TxBuf
**輸出 : Status
**使用 : nRF_Tx_Data(TxBuf);
**=====================================================================================================*/
/*=====================================================================================================*/
u8 nRF_Tx_Data( u8 *TxBuf )
{
  u8 Sta;

  NRF_CE = 0;
  nRF_WriteBuf(WR_TX_PLOAD, TxBuf, TX_PLOAD_WIDTH);
  NRF_CE = 1;

  while(NRF_IRQ!=0);
  Sta = nRF_ReadReg(STATUS);
  nRF_WriteReg(NRF_WRITE+STATUS, Sta);
  nRF_WriteReg(FLUSH_TX, NOP);

  if(Sta&MAX_RT)
    return MAX_RT;
  else if(Sta&TX_DS)
    return TX_DS;
  else
    return ERROR;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : nRF_Rx_Data
**功能 : 接收資料
**輸入 : *RxBuf
**輸出 : Status
**使用 : nRF_Tx_Data(TxBuf);
**=====================================================================================================*/
/*=====================================================================================================*/
u8 nRF_Rx_Data( u8 *RxBuf )
{
  u8 Sta;

  NRF_CE = 1;
  while(NRF_IRQ!=0);
  NRF_CE = 0;

  Sta = nRF_ReadReg(STATUS);
  nRF_WriteReg(NRF_WRITE+STATUS, Sta);

  if(Sta&RX_DR) {
    nRF_ReadBuf(RD_RX_PLOAD, RxBuf, RX_PLOAD_WIDTH);
    nRF_WriteReg(FLUSH_RX, NOP);
    return RX_DR;
  }
  else
    return ERROR;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
