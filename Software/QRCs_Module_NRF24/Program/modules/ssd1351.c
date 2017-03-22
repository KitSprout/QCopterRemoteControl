/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    ssd1351.c
  * @author  KitSprout
  * @date    16-Mar-2017
  * @brief   
  * 
  */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "drivers\stm32f4_spi.h"
#include "modules\ssd1351.h"

#include <stdio.h>
#include <string.h>

/** @addtogroup STM32_Module
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
static uint8_t TX_BUFFER[OLED_MAX_TXBUF] = {0};
static uint8_t RX_BUFFER[OLED_MAX_RXBUF] = {0};

/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

/**
  * @brief  OLED_WriteCmd
  */
static void OLED_WriteCmd( uint8_t writeCmd )
{
#if !defined(OLED_USE_SIMU_SPI)
  OLED_CS_L();
  OLED_DC_L();
  SPI_RW(hOled.handle, writeCmd);
  OLED_DC_H();
  OLED_CS_H();

#else
  OLED_CS_L();
  OLED_DC_L();
  for (uint8_t i = 0; i < 8; i++) {
    OLED_SCK_L();
    if (writeCmd & 0x80)
      OLED_SDI_H();
    else 
      OLED_SDI_L();
    writeCmd <<= 1;
    OLED_SCK_H();
  }
  OLED_CS_H();

#endif
}

static void OLED_WriteData( uint8_t writeData )
{
#if !defined(OLED_USE_SIMU_SPI)
  OLED_CS_L();
  OLED_DC_H();
  SPI_RW(hOled.handle, writeData);
	OLED_DC_H();
  OLED_CS_H();

#else
  OLED_CS_L();	
  OLED_DC_H();
  for (uint8_t i = 0; i < 8; i++) {
    OLED_SCK_L();
    if (writeData & 0x80)
      OLED_SDI_H();
    else 
      OLED_SDI_L();
    writeData <<= 1;
    OLED_SCK_H();
  }
  OLED_CS_H();

#endif
}

/**
  * @brief  OLED_WriteColor
  */
static void OLED_WriteColor( uint16_t color )
{
#if !defined(OLED_USE_SIMU_SPI)
  OLED_CS_L();
  OLED_DC_H();
  SPI_RW(hOled.handle, Byte16U8H(color));
  SPI_RW(hOled.handle, Byte16U8L(color));
  OLED_CS_H();

#else
  OLED_CS_L();	
  OLED_DC_H();
  for (uint8_t i = 0; i < 16; i++) {
    OLED_SCK_L();
    if (color & 0x8000)
      OLED_SDI_H();
    else 
      OLED_SDI_L();
    color <<= 1;
    OLED_SCK_H();
  }
  OLED_CS_H();

#endif
}

/**
  * @brief  OLED_Config
  */
void OLED_Config( void )
{
 	GPIO_InitTypeDef  GPIO_InitStruct;

  hOled.pTxBuf = TX_BUFFER;
  hOled.pRxBuf = RX_BUFFER;

#if !defined(OLED_USE_SIMU_SPI)

  /* SPI Pin ******************************************************************/
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = OLED_CS_PIN;
  HAL_GPIO_Init(OLED_CS_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = OLED_DC_PIN;
  HAL_GPIO_Init(OLED_DC_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = OLED_RES_PIN;
  HAL_GPIO_Init(OLED_RES_GPIO_PORT, &GPIO_InitStruct);

  OLED_CS_H();  // LOW ENABLE

  /* SPI Init ****************************************************************/
  hOled.handle->Instance               = OLED_SPIx;
  hOled.handle->Init.Mode              = SPI_MODE_MASTER;
  hOled.handle->Init.Direction         = SPI_DIRECTION_2LINES;
  hOled.handle->Init.DataSize          = SPI_DATASIZE_8BIT;
  hOled.handle->Init.CLKPolarity       = SPI_POLARITY_HIGH;
  hOled.handle->Init.CLKPhase          = SPI_PHASE_2EDGE;
  hOled.handle->Init.NSS               = SPI_NSS_SOFT;
  hOled.handle->Init.BaudRatePrescaler = OLED_SPIx_SPEED;
  hOled.handle->Init.FirstBit          = SPI_FIRSTBIT_MSB;
  hOled.handle->Init.TIMode            = SPI_TIMODE_DISABLE;
  hOled.handle->Init.CRCCalculation    = SPI_CRCCALCULATION_ENABLE;
  hOled.handle->Init.CRCPolynomial     = 7;
  HAL_SPI_Init(hOled.handle);

  __HAL_SPI_ENABLE(hOled.handle);

#else
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = OLED_SCK_PIN;
  HAL_GPIO_Init(OLED_SCK_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = OLED_SDI_PIN;
  HAL_GPIO_Init(OLED_SDI_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = OLED_CS_PIN;
  HAL_GPIO_Init(OLED_CS_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = OLED_DC_PIN;
  HAL_GPIO_Init(OLED_DC_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = OLED_RES_PIN;
  HAL_GPIO_Init(OLED_RES_GPIO_PORT, &GPIO_InitStruct);

  OLED_SCK_H();
  OLED_SDI_H();
  OLED_CS_H();
  OLED_DC_H();
  OLED_RES_H();

#endif
}

/**
  * @brief  OLED_Init
  */
void OLED_Init( void )
{
  /* Hardware Reset */
  OLED_RES_L();
  delay_ms(10);
  OLED_RES_H();
  delay_ms(20);

  /* Device Init */
  OLED_WriteCmd(0xFD);    // Unlock Driver IC
  OLED_WriteData(0x12);
  OLED_WriteCmd(0xFD);    // Unlock All Commands
  OLED_WriteData(0xB1);

  OLED_Display(DISABLE);  // Display Off

  OLED_WriteCmd(0xB3);    // Set Clock as 90 Frames/Sec
  OLED_WriteCmd(0xF1);
  OLED_WriteCmd(0xCA);    // 1/128 Duty
  OLED_WriteData(0x7F);
  OLED_WriteCmd(0xA0);    // Set Horizontal Address Increment
  OLED_WriteData(0x74);

  OLED_WriteCmd(0xA1);    // Set Mapping RAM Display Start Line
  OLED_WriteData(0x00);
  OLED_WriteCmd(0xA2);    // Shift Mapping RAM Counter
  OLED_WriteData(0x00);
  OLED_WriteCmd(0xB5);    // Disable GPIO Pins Input
  OLED_WriteData(0x00);
  OLED_WriteCmd(0xAB);    // Enable Internal VDD Regulator
  OLED_WriteData(0x01);
  OLED_WriteCmd(0xB4);    // Enable External VSL
  OLED_WriteData(0xA0);
  OLED_WriteData(0xB5);
  OLED_WriteData(0x55);
  OLED_WriteCmd(0xC1);    // Set Contrast of Color
  OLED_WriteData(0xC8);
  OLED_WriteData(0x80);
  OLED_WriteData(0xC8);
  OLED_WriteCmd(0xC7);    // Set Scale Factor of Segment Output Current Control
  OLED_WriteData(0x0F);
  OLED_WriteCmd(0xB8);    // Set Pulse Width for Gray Scale Table
  OLED_WriteData(0x02);
  OLED_WriteData(0x03);
  OLED_WriteData(0x04);
  OLED_WriteData(0x05);
  OLED_WriteData(0x06);
  OLED_WriteData(0x07);
  OLED_WriteData(0x08);
  OLED_WriteData(0x09);
  OLED_WriteData(0x0A);
  OLED_WriteData(0x0B);
  OLED_WriteData(0x0C);
  OLED_WriteData(0x0D);
  OLED_WriteData(0x0E);
  OLED_WriteData(0x0F);
  OLED_WriteData(0x10);
  OLED_WriteData(0x11);
  OLED_WriteData(0x12);
  OLED_WriteData(0x13);
  OLED_WriteData(0x15);
  OLED_WriteData(0x17);
  OLED_WriteData(0x19);
  OLED_WriteData(0x1B);
  OLED_WriteData(0x1D);
  OLED_WriteData(0x1F);
  OLED_WriteData(0x21);
  OLED_WriteData(0x23);
  OLED_WriteData(0x25);
  OLED_WriteData(0x27);
  OLED_WriteData(0x2A);
  OLED_WriteData(0x2D);
  OLED_WriteData(0x30);
  OLED_WriteData(0x33);
  OLED_WriteData(0x36);
  OLED_WriteData(0x39);
  OLED_WriteData(0x3C);
  OLED_WriteData(0x3F);
  OLED_WriteData(0x42);
  OLED_WriteData(0x45);
  OLED_WriteData(0x48);
  OLED_WriteData(0x4C);
  OLED_WriteData(0x50);
  OLED_WriteData(0x54);
  OLED_WriteData(0x58);
  OLED_WriteData(0x5C);
  OLED_WriteData(0x60);
  OLED_WriteData(0x64);
  OLED_WriteData(0x68);
  OLED_WriteData(0x6C);
  OLED_WriteData(0x70);
  OLED_WriteData(0x74);
  OLED_WriteData(0x78);
  OLED_WriteData(0x7D);
  OLED_WriteData(0x82);
  OLED_WriteData(0x87);
  OLED_WriteData(0x8C);
  OLED_WriteData(0x91);
  OLED_WriteData(0x96);
  OLED_WriteData(0x9B);
  OLED_WriteData(0xA0);
  OLED_WriteData(0xA5);
  OLED_WriteData(0xAA);
  OLED_WriteData(0xAF);
  OLED_WriteData(0xB4);
  OLED_WriteCmd(0xB1);    // Set Phase 1 as 5 Clocks & Phase 2 as 3 Clocks
  OLED_WriteData(0x32);
  OLED_WriteCmd(0xBB);    // Set Pre-Charge Voltage Level as 0.50 * VCC
  OLED_WriteData(0x17);
  OLED_WriteCmd(0xB2);    // Enhance Display Performance
  OLED_WriteData(0xA4);
  OLED_WriteData(0x00);
  OLED_WriteData(0x00);
  OLED_WriteCmd(0xB6);    // Set Second Pre-Charge Period as 1 Clock
  OLED_WriteData(0x01);
  OLED_WriteCmd(0xBE);    // Set Common Pins Deselect Voltage Level as 0.82 * VCC
  OLED_WriteData(0x05);
  OLED_WriteCmd(0xA6);    // Normal Display Mode

  OLED_Clean(WHITE);
  OLED_Display(ENABLE);
}

/**
  * @brief  OLED_Display
  */
void OLED_Display( uint8_t cmd )
{
  if (cmd == ENABLE) {
    OLED_WriteCmd(0xAF);
  }
  else {
    OLED_WriteCmd(0xAE);
  }
}

/**
  * @brief  OLED_Clean
  */
void OLED_Clean( uint16_t color )
{
  uint32_t point = OLED_W * OLED_H;

  OLED_SetWindow(0, 0, OLED_W - 1, OLED_H - 1);

  while (point--) {
    OLED_WriteColor(color);
  }
}

/**
  * @brief  OLED_SetWindow
  */
void OLED_SetWindow( uint8_t posX1, uint8_t posY1, uint8_t posX2, uint8_t posY2 )
{
  if ((posX1 > posX2) || (posY1 > posY2) || (posX2 >= OLED_W) || (posY2 >= OLED_H)) {
    return;
  }

  OLED_WriteCmd(0x15);
  OLED_WriteData(posX1);
  OLED_WriteData(posX2);
  OLED_WriteCmd(0x75);
  OLED_WriteData(posY1);
  OLED_WriteData(posY2);

  OLED_WriteCmd(0x5C);
}

/**
  * @brief  OLED_DrawPixel
  */
void OLED_DrawPixel( uint8_t posX, uint8_t posY, uint16_t color )
{
  OLED_SetWindow(posX, posY, posX, posY);
  OLED_WriteColor(color);
}

/**
  * @brief  OLED_DrawLineX
  */
void OLED_DrawLineX( uint8_t posX, uint8_t posY, uint8_t length, uint16_t color )
{
  if ((posX + length) > OLED_W) {
    return;
  }

  OLED_SetWindow(posX, posY, posX + length - 1, posY);

  while (length--) {
    OLED_WriteColor(color);
  }
}

/**
  * @brief  OLED_DrawLineY
  */
void OLED_DrawLineY( uint8_t posX, uint8_t posY, uint8_t length, uint16_t color )
{
  if ((posY + length) > OLED_H) {
    return;
  }

  OLED_SetWindow(posX, posY, posX, posY + length - 1);

  while (length--) {
    OLED_WriteColor(color);
  }
}

/**
  * @brief  OLED_DrawLine
  */
void OLED_DrawLine( uint8_t posX1, uint8_t posY1, uint8_t posX2, uint8_t posY2, uint16_t color )
{
  int8_t dx = (posX2 - posX1), dy = (posY2 - posY1);
  int8_t err, step;
  uint8_t steep = absInt(dy) > absInt(dx);

  if (steep) {
    swapU8(&posX1, &posY1);
    swapU8(&posX2, &posY2);
  }
  if (posX1 > posX2) {
    swapU8(&posX1, &posX2);
    swapU8(&posY1, &posY2);
  }

  dx = posX2 - posX1;
  dy = posY2 - posY1;
  err = dx / 2;
  step = (dy > 0) ? (1) : (-1);
  dx = absInt(dx);
  dy = absInt(dy);

  while (posX1 <= posX2) {
    if (steep) {
      OLED_DrawPixel(posY1, posX1, color);
    }
    else {
      OLED_DrawPixel(posX1, posY1, color);
    }
    posX1++;
    err -= dy;
    if (err < 0) {
      posY1 += step;
      err += dx;
    }
  }
}

/**
  * @brief  OLED_DrawRect
  */
void OLED_DrawRect( uint8_t posX, uint8_t posY, uint8_t width, uint8_t height, uint16_t color )
{
  if ((width > OLED_W) || (height > OLED_H)) {
    return;
  }

  if (((posX + width) > OLED_W) || ((posY + height) > OLED_H)) {
    return;
  }

  OLED_DrawLineX(posX,             posY,              width,      color);
  OLED_DrawLineX(posX,             posY + height - 1, width,      color);
  OLED_DrawLineY(posX,             posY + 1,          height - 2, color);
  OLED_DrawLineY(posX + width - 1, posY + 1,          height - 2, color);
}

/**
  * @brief  OLED_DrawRectFill
  */
void OLED_DrawRectFill( uint8_t posX, uint8_t posY, uint8_t width, uint8_t height, uint16_t color )
{
  uint32_t point = width * height;

  if ((width > OLED_W) || (height > OLED_H)) {
    return;
  }

  OLED_SetWindow(posX, posY, posX + width - 1, posY + height - 1);

  while (point--) {
    OLED_WriteColor(color);
  }
}

/**
  * @brief  OLED_DrawCircle
  */
void OLED_DrawCircle( uint8_t posX, uint8_t posY, uint8_t radius, uint16_t color )
{
  int16_t di = 3 - (radius * 2);
  uint16_t cX = 0, cY = radius;

//  if (((posX + radius) > OLED_W) || ((posX - radius) < 0) ||
//      ((posY + radius) > OLED_H) || ((posY - radius) < 0)) {
//    return;
//  }

  while (cX <= cY) {
    OLED_DrawPixel(posX + cX, posY - cY, color);
    OLED_DrawPixel(posX - cX, posY - cY, color);
    OLED_DrawPixel(posX + cY, posY - cX, color);
    OLED_DrawPixel(posX - cY, posY - cX, color);
    OLED_DrawPixel(posX + cX, posY + cY, color);
    OLED_DrawPixel(posX - cX, posY + cY, color);
    OLED_DrawPixel(posX + cY, posY + cX, color);
    OLED_DrawPixel(posX - cY, posY + cX, color);

    if (di < 0) {
      di += (cX << 2) + 6;
    }
    else {
      di += ((cX - cY) << 2) + 10;
      cY--;
    }
    cX++;
  }
}

/**
  * @brief  OLED_DrawCircleFill
  */
void OLED_DrawCircleFill( uint8_t posX, uint8_t posY, uint8_t radius, uint16_t color )
{
  int16_t di = 3 - (radius * 2);
  uint16_t cX = 0, cY = radius;

  while (cX <= cY) {
    OLED_DrawLineX(posX - cX, posY - cY, (cX << 1) + 1, color);
    OLED_DrawLineX(posX - cX, posY + cY, (cX << 1) + 1, color);
    OLED_DrawLineX(posX - cY, posY - cX, (cY << 1) + 1, color);
    OLED_DrawLineX(posX - cY, posY + cX, (cY << 1) + 1, color);

    if (di < 0) {
      di += (cX << 2) + 6;
    }
    else {
      di += ((cX - cY) << 2) + 10;
      cY--;
    }
    cX++;
  }
}

/**
  * @brief  OLED_DrawVect
  */
void OLED_DrawVect( vector_t *vect, uint16_t *color, uint8_t lens )
{
  for (uint8_t i = 0;  i < (lens - 1); i++) {
    OLED_DrawLine(vect[i].x, vect[i].y, vect[i+1].x, vect[i+1].y, color[i]);
  }
  OLED_DrawLine(vect[lens - 1].x, vect[lens - 1].y, vect[0].x, vect[0].y, color[lens - 1]);
}

/**
  * @brief  OLED_DrawPic
  */
void OLED_DrawPic( uint8_t posX, uint8_t posY, uint8_t width, uint8_t height, const uint16_t *pic )
{
  uint32_t point = height * width;

  if ((width > OLED_W) || (height > OLED_H)) {
    return;
  }

  OLED_SetWindow(posX, posY, posX + width - 1, posY + height - 1);

  for (uint32_t i = 0; i < point; i++)
    OLED_WriteColor(pic[i]);
}

/**
  * @brief  OLED_PutChar
  */
void OLED_PutChar( uint8_t posX, uint8_t posY, sFONT *pFont, uint8_t word, uint16_t fontColor, uint16_t backColor )
{
  uint8_t tmp = 0;
  uint8_t font_h = pFont->height;
  uint8_t font_w = pFont->width;
  uint16_t point = 0;

  if (pFont->type == dirH) {
    point = (word - ' ') * font_h;
    for (uint8_t i = 0; i < font_h; i++) {
      tmp = pFont->table[point + i];
      for (uint8_t j = 0; j < font_w; j++) {
        if ((tmp << j) & 0x80)
          OLED_DrawPixel(posX + j, posY + i, fontColor);
        else
          OLED_DrawPixel(posX + j, posY + i, backColor);
      }
    }
  }
  else {
    point = (word - ' ') * font_w;
    for (uint8_t i = 0; i < font_w; i++) {
      tmp = pFont->table[point + i];
      for (uint8_t j = 0; j < font_h; j++) {
        if ((tmp >> j) & 0x01)
          OLED_DrawPixel(posX + i, posY + j, fontColor);
        else
          OLED_DrawPixel(posX + i, posY + j, backColor);
      }
    }
  }
}

/**
  * @brief  OLED_PutStr
  */
void OLED_PutStr( uint8_t posX, uint8_t posY, sFONT *pFont, char *pString, uint16_t fontColor, uint16_t backColor )
{
  uint16_t offsetX = 0;

  while (*pString) {
    OLED_PutChar(posX + offsetX, posY, pFont, *pString, fontColor, backColor);
    pString++;
    offsetX += pFont->width;
  }
}

/**
  * @brief  OLED_PutNum
  */
void OLED_PutNum( uint8_t posX, uint8_t posY, sFONT *pFont, StringType_t type, uint8_t lens, int32_t number, uint16_t fontColor, uint16_t backColor )
{
  char strBuf[16] = {0};

  num2Str(type, lens, strBuf, number);
  OLED_PutStr(posX, posY, pFont, strBuf, fontColor, backColor);
}

/**
  * @brief  OLED_TestColoBar
  */
#define COLOR_NUMBER      (16)
#define COLOR_BAR_HEIGHT  (OLED_W / COLOR_NUMBER)  // 128/16 = 6

void OLED_TestColoBar( void )
{
  const uint16_t drawColor[COLOR_NUMBER] = {
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
    GRAYBLUE
  };

  OLED_SetWindow(0, 0, OLED_W - 1, OLED_H - 1);

  for (uint32_t i = 0; i < COLOR_NUMBER; i++) {
    uint32_t j = (OLED_H / COLOR_NUMBER) * OLED_W;
    while (j--)
      OLED_WriteColor(drawColor[i]);
  }
}

/*************************************** END OF FILE ****************************************/
