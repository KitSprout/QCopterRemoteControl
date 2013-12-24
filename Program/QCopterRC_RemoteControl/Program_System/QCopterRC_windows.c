/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "QCopterRC_windows.h"
#include "module_r61581.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void Windows_Clear( u32 Color )
{
  LCD_DrawRectangleFill(Window_PosX, Window_PosY, Window_W, Window_H, Color);
}
void Windows_DrawPixel( u16 CoordiX, u16 CoordiY, u16 Color )
{
  LCD_DrawPixel(Window_PosX+CoordiX, Window_PosY+CoordiY, Color);
}
void Windows_DrawLineX( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
{
  LCD_DrawLineX(Window_PosX+CoordiX, Window_PosY+CoordiY, Length, Color);
}
void Windows_DrawLineY( u16 CoordiX, u16 CoordiY, u16 Length, u16 Color )
{
  LCD_DrawLineY(Window_PosX+CoordiX, Window_PosY+CoordiY, Length, Color);
}
void Windows_DrawRectangle( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color )
{
  LCD_DrawRectangle(Window_PosX+CoordiX, Window_PosY+CoordiY, Width, Height, Color);
}
void Windows_DrawRectangleFill( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, u16 Color )
{
  LCD_DrawRectangleFill(Window_PosX+CoordiX, Window_PosY+CoordiY, Width, Height, Color);
}
void Windows_DrawCircle( u16 CoordiX, u16 CoordiY, u16 Radius, u16 Color )
{
  LCD_DrawCircle(Window_PosX+CoordiX, Window_PosY+CoordiY, Radius, Color);
}
void Windows_DrawPicture( u16 CoordiX, u16 CoordiY, u16 Width, u16 Height, uc8 *Pic )
{
  LCD_DrawPicture(Window_PosX+CoordiX, Window_PosX+CoordiY, Width, Height, Pic);
}
void Windows_PutStr( u16 CoordiX, u16 CoordiY, u8 *ChWord, u8 FontStyle, u16 FontColor, u16 BackColor )
{
  LCD_PutStr(Window_PosX+CoordiX, Window_PosY+CoordiY, ChWord, FontStyle, FontColor, BackColor);
}
void Windows_PutNum( u16 CoordiX, u16 CoordiY, u8 Type, u8 Length, u32 NumData, u16 FontColor, u16 BackColor )
{
  LCD_PutNum(Window_PosX+CoordiX, Window_PosY+CoordiY, Type, Length, NumData, FontColor, BackColor);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
#define MenuButton_W 64
#define MenuButton_H 20
#define MenuButton_HelfW 32
#define MenuButton_HelfH 10
static void Windows_DrawMenuButton( u16 CoordiX, u16 CoordiY, u8* MenuStr, u32 Color )
{
  u8 strPosX = MenuButton_HelfW-(u8)((Str_LenOfStr(MenuStr)/2.0f)*8);
  u8 strPosY = MenuButton_HelfH-8;

  LCD_DrawRectangle(CoordiX,   CoordiY,   MenuButton_W,   MenuButton_H,   Color);
  LCD_DrawRectangle(CoordiX+1, CoordiY+1, MenuButton_W-2, MenuButton_H-2, Color);

  LCD_PutStr(CoordiX+strPosX, CoordiY+strPosY, MenuStr, ASCII1608, WHITE, BLACK);
}
static void Windows_DrawFixPixel( u16 CoordiX, u16 CoordiY, u32 Color )
{
  LCD_DrawRectangleFill(CoordiX, CoordiY, 2, 2, Color);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
#define MenuButton_Pos 296  // Menu_H = 24
void Windows_DrawMenu( void )
{
  LCD_DrawRectangle(Window_PosX-2, Window_PosY-2, Window_W+4, Window_H+4, WHITE);
  LCD_DrawRectangle(Window_PosX-1, Window_PosX-1, Window_W+2, Window_H+2, WHITE);

  Windows_DrawMenuButton(Windows_SelMenu_1, MenuButton_Pos+4, Windows_MenuName_1, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_2, MenuButton_Pos+4, Windows_MenuName_2, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_3, MenuButton_Pos+4, Windows_MenuName_3, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_4, MenuButton_Pos+4, Windows_MenuName_4, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_5, MenuButton_Pos+4, Windows_MenuName_5, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_6, MenuButton_Pos+4, Windows_MenuName_6, WHITE);
  Windows_DrawMenuButton(Windows_SelMenu_7, MenuButton_Pos+4, Windows_MenuName_7, WHITE);

  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos,   MenuButton_W-4, BLACK);
  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos+1, MenuButton_W-4, BLACK);
  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos+4, MenuButton_W-4, BLACK);
  LCD_DrawLineX(Window_PosX+Windows_SelMenu_1, MenuButton_Pos+5, MenuButton_W-4, BLACK);

  Windows_DrawFixPixel(Windows_SelMenu_1,                MenuButton_Pos+2, WHITE);
  Windows_DrawFixPixel(Windows_SelMenu_1+MenuButton_W-2, MenuButton_Pos+2, WHITE);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void Windows_SelMenu( u16 CoordiX, u32 SColor, u32 BColor )
{
  static u16 SelMenu[2] = {0};
  static u16 Tmp_CoordiX = 4;

  SelMenu[0] = (CoordiX-4)/68;

  LCD_DrawRectangle(Window_PosX-2, Window_PosY-2, Window_W+4, Window_H+4, WHITE);
  LCD_DrawRectangle(Window_PosX-1, Window_PosX-1, Window_W+2, Window_H+2, WHITE);
  LCD_DrawLineX(Window_PosX+Tmp_CoordiX, MenuButton_Pos+4, MenuButton_W-4, SColor);
  LCD_DrawLineX(Window_PosX+Tmp_CoordiX, MenuButton_Pos+5, MenuButton_W-4, SColor);
  LCD_DrawLineX(Window_PosX+CoordiX, MenuButton_Pos,   MenuButton_W-4, BColor);
  LCD_DrawLineX(Window_PosX+CoordiX, MenuButton_Pos+1, MenuButton_W-4, BColor);
  LCD_DrawLineX(Window_PosX+CoordiX, MenuButton_Pos+4, MenuButton_W-4, BColor);
  LCD_DrawLineX(Window_PosX+CoordiX, MenuButton_Pos+5, MenuButton_W-4, BColor);

  Windows_DrawFixPixel(Tmp_CoordiX,                MenuButton_Pos+2, BColor);
  Windows_DrawFixPixel(Tmp_CoordiX+MenuButton_W-2, MenuButton_Pos+2, BColor);
  Windows_DrawFixPixel(CoordiX,                MenuButton_Pos+2, SColor);
  Windows_DrawFixPixel(CoordiX+MenuButton_W-2, MenuButton_Pos+2, SColor);

  Tmp_CoordiX = CoordiX;
  SelMenu[1] = SelMenu[0];
}
/*=====================================================================================================*/
/*=====================================================================================================*/
