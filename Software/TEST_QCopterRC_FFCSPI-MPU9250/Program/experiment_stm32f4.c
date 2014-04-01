/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "QCopterRC_board.h"
#include "system_waveForm.h"
#include "module_r61581.h"
#include "module_mpu9250.h"
#include "algorithm_mathUnit.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define WaveFromNum_X 420
#define WaveFromNum_Y 10

typedef __IO enum {
  WAVEFORM_OUT_L = 0,
  WAVEFORM_ACC,
  WAVEFORM_GYR,
  WAVEFORM_MAG,
  WAVEFORM_ANG,
  WAVEFORM_TEST,
  WAVEFORM_OUT_R
} WAVEFORM_SEL;

typedef struct {
  s16 X;
  s16 Y;
  s16 Z;
  fp32 TrueX;
  fp32 TrueY;
  fp32 TrueZ;
} SENSOR_ST;
/*=====================================================================================================*/
/*=====================================================================================================*/
SENSOR_ST Acc, Gyr, Mag, Ang;

WaveForm_Struct WaveForm;
/*=====================================================================================================*/
/*=====================================================================================================*/
void System_Init( void )
{
  u8 DeviceID = ERROR;

	SystemInit();

	LED_Config();
  KEY_Config();
  MPU9250_Config();
  R61581_Config();

  MPU9250_Init();
  R61581_Init();

  // WaveFrom Init
	WaveForm.Channel = 3;
	WaveForm.WindowColor = WHITE;
	WaveForm.BackColor = BLACK;
	WaveForm.Data[0] = 0;
	WaveForm.Data[1] = 0;
	WaveForm.Data[2] = 0;
	WaveForm.Scale[0] = 100;
	WaveForm.Scale[1] = 100;
	WaveForm.Scale[2] = 100;
	WaveForm.PointColor[0] = RED;
	WaveForm.PointColor[1] = GREEN;
	WaveForm.PointColor[2] = BLUE;

  ///// TEST IMU
  DeviceID = MPU9250_Check();
  LCD_PutStr(10, 10+16*0, (u8*)"Device ID = 0x", ASCII1608, WHITE, BLACK);
  LCD_PutNum(10+14*8, 10+16*0, Type_H, 2, DeviceID, WHITE, BLACK);
  if(DeviceID == SUCCESS) {
    LED_R = !LED_R;
    LED_G = 0;
    LED_B = 0;
    LED_Y = 0;
    LCD_PutStr(10, 10+16*1, (u8*)"Read Device ID SUCCESS!!", ASCII1608, WHITE, BLACK);
  }
  else {
    LED_R = !LED_R;
    LED_G = 0;
    LED_B = 1;
    LED_Y = 1;
    LCD_PutStr(10, 10+16*1, (u8*)"Read Device ID ERROR!!", ASCII1608, WHITE, BLACK);
    while(1);
  }

  // Windows Init
  LCD_Clear(BLACK);

  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*0,  (u8*)"-------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2,  (u8*)"       ", ASCII1608, WHITE, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*4,  (u8*)"-------", ASCII1608, WHITE, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*7,  (u8*)" AxisX ", ASCII1608, RED,   BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*12, (u8*)" AxisY ", ASCII1608, GREEN, BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*17, (u8*)" AxisZ ", ASCII1608, BLUE,  BLACK);
  LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*22, (u8*)"-------", ASCII1608, WHITE, BLACK);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFrom_Run( WAVEFORM_SEL WaveForm_Sel )
{
  static s32 Sita = 0;

  switch(WaveForm_Sel) {
    case WAVEFORM_ACC:
      WaveForm.Data[0] = (s16)(Acc.TrueX*1000);
      WaveForm.Data[1] = (s16)(Acc.TrueY*1000);
      WaveForm.Data[2] = (s16)(Acc.TrueZ*1000);
      LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2, (u8*)"  ACC  ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_GYR:
      WaveForm.Data[0] = (s16)(Gyr.TrueX*100);
      WaveForm.Data[1] = (s16)(Gyr.TrueY*100);
      WaveForm.Data[2] = (s16)(Gyr.TrueZ*100);
      LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2, (u8*)"  GYR  ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_MAG:
      WaveForm.Data[0] = (s16)(Mag.TrueX*10);
      WaveForm.Data[1] = (s16)(Mag.TrueY*10);
      WaveForm.Data[2] = (s16)(Mag.TrueZ*10);
      LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2, (u8*)"  MAG  ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_ANG:
      WaveForm.Data[0] = (s16)(Ang.TrueX*100);
      WaveForm.Data[1] = (s16)(Ang.TrueY*100);
      WaveForm.Data[2] = (s16)(Ang.TrueZ*100);
      LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2, (u8*)"  ANG  ", ASCII1608, WHITE, BLACK);
      break;
    case WAVEFORM_TEST:
      Sita++;
      if(Sita == 360) Sita = 0;
      WaveForm.Data[0] = sinf(toRad(Sita))*10000;
      WaveForm.Data[1] = sinf(toRad(Sita-120))*10000;
      WaveForm.Data[2] = sinf(toRad(Sita-240))*10000;
      LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2, (u8*)"  SIN  ", ASCII1608, WHITE, BLACK);
      break;
    default:
      LCD_PutStr(WaveFromNum_X, WaveFromNum_Y+8*2, (u8*)" ERROR ", ASCII1608, WHITE, BLACK);
      break;
  }

  LCD_PutNum(WaveFromNum_X, WaveFromNum_Y+8*9,  Type_I, 5, WaveForm.Data[0], RED,   BLACK);
  LCD_PutNum(WaveFromNum_X, WaveFromNum_Y+8*14, Type_I, 5, WaveForm.Data[1], GREEN, BLACK);
  LCD_PutNum(WaveFromNum_X, WaveFromNum_Y+8*19, Type_I, 5, WaveForm.Data[2], BLUE,  BLACK);

  WaveFormPrint(&WaveForm);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void IMU_Read( void )
{
  u8 ReadBuf[24] = {0};

  MPU9250_Read(ReadBuf);

  Acc.X = (s16)Byte16(ReadBuf[0],  ReadBuf[1]);   // Acc_X
  Acc.Y = (s16)Byte16(ReadBuf[2],  ReadBuf[3]);   // Acc_Y
  Acc.Z = (s16)Byte16(ReadBuf[4],  ReadBuf[5]);   // Acc_Z
  Gyr.X = (s16)Byte16(ReadBuf[8],  ReadBuf[9]);   // Gyr_X
  Gyr.Y = (s16)Byte16(ReadBuf[10], ReadBuf[11]);  // Gyr_Y
  Gyr.Z = (s16)Byte16(ReadBuf[12], ReadBuf[13]);  // Gyr_Z
  Mag.X = (s16)Byte16(ReadBuf[15], ReadBuf[14]);  // Mag_X
  Mag.Y = (s16)Byte16(ReadBuf[17], ReadBuf[16]);  // Mag_Y
  Mag.Z = (s16)Byte16(ReadBuf[19], ReadBuf[18]);  // Mag_Z
//  Temp  = (s16)Byte16(ReadBuf[6],  ReadBuf[7]);   // Temp

  Acc.TrueX = Acc.X*MPU9250A_4g;      // g/LSB
  Acc.TrueY = Acc.Y*MPU9250A_4g;      // g/LSB
  Acc.TrueZ = Acc.Z*MPU9250A_4g;      // g/LSB
  Gyr.TrueX = Gyr.X*MPU9250G_2000dps; // dps/LSB
  Gyr.TrueY = Gyr.Y*MPU9250G_2000dps; // dps/LSB
  Gyr.TrueZ = Gyr.Z*MPU9250G_2000dps; // dps/LSB
  Mag.TrueX = Mag.X*MPU9250M_4800uT;  // uT/LSB
  Mag.TrueY = Mag.Y*MPU9250M_4800uT;  // uT/LSB
  Mag.TrueZ = Mag.Z*MPU9250M_4800uT;  // uT/LSB
}
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  WAVEFORM_SEL WaveForm_Sel = WAVEFORM_TEST;

  System_Init();

  while(1) {
    LED_R = !LED_R;
    LED_G = !LED_G;
    LED_B = !LED_B;
    LED_Y = !LED_Y;
//    Delay_1ms(50);

    #define DeBounce 120
    if(DEF_KEY_PR == 0) {
      WaveForm_Sel++;
      if(WaveForm_Sel == WAVEFORM_OUT_R)
        WaveForm_Sel = (WAVEFORM_SEL)(WAVEFORM_OUT_L+1);
      Delay_1ms(DeBounce);
    }
    else if(DEF_KEY_PL == 0) {
      WaveForm_Sel--;
      if(WaveForm_Sel == WAVEFORM_OUT_L)
        WaveForm_Sel = (WAVEFORM_SEL)(WAVEFORM_OUT_R-1);
      Delay_1ms(DeBounce);
    }
    else if(DEF_KEY_PP == 0) {
      // STOP RUN
    }
    else {
      IMU_Read();
      WaveFrom_Run(WaveForm_Sel);
    }
	}
}
/*=====================================================================================================*/
/*=====================================================================================================*/
