/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_adc.h"
#include "QCopterRC_windows.h"
#include "QCopterRC_userInterface.h"
#include "module_r61581.h"
#include "algorithm_string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_Init( void )
{
  Windows_DrawMenu();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_MoveSel( WINDOWS_MENU MenuSel )
{
  switch(MenuSel) {
    case WINDOWS_CTRL:
      Windows_Clear(BLACK);
      Windows_SelMenu(Windows_SelMenu_1, WHITE, BLACK);
      MenuCtrl_Motor_Init();
      MenuCtrl_Connection_Init();
      MenuCtrl_Mode_Init();
      MenuCtrl_WorkTime_Init();
      MenuCtrl_Power_Init();
      break;
    case WINDOWS_TRACK:
      Windows_Clear(GREEN);
      Windows_SelMenu(Windows_SelMenu_2, WHITE, BLACK);
      break;
    case WINDOWS_WAVE:
      Windows_Clear(BLACK);
      Windows_SelMenu(Windows_SelMenu_3, WHITE, BLACK);
      break;
    case WINDOWS_GPS:
      Windows_Clear(BLUE);
      Windows_SelMenu(Windows_SelMenu_4, WHITE, BLACK);
      break;
    case WINDOWS_IMAGE:
      Windows_Clear(RED);
      Windows_SelMenu(Windows_SelMenu_5, WHITE, BLACK);
      break;
    case WINDOWS_TEST:
      Windows_Clear(BLACK);
      Windows_SelMenu(Windows_SelMenu_6, WHITE, BLACK);

      #define Axis_ADC_X 290
      #define Axis_ADC_Y 96
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*0, (u8*)"---- ADC -----", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*1, (u8*)"ADC_RX = ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*2, (u8*)"ADC_RY = ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*3, (u8*)"ADC_LX = ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*4, (u8*)"ADC_LY = ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*5, (u8*)"ADC_RZ = ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*6, (u8*)"ADC_LZ = ", ASCII1608, WHITE, BLACK);
      LCD_PutStr(Axis_ADC_X, Axis_ADC_Y+16*7, (u8*)"--------------", ASCII1608, WHITE, BLACK);
      break;
    case WINDOWS_CONF:
      Windows_Clear(YELLOW);
      Windows_SelMenu(Windows_SelMenu_7, WHITE, BLACK);
      break;
    default:
    // ERROR
    break;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void UserInterface_Update( WINDOWS_MENU MenuSel )
{
  u16 ADC_AveTr[6] = {0};

  switch(MenuSel) {

    /************************** FSM CTRL **************************************/
    case WINDOWS_CTRL:    // 主控介面

      break;

    /************************** FSM TRACK *************************************/
    case WINDOWS_TRACK:   // 3D 追蹤

      break;

    /************************** FSM WAVE **************************************/
    case WINDOWS_WAVE:    // 示波器

      break;

    /************************** FSM GPS ***************************************/
    case WINDOWS_GPS:     // GPS 定位

      break;

    /************************** FSM IMAGE *************************************/
    case WINDOWS_IMAGE:   // 影像

      break;

    /************************** FSM TEST **************************************/
    case WINDOWS_TEST:    // 保留
      ADC_Average(ADC_AveTr);
      LCD_PutNum(Axis_ADC_X+8*9, Axis_ADC_Y+16*1, Type_D, 5, ADC_AveTr[0], WHITE, BLACK);
      LCD_PutNum(Axis_ADC_X+8*9, Axis_ADC_Y+16*2, Type_D, 5, ADC_AveTr[1], WHITE, BLACK);
      LCD_PutNum(Axis_ADC_X+8*9, Axis_ADC_Y+16*3, Type_D, 5, ADC_AveTr[2], WHITE, BLACK);
      LCD_PutNum(Axis_ADC_X+8*9, Axis_ADC_Y+16*4, Type_D, 5, ADC_AveTr[3], WHITE, BLACK);
      LCD_PutNum(Axis_ADC_X+8*9, Axis_ADC_Y+16*5, Type_D, 5, ADC_AveTr[4], WHITE, BLACK);
      LCD_PutNum(Axis_ADC_X+8*9, Axis_ADC_Y+16*6, Type_D, 5, ADC_AveTr[5], WHITE, BLACK);
      break;

    /************************** FSM CONF **************************************/
    case WINDOWS_CONF:    // 設定

      break;

    /************************** default ***************************************/
    default:
      // ERROR
      break;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 馬達 Motor */
// MAX_LW = {40,221}
#define Motor_X0	440
#define Motor_Y0	25
static void MenuCtrl_Motor_Init( void )
{
	Windows_PutStr(Motor_X0+16, Motor_Y0+205, (u8*)".", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Motor_X0+32, Motor_Y0+205, (u8*)"%", ASCII1608, WHITE, BLACK);
}
//static void MenuCtrl_Motor( void )
//{
//	u8 i = 0;
//	u16 Tmp_ADC = 0;

//	Tmp_ADC = (u16)((double)(ADC_AveTr[2]-70)/39.5f+0.5f);
//	Tmp_Motor_PWM = (u16)((double)(PWM_Motor-800)/1.2f+0.5f);
//	Data_PL = (u16)(Tmp_Motor_PWM/10);
//	Data_PR = (u16)(Tmp_Motor_PWM%10);

//	if(Data_PL >= 100) {
//		NumToChar(Type_D, 2, PrintTr[4], 99);
//		NumToChar(Type_D, 1, PrintTr[5], 9);
//	}
//	else {
//		NumToChar(Type_D, 2, PrintTr[4], Data_PL);
//		NumToChar(Type_D, 1, PrintTr[5], Data_PR);
//	}
//	Windows_PutStr(Motor_X0, Motor_Y0+205, PrintTr[4], ASCII1608, WHITE, BLACK);
//	Windows_PutStr(Motor_X0+24, Motor_Y0+205, PrintTr[5], ASCII1608, WHITE, BLACK);
//	for(i=0; i<41; i++) {
//		if((i%4)==0) {
//			if(i<=(Data_PL*2/5) && i>27)
//				Windows_DrawRectangleFill(Motor_X0, Motor_Y0+5*(40-i), 32, 3, 0x470000);
//			else if(i<=(Data_PL*2/5))
//				Windows_DrawRectangleFill(Motor_X0, Motor_Y0+5*(40-i), 32, 3, GREEN);
//			else
//				Windows_DrawRectangleFill(Motor_X0, Motor_Y0+5*(40-i), 32, 3, 0x050505);
//		}
//		else {
//			if(i<=(Data_PL*2/5) && i>27)
//				Windows_DrawRectangleFill(Motor_X0+12, Motor_Y0+5*(40-i), 20, 3, 0x470000);
//			else if(i<=(Data_PL*2/5))
//				Windows_DrawRectangleFill(Motor_X0+12, Motor_Y0+5*(40-i), 20, 3, GREEN);
//			else
//				Windows_DrawRectangleFill(Motor_X0+12, Motor_Y0+5*(40-i), 20, 3, 0x050505);
//		}
//	}
//	for(i=0; i<41; i++) {
//		if(i<=(Tmp_ADC*2/5))
//			Windows_DrawRectangleFill(475, 25+5*(40-i), 3, 3, RED);
//		else
//			Windows_DrawRectangleFill(475, 25+5*(40-i), 3, 3, 0x400000);
//	}
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 連線狀況 Connection */
// MAX_LW = {21,15}
#define Connect_X0	10
#define Connect_Y0	5
static void MenuCtrl_Connection_Init( void )
{
	Windows_DrawRectangleFill(Connect_X0, Connect_Y0+10, 5, 5, WHITE);
	Windows_DrawRectangleFill(Connect_X0+8, Connect_Y0+5, 5, 10, WHITE);
	Windows_DrawRectangleFill(Connect_X0+16, Connect_Y0, 5, 15, WHITE);
}
//static void MenuCtrl_Connection( void )
//{
//	if(Connect_Test[0] == Connect_Test[1]) {
//		Windows_DrawRectangleFill(Connect_X0, Connect_Y0+10, 5, 5, WHITE);
//		Windows_DrawRectangleFill(Connect_X0+8, Connect_Y0+5, 5, 10, WHITE);
//		Windows_DrawRectangleFill(Connect_X0+16, Connect_Y0, 5, 15, WHITE);
//	}
//	else {
//		Windows_DrawRectangleFill(Connect_X0, Connect_Y0+10, 5, 5, GREEN);
//		Windows_DrawRectangleFill(Connect_X0+8, Connect_Y0+5, 5, 10, GREEN);
//		Windows_DrawRectangleFill(Connect_X0+16, Connect_Y0, 5, 15, GREEN);
//	}
//	Connect_Test[1] = Connect_Test[0];
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 模式 Mode */
// MAX_LW = {104,20}
#define Mode_X0	46
#define Mode_Y0	0
static void MenuCtrl_Mode_Init( void )
{
	Windows_DrawRectangle(Mode_X0, Mode_Y0, 20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+1, Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+28, Mode_Y0, 20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+29, Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+56, Mode_Y0, 20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+57, Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+84, Mode_Y0, 20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+85, Mode_Y0+1, 18, 18, WHITE);
	Windows_DrawRectangle(Mode_X0+112, Mode_Y0, 20, 20, WHITE);
	Windows_DrawRectangle(Mode_X0+113, Mode_Y0+1, 18, 18, WHITE);
	Windows_PutStr(Mode_X0+7, Mode_Y0+3, (u8*)"F", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+35, Mode_Y0+3, (u8*)"A", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+63, Mode_Y0+3, (u8*)"G", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+91, Mode_Y0+3, (u8*)"C", ASCII1608, WHITE, BLACK);
	Windows_PutStr(Mode_X0+119, Mode_Y0+3, (u8*)"L", ASCII1608, WHITE, BLACK);
}
//static void MenuCtrl_Mode( void )
//{
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 運行時間 WorkTime */
// MAX_LW = {40,16}
#define Time_X0	195
#define Time_Y0	4
static void MenuCtrl_WorkTime_Init( void )
{
	Windows_PutStr(Time_X0+16, Time_Y0, (u8*)":", ASCII1608, WHITE, BLACK);
}
//static void MenuCtrl_WorkTime( void )
//{
//	u8 PrintTr[2][4];

//	NumToChar(Type_D, 2, PrintTr[0], Time_Sec);
//	NumToChar(Type_D, 2, PrintTr[1], Time_Min);
//	Windows_PutStr(Time_X0, Time_Y0, PrintTr[1], ASCII1608, WHITE, BLACK);
//	Windows_PutStr(Time_X0+24, Time_Y0, PrintTr[0], ASCII1608, WHITE, BLACK);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
/* 電池電量 BatteryPower */
#define Power_X0	440
#define Power_Y0	0
static void MenuCtrl_Power_Init( void )
{
	Windows_DrawRectangleFill(Power_X0+3, Power_Y0,   31, 20, WHITE);
	Windows_DrawRectangleFill(Power_X0,   Power_Y0+6,  3,  8, WHITE);
	Windows_DrawRectangleFill(Power_X0+7, Power_Y0+3, 23, 14, BLACK);
}
//static void MenuCtrl_Power( void )
//{
//	Windows_DrawRectangleFill(Power_X0+9,  Power_Y0+5, 5, 10, GREEN);
//	Windows_DrawRectangleFill(Power_X0+16, Power_Y0+5, 5, 10, GREEN);
//	Windows_DrawRectangleFill(Power_X0+23, Power_Y0+5, 5, 10, GREEN);
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
