/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_sdio.h"
#include "module_r61581.h"
#include "algorithm_string.h"
#include "algorithm_bitmap.h"

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
FILINFO finfo;
FIL file;

int main( void )
{
  u32 i = 0;
  u8 BitmapHeader[54] = {0};

  FRESULT res;
  BmpHeader BMP_HEADER;

  SystemInit();
  GPIO_Config();
  R61581_Config();
  R61581_Init();

  LED_R = 1;
  LED_G = 1;
  LED_B = 1;
  LED_Y = 1;

  LED_R = 0;
  LCD_Clear(BLACK);

  // SD Card Init Info
  #define Axis_X 8
  #define Axis_Y 0
  LCD_PutStr(Axis_X, Axis_Y+16*0, (u8*)"----------------------------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*1, (u8*)"     SDIO SD Fatfs Demo     ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*2, (u8*)"----------------------------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X, Axis_Y+16*3, (u8*)" SD Init ... ", ASCII1608, WHITE, BLACK);
  while(SD_Init() != SD_OK) {
    LCD_PutStr(Axis_X+8*13, Axis_Y+16*3, (u8*)"Failed!!", ASCII1608, WHITE, BLACK);
    while(1) {
      LED_R = ~LED_R;
      Delay_100ms(2);
    }
  }
  LCD_PutStr(Axis_X+8*13, Axis_Y+16*3,  (u8*)"OK!!", ASCII1608, WHITE, BLACK);

  LCD_PutStr(Axis_X,      Axis_Y+16*5,  (u8*)"------- SD Init Info -------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*6,  (u8*)" Capacity : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*12, Axis_Y+16*6,  Type_D, 5, SDCardInfo.CardCapacity>>20, ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*17, Axis_Y+16*6,  (u8*)" MB", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*7,  (u8*)" CardBlockSize : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*17, Axis_Y+16*7,  Type_D, 5, SDCardInfo.CardBlockSize, ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*22, Axis_Y+16*7,  (u8*)" ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*8,  (u8*)" CardType : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*12, Axis_Y+16*8,  Type_D, 5, SDCardInfo.CardType, ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*17, Axis_Y+16*8,  (u8*)" ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*9,  (u8*)" RCA : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(Axis_X+8*7,  Axis_Y+16*9,  Type_D, 5, SDCardInfo.RCA, ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X+8*12, Axis_Y+16*9,  (u8*)" ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(Axis_X,      Axis_Y+16*10, (u8*)"----------------------------", ASCII1608, WHITE, BLACK);

  // Bitmap Header Info
  #define BMP_X 245
  #define BMP_Y 0

  res = f_mount(&FatFs, "", 1);

  LCD_PutStr(Axis_X,      Axis_Y+16*12, (u8*)" Read QRC.bmp ...", ASCII1608, WHITE, BLACK);
  f_open(&file, "QRC.bmp", FA_OPEN_EXISTING | FA_READ);
  res = f_read(&file, BitmapHeader, sizeof(BmpHeader), &i);
  while(res!=FR_OK) {
		LCD_PutStr(Axis_X+8*17, Axis_Y+16*12, (u8*)" Failed!!", ASCII1608, WHITE, BLACK);
		while(1) {
      LED_R = ~LED_R;
      Delay_100ms(2);
    }
	}
  f_close(&file);
  LCD_PutStr(Axis_X+8*17, Axis_Y+16*12, (u8*)" OK!!", ASCII1608, WHITE, BLACK);

  LCD_PutStr(BMP_X,      BMP_Y+16*0,  (u8*)"----------------------------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*1,  (u8*)"       BMP HeaderInfo       ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*2,  (u8*)"----------------------------", ASCII1608, WHITE, BLACK);

  BMP_ReadInfo(&BMP_HEADER, BitmapHeader);

  LCD_PutStr(BMP_X,      BMP_Y+16*3,  (u8*)" Identifier : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*14, BMP_Y+16*3,  Type_H, 4, BMP_HEADER.Identifier, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*4,  (u8*)" FileSize : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*12, BMP_Y+16*4,  Type_H, 8, BMP_HEADER.FileSize, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*5,  (u8*)" Reserved : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*12, BMP_Y+16*5,  Type_H, 8, BMP_HEADER.Reserved, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*6,  (u8*)" DataOffset : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*14, BMP_Y+16*6,  Type_H, 8, BMP_HEADER.DataOffset, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*7,  (u8*)" HeaderSize : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*14, BMP_Y+16*7,  Type_H, 8, BMP_HEADER.HeaderSize, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*8,  (u8*)" Width : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*9,  BMP_Y+16*8,  Type_H, 8, BMP_HEADER.Width, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*9,  (u8*)" Height : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*10, BMP_Y+16*9,  Type_H, 8, BMP_HEADER.Height, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*10, (u8*)" Planes : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*10, BMP_Y+16*10, Type_H, 4, BMP_HEADER.Planes, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*11, (u8*)" BitsPerPixel : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*16, BMP_Y+16*11, Type_H, 4, BMP_HEADER.BitsPerPixel, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*12, (u8*)" Compression : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*15, BMP_Y+16*12, Type_H, 8, BMP_HEADER.Compression, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*13, (u8*)" DataSize : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*12, BMP_Y+16*13, Type_H, 8, BMP_HEADER.DataSize, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*14, (u8*)" H_Resolution : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*16, BMP_Y+16*14, Type_H, 8, BMP_HEADER.H_Resolution, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*15, (u8*)" V_Resolution : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*16, BMP_Y+16*15, Type_H, 8, BMP_HEADER.V_Resolution, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*16, (u8*)" UsedColors : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*14, BMP_Y+16*16, Type_H, 8, BMP_HEADER.UsedColors, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*17, (u8*)" ImportantColors : ", ASCII1608, WHITE, BLACK);
  LCD_PutNum(BMP_X+8*19, BMP_Y+16*17, Type_H, 8, BMP_HEADER.ImportantColors, ASCII1608, WHITE, BLACK);
  LCD_PutStr(BMP_X,      BMP_Y+16*18, (u8*)"----------------------------", ASCII1608, WHITE, BLACK);

  Delay_100ms(1);
  //////////////////// Wait
  while(KEY_S2 != 1){
    LED_G = ~LED_G;
    Delay_100ms(5);
  }
  LED_G = 0;
  LCD_Clear(BLACK);

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
