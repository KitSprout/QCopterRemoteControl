/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "QCopterRC_board.h"
#include "module_r61581.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void MoveCirR( u16 CoordiX, u16 CoordiY, u16 Radius, u16 LineColor, u16 BackColor )
{
  static u32 clearColor = 0;
  static u16 tmpRadius = 0;
  static u16 tmpCoordiX = 0, tmpCoordiY = 0;

  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);
  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);

  tmpRadius = Radius;
  clearColor = BackColor;
  tmpCoordiX = CoordiX;
  tmpCoordiY = CoordiY;

  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
}
void MoveCirL( u16 CoordiX, u16 CoordiY, u16 Radius, u16 LineColor, u16 BackColor )
{
  static u32 clearColor = 0;
  static u16 tmpRadius = 0;
  static u16 tmpCoordiX = 0, tmpCoordiY = 0;

  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);
  LCD_DrawCircle(tmpCoordiX, tmpCoordiY, tmpRadius, clearColor);

  tmpRadius = Radius;
  clearColor = BackColor;
  tmpCoordiX = CoordiX;
  tmpCoordiY = CoordiY;

  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
  LCD_DrawCircle(CoordiX, CoordiY, Radius, LineColor);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
	SystemInit();
	KeyBoard_Config();
  R61581_Config();
  R61581_Init();

  while(1) {

    LED_R = !LED_R;
    LED_G = !LED_G;
    LED_B = !LED_B;
    LED_Y = !LED_Y;

    KeyBoard_Read();

    #define Axis_CIR_X 118
    #define Axis_CIR_Y 220

    LCD_DrawCircle(Axis_CIR_X,     Axis_CIR_Y-100, 102, WHITE);
    LCD_DrawCircle(Axis_CIR_X,     Axis_CIR_Y-100, 101, WHITE);
    LCD_DrawCircle(Axis_CIR_X+240, Axis_CIR_Y-100, 102, WHITE);
    LCD_DrawCircle(Axis_CIR_X+240, Axis_CIR_Y-100, 101, WHITE);

    #define Axis_KEY_X 20
    #define Axis_KEY_Y 250

    if(KEY_LP == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*0, (u8*)"KEY_LP", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*0, (u8*)"KEY_LP", ASCII1608, WHITE, BLACK);
    if(KEY_LR == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*1, (u8*)"KEY_LR", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*1, (u8*)"KEY_LR", ASCII1608, WHITE, BLACK);
    if(KEY_LL == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*2, (u8*)"KEY_LL", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*0,  Axis_KEY_Y+16*2, (u8*)"KEY_LL", ASCII1608, WHITE, BLACK);

    if(KEY_PP == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*0, (u8*)"KEY_PP", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*0, (u8*)"KEY_PP", ASCII1608, WHITE, BLACK);
    if(KEY_PR == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*1, (u8*)"KEY_PR", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*1, (u8*)"KEY_PR", ASCII1608, WHITE, BLACK);
    if(KEY_PL == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*2, (u8*)"KEY_PL", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*8,  Axis_KEY_Y+16*2, (u8*)"KEY_PL", ASCII1608, WHITE, BLACK);

    if(KEY_S1 == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*0, (u8*)"KEY_S1", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*0, (u8*)"KEY_S1", ASCII1608, WHITE, BLACK);
    if(KEY_S2 == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*1, (u8*)"KEY_S2", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*1, (u8*)"KEY_S2", ASCII1608, WHITE, BLACK);
    if(KEY_S3 == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*2, (u8*)"KEY_S3", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*16, Axis_KEY_Y+16*2, (u8*)"KEY_S3", ASCII1608, WHITE, BLACK);

    if(KEY_RP == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*0, (u8*)"KEY_RP", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*0, (u8*)"KEY_RP", ASCII1608, WHITE, BLACK);
    if(KEY_RR == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*1, (u8*)"KEY_RR", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*1, (u8*)"KEY_RR", ASCII1608, WHITE, BLACK);
    if(KEY_RL == PRESS_ON)  LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*2, (u8*)"KEY_RL", ASCII1608, GREEN, BLACK);
    else                    LCD_PutStr(Axis_KEY_X+8*24, Axis_KEY_Y+16*2, (u8*)"KEY_RL", ASCII1608, WHITE, BLACK);

    LCD_PutStr(Axis_KEY_X+8*35, Axis_KEY_Y+16*0, (u8*)"LX:", ASCII1608, WHITE, BLACK);
    LCD_PutStr(Axis_KEY_X+8*35, Axis_KEY_Y+16*1, (u8*)"LY:", ASCII1608, WHITE, BLACK);
    LCD_PutStr(Axis_KEY_X+8*35, Axis_KEY_Y+16*2, (u8*)"LZ:", ASCII1608, WHITE, BLACK);
    LCD_PutStr(Axis_KEY_X+8*47, Axis_KEY_Y+16*0, (u8*)"RX:", ASCII1608, WHITE, BLACK);
    LCD_PutStr(Axis_KEY_X+8*47, Axis_KEY_Y+16*1, (u8*)"RY:", ASCII1608, WHITE, BLACK);
    LCD_PutStr(Axis_KEY_X+8*47, Axis_KEY_Y+16*2, (u8*)"RZ:", ASCII1608, WHITE, BLACK);

    LCD_PutNum(Axis_KEY_X+8*38, Axis_KEY_Y+16*0, Type_D, 5, JS_LX, WHITE, BLACK);
    LCD_PutNum(Axis_KEY_X+8*38, Axis_KEY_Y+16*1, Type_D, 5, JS_LY, WHITE, BLACK);
    LCD_PutNum(Axis_KEY_X+8*38, Axis_KEY_Y+16*2, Type_D, 5, JS_LZ, WHITE, BLACK);
    LCD_PutNum(Axis_KEY_X+8*50, Axis_KEY_Y+16*0, Type_D, 5, JS_RX, WHITE, BLACK);
    LCD_PutNum(Axis_KEY_X+8*50, Axis_KEY_Y+16*1, Type_D, 5, JS_RY, WHITE, BLACK);
    LCD_PutNum(Axis_KEY_X+8*50, Axis_KEY_Y+16*2, Type_D, 5, JS_RZ, WHITE, BLACK);

    MoveCirL(Axis_CIR_X+(JS_LX*0.0244140625f-50),       (Axis_CIR_Y-100)+(50-JS_LY*0.0244140625f), 25, GREEN, BLACK);
    MoveCirR((Axis_CIR_X+240)+(JS_RX*0.0244140625f-50), (Axis_CIR_Y-100)+(50-JS_RY*0.0244140625f), 25, GREEN, BLACK);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
