/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "module_r61581.h"
#include "system_waveForm.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormInit( WaveForm_Struct* WaveForm )
{
  WaveForm->Channel = 4;
  WaveForm->WindowColor = WHITE;
  WaveForm->BackColor = BLACK;
  WaveForm->Data[0] = 0;
  WaveForm->Data[1] = 0;
  WaveForm->Data[2] = 0;
  WaveForm->Data[3] = 0;
  WaveForm->Scale[0] = 100;
  WaveForm->Scale[1] = 100;
  WaveForm->Scale[2] = 100;
  WaveForm->Scale[3] = 100;
  WaveForm->PointColor[0] = RED;
  WaveForm->PointColor[1] = GREEN;
  WaveForm->PointColor[2] = BLUE;
  WaveForm->PointColor[3] = YELLOW;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormPrint( WaveForm_Struct* WaveForm )
{
  u16 i, j;
  s16 TempY[WaveChannelMax] = {0};
  s16 CoordiY[WaveChannelMax] = {0};

  static u16 WavePic[WaveChannelMax][WaveFormW] = {0};

  /* 更新顯示座標 */
  for(i=0; i<WaveForm->Channel; i++) {
    for(j=0; j<WaveFormW-1; j++)
      WavePic[i][j] = WavePic[i][j+1];
    TempY[i] = (s16)((double)WaveForm->Data[i]/WaveForm->Scale[i]+0.5);
    CoordiY[i] = WaveFormH - TempY[i];
    if(CoordiY[i]<0)
      WavePic[i][WaveFormW-1] = 0;
    else if(CoordiY[i]>WaveForm2H)
      WavePic[i][WaveFormW-1] = WaveForm2H;
    else
      WavePic[i][WaveFormW-1] = CoordiY[i];
  }
  /* 畫邊框 */
  LCD_DrawLineX(WaveWindowX,           WaveWindowY,            WaveFormW,	   WaveForm->WindowColor);
  LCD_DrawLineX(WaveWindowX,           WaveWindowY+WaveForm2H, WaveFormW,    WaveForm->WindowColor);
  LCD_DrawLineY(WaveWindowX,           WaveWindowY,            WaveForm2H+1, WaveForm->WindowColor);
  LCD_DrawLineY(WaveWindowX+WaveFormW, WaveWindowY,            WaveForm2H+1, WaveForm->WindowColor);
  /* 顯示 */
  for(i=0; i<WaveFormW-1; i++) {
    /* 清除上筆數據 */
    for(j=0; j<WaveForm->Channel; j++) {
      if(WavePic[j][i] == 0)
      LCD_DrawPixel(WaveWindowX+i+1, WaveWindowY+WavePic[j][i], WaveForm->WindowColor);
      else if(WavePic[j][i] == WaveForm2H)
      LCD_DrawPixel(WaveWindowX+i+1, WaveWindowY+WavePic[j][i], WaveForm->WindowColor);
      else
      LCD_DrawPixel(WaveWindowX+i+1, WaveWindowY+WavePic[j][i], WaveForm->BackColor);
    }
    /* 畫輔助線 */
    if((i%10) < 3) {
      for(j=0; j<=WaveFormH; j+=(WaveFormH/10)) {
        LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WaveFormH+j, WaveForm->WindowColor);
        LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WaveFormH-j, WaveForm->WindowColor);
      }
    }
    /* 更新顯示新數據 */
    for(j=0; j<WaveForm->Channel; j++) {
      if(WavePic[j][i] == 0)
        LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WavePic[j][i], WaveForm->WindowColor);
      else if(WavePic[j][i] == WaveForm2H)
        LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WavePic[j][i], WaveForm->WindowColor);
      else
        LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WavePic[j][i], WaveForm->PointColor[j]);
    }
    /* 畫中線 */
    LCD_DrawPixel(WaveWindowX+i, WaveWindowY+WaveFormH, WaveForm->WindowColor);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
