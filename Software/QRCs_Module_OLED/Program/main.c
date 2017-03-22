/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    main.c
  * @author  KitSprout
  * @date    16-Mar-2017
  * @brief   
  * 
  */

/* Includes --------------------------------------------------------------------------------*/
#include "drivers\stm32f4_system.h"
#include "modules\ssd1351.h"
#include "stm32f4xx_bsp.h"

/** @addtogroup STM32_Program
  * @{
  */

/* Private typedef -------------------------------------------------------------------------*/
/* Private define --------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------*/
/* Private functions -----------------------------------------------------------------------*/

int main( void )
{
  static uint8_t i = 0;
  static uint16_t color[3] = { RED, GREEN, BLUE };
  static vector_t vec[3] = {
    [0] = { .x =  95, .y = 50 },
    [1] = { .x = 110, .y = 40 },
    [2] = { .x = 100, .y = 70 }
  };

  HAL_Init();
  BSP_GPIO_Config();
  BSP_OLED_Config();

  OLED_Clean(BLACK);
  OLED_TestColoBar();
  OLED_DrawRectFill(10, 0, OLED_W - 20, OLED_H, BLACK);
  OLED_PutStr(CENTER(FONT16, "HELLO"), LINE(FONT16, 2), &FONT16, "HELLO", WHITE, BLACK);
  OLED_PutStr(CENTER(FONT16, "WORLD"), LINE(FONT16, 3), &FONT16, "WORLD",  WHITE, BLACK);

  OLED_DrawCircle(40, 20, 14, RED);
  OLED_DrawCircleFill(40, 20, 10, GREEN);

  OLED_DrawRectFill(40, 100, 40, 10, RED);
  OLED_DrawRect(40, 100, 50, 14, GREEN);

  OLED_DrawVect(vec, color, 3);

  OLED_DrawLine(0, 127, 127, 0, GREEN);
  OLED_DrawLine(0, 20, 127, 20, YELLOW);
  OLED_DrawLine(20, 0, 20, 127, RED);
  OLED_DrawLine(0, 0, 127, 127, BLUE);
  OLED_DrawLine(0, 127, 127, 80, GREEN);
  OLED_DrawLine(127, 80, 0, 127, WHITE);
  OLED_DrawLine(60, 127, 30, 80, GREEN);
  OLED_DrawLine(100, 30, 20, 100, RED);

  while (1) {
    OLED_PutNum(CENTER(FONT16, "   "), LINE(FONT16, 5), &FONT16, S_DEC, 3, i++, WHITE, BLACK);
    LED_G_Toggle();
    delay_ms(200);
  }
}

/*************************************** END OF FILE ****************************************/
