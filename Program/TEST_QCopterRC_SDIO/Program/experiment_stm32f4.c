/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_usart.h"
#include "stm32f4_sdio.h"
#include "module_rs232.h"
#include "module_r61581.h"
#include "algorithm_string.h"
#include "ff.h"
#include "diskio.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define KEY_RP  PAI(8)
#define KEY_RR  PDI(6)
#define KEY_RL  PDI(3)

#define KEY_LP  PAI(1)
#define KEY_LR  PBI(2)
#define KEY_LL  PAI(0)

#define KEY_PP  PEI(1)
#define KEY_PR  PEI(0)
#define KEY_PL  PEI(2)

#define KEY_S1  PEI(3)
#define KEY_S2  PEI(4)
#define KEY_S3  PEI(5)

#define LED_R   PCO(15)
#define LED_G   PCO(14)
#define LED_B   PCO(13)
#define LED_Y   PEO(6)
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
FATFS FatFs;
FRESULT res;
FILINFO finfo;
DIR dirs;
FIL file;

int main( void )
{
  u32 i = 0;
  u8 FileNum = 0;
  u8 ReadBuf[128] = {0};
  u8 WriteData[50] = "ABCDEFG";

  SystemInit();
  GPIO_Config();
  RS232_Config();
  R61581_Config();
  R61581_Init();

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
  LED_Y = 1;

  LED_R = 0;
  LCD_Clear(BLACK);

  // SD Card Init Info
  #define Axis_X 10
  #define Axis_Y 0
  LCD_PutStr(Axis_X, Axis_Y+16*0, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*1, (u8*)" SDIO SD Fatfs demo",     ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*2, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*3, (u8*)" SD Init ... ", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)" \r\n");
  RS232_SendStr(USART2, (u8*)"----------------------\r\n");
  RS232_SendStr(USART2, (u8*)"----------------------\r\n");
  RS232_SendStr(USART2, (u8*)" SDIO SD FatFs demo\r\n");
  RS232_SendStr(USART2, (u8*)"----------------------\r\n");
  RS232_SendStr(USART2, (u8*)"----------------------\r\n\r\n");
  RS232_SendStr(USART2, (u8*)" SD Init ... ");
  while(SD_Init() != SD_OK) {
    LCD_PutStr(Axis_X+8*13, Axis_Y+16*3, (u8*)"Failed!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)"Failed!!\r\n");
    while(1) {
      LED_R = ~LED_R;
      Delay_100ms(2);
    }
  }
  LCD_PutStr(Axis_X+8*13, Axis_Y+16*3, (u8*)"OK!!", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)"OK!!\r\n\r\n");

  LCD_PutStr(Axis_X,      Axis_Y+16*5,  (u8*)"---- SD Init Info -----", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*6,  (u8*)" Capacity : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*12, Axis_Y+16*6,  Type_D, 5, SDCardInfo.CardCapacity>>20, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*17, Axis_Y+16*6,  (u8*)" MB", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*7,  (u8*)" CardBlockSize : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*17, Axis_Y+16*7,  Type_D, 5, SDCardInfo.CardBlockSize, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*22, Axis_Y+16*7,  (u8*)" ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*8,  (u8*)" CardType : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*12, Axis_Y+16*8,  Type_D, 5, SDCardInfo.CardType, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*17, Axis_Y+16*8,  (u8*)" ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*9,  (u8*)" RCA : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*7,  Axis_Y+16*9,  Type_D, 5, SDCardInfo.RCA, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*12, Axis_Y+16*9,  (u8*)" ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*10, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)"-----SD Init Info-----\r\n");
  RS232_SendStr(USART2, (u8*)" Capacity : ");
  RS232_SendNum(USART2, Type_D, 5, SDCardInfo.CardCapacity>>20);
  RS232_SendStr(USART2, (u8*)" MB\r\n");
  RS232_SendStr(USART2, (u8*)" CardBlockSize : ");
  RS232_SendNum(USART2, Type_D, 5, SDCardInfo.CardBlockSize);
  RS232_SendStr(USART2, (u8*)"\r\n");
  RS232_SendStr(USART2, (u8*)" CardType : ");
  RS232_SendNum(USART2, Type_D, 5, SDCardInfo.CardType);
  RS232_SendStr(USART2, (u8*)"\r\n");
  RS232_SendStr(USART2, (u8*)" RCA : ");
  RS232_SendNum(USART2, Type_D, 5, SDCardInfo.RCA);
  RS232_SendStr(USART2, (u8*)"\r\n");
  RS232_SendStr(USART2, (u8*)"----------------------\r\n");
  RS232_SendStr(USART2, (u8*)"\r\n");

  Delay_100ms(1);
  //////////////////// Wait
  while(KEY_S2 != 1){
    LED_G = ~LED_G;
    Delay_100ms(5);
  }
  LED_G = 0;
  LCD_Clear(BLACK);

  // Read Directory File
  LCD_PutStr(Axis_X, Axis_Y+16*0, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*1, (u8*)" SD_Card Read Directory", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*2, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)"----------------------\r\n");
  RS232_SendStr(USART2, (u8*)" SD_Card Read Directory File\r\n");
  RS232_SendStr(USART2, (u8*)"----------------------\r\n\r\n");

  res = f_mount(&FatFs, "", 1);
  res = f_opendir(&dirs, "0:/");
  res = f_readdir(&dirs, &finfo);
  while(res!= FR_OK) {
    LCD_PutStr(Axis_X, Axis_Y+16*3, (u8*)" Fatfs failed!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)" FatFs failed!!\r\n");
    while(1) {
      LED_R = ~LED_R;
      Delay_100ms(2);
    }
  }
  LCD_PutStr(Axis_X, Axis_Y+16*3, (u8*)" File name : ", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)" File name : \r\n");

  while(finfo.fname[0]) {
    f_readdir(&dirs, &finfo);
    if(!finfo.fname[0])
      break;
    if(FileNum<11) {
      LCD_PutStr(Axis_X,     Axis_Y+16*(3+FileNum), (u8*)" ... ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_X+8*5, Axis_Y+16*(3+FileNum), (u8*)finfo.fname, ASCII1608, WHITE, BLACK);
    }
    else if((FileNum>=11) && (FileNum<22)) {
      LCD_PutStr(Axis_X+200,     Axis_Y+16*(3+FileNum-11), (u8*)" ... ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_X+8*5+200, Axis_Y+16*(3+FileNum-11), (u8*)finfo.fname, ASCII1608, WHITE, BLACK);
    }
    else {
      FileNum = 0;
      break;
    }
    FileNum++;
    RS232_SendStr(USART2, (u8*)" ... ");
    RS232_SendStr(USART2, (u8*)finfo.fname);
    RS232_SendStr(USART2, (u8*)"\r\n");
  }

  Delay_100ms(1);
  //////////////////// Wait
  while(KEY_S2 != 1){
    LED_B = ~LED_B;
    Delay_100ms(5);
  }
  LED_B = 0;
  LCD_Clear(BLACK);

  // Write File
  LCD_PutStr(Axis_X, Axis_Y+16*0, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*1, (u8*)" SD_Card Write Data",     ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*2, (u8*)"-----------------------", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)"-----------------------\r\n");
  RS232_SendStr(USART2, (u8*)" SD_Card Write Data File\r\n");
  RS232_SendStr(USART2, (u8*)"-----------------------\r\n\r\n");

  LCD_PutStr(Axis_X, Axis_Y+16*3, (u8*)" f_open ... ", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)" f_open ... ");
  res = f_open(&file,"SDCard_K.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
  if(res==FR_OK) {
    LCD_PutStr(Axis_X+8*12, Axis_Y+16*3, (u8*)"OK!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)"OK!!\r\n");
  }
  else {
    LCD_PutStr(Axis_X+8*12, Axis_Y+16*3, (u8*)"failed!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)"failed!!\r\n");
  }

  LCD_PutStr(Axis_X, Axis_Y+16*4, (u8*)" f_write ... ", ASCII1608, WHITE, BLACK);

  RS232_SendStr(USART2, (u8*)" f_write ... ");
  res = f_write(&file, WriteData, 20, &i); 
  if(res==FR_OK) {
    LCD_PutStr(Axis_X+8*13, Axis_Y+16*4, (u8*)"OK!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)"OK!!\r\n");
  }
  else {
    LCD_PutStr(Axis_X+8*13, Axis_Y+16*4, (u8*)"failed!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)"failed!!\r\n");
  }

  file.fptr = 0;

  LCD_PutStr(Axis_X, Axis_Y+16*5, (u8*)" f_read ... ", ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, (u8*)" f_read ... ");
  res = f_read(&file, ReadBuf, 100, &i);
  if(res==FR_OK) {
    LCD_PutStr(Axis_X+8*12, Axis_Y+16*5, (u8*)"OK!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)"OK!!\r\n");
  }
  else {
    LCD_PutStr(Axis_X+8*12, Axis_Y+16*5, (u8*)"failed!!", ASCII1608, WHITE, BLACK);
    RS232_SendStr(USART2, (u8*)"failed!!\r\n");
  }

  f_close(&file);

  LCD_PutStr(Axis_X, Axis_Y+16*7, (u8*)" Read String : ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*1, Axis_Y+16*8, (u8*)ReadBuf, ASCII1608, WHITE, BLACK);
  RS232_SendStr(USART2, ReadBuf);

  while(1) {
    LED_Y = ~LED_Y;
    Delay_100ms(2);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | 
                         RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);

  /* LED_R PC13 */  /* LED_G PC14 */  /* LED_B PC15 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  /* LED_Y PE6 */ 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* KEY_LL PA0 */  /* KEY_LP PA1 */  /* KEY_RP PA8 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* KEY_LR PB2 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  /* KEY_RL PD3 */  /* KEY_RR PD6 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  /* KEY_PR PE0 */  /* KEY_PP PE1 */  /* KEY_PL PE2 */
  /* KEY_S1 PE3 */  /* KEY_S2 PE4 */  /* KEY_S3 PE5 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |
                             GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
  LED_Y = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
