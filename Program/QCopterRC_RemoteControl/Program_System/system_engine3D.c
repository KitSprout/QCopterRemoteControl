/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "system_engine3D.h"
#include "algorithm_mathUnit.h"
#include "algorithm_quaternion.h"
///*=====================================================================================================*/
///*=====================================================================================================*/
//void Engine3D_RotateX( s16 Angle, s16 *Coordinate )
//{
//	s16 Temp[2] = {0};
//	float TempSin = 0.0f;
//	float TempCos = 0.0f;

//	TempSin = arm_sin_f32(toRad(Angle));
//	TempCos = arm_cos_f32(toRad(Angle));

//	Temp[0] = (s16)((float)Coordinate[1]*TempCos - (float)Coordinate[2]*TempSin+0.5f);
//	Temp[1] = (s16)((float)Coordinate[2]*TempCos + (float)Coordinate[1]*TempSin+0.5f);

//	Coordinate[1] = Temp[0];
//	Coordinate[2] = Temp[1];
//}
///*=====================================================================================================*/
///*=====================================================================================================*/
//void Engine3D_RotateY( s16 Angle, s16 *Coordinate )
//{
//	s16 Temp[2] = {0};
//	float TempSin = 0.0f;
//	float TempCos = 0.0f;

//	TempSin = arm_sin_f32(toRad(Angle));
//	TempCos = arm_cos_f32(toRad(Angle));

//	Temp[0] = (s16)((float)Coordinate[0]*TempCos + (float)Coordinate[2]*TempSin + 0.5f);
//	Temp[1] = (s16)((float)Coordinate[2]*TempCos - (float)Coordinate[0]*TempSin + 0.5f);

//	Coordinate[0] = Temp[0];
//	Coordinate[2] = Temp[1];
//}
///*=====================================================================================================*/
///*=====================================================================================================*/
//void Engine3D_RotateZ( s16 Angle, s16 *Coordinate )
//{
//	s16 Temp[2] = {0};
//	float TempSin = 0.0f;
//	float TempCos = 0.0f;

//	TempSin = arm_sin_f32(toRad(Angle));
//	TempCos = arm_cos_f32(toRad(Angle));

//	Temp[0] = (s16)((float)Coordinate[0]*TempCos - (float)Coordinate[1]*TempSin + 0.5f);
//	Temp[1] = (s16)((float)Coordinate[1]*TempCos + (float)Coordinate[0]*TempSin + 0.5f);

//	Coordinate[0] = Temp[0];
//	Coordinate[1] = Temp[1];
//}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Engine3D_RotateByDCM
**功能 : 利用方向餘弦矩陣 DCM 旋轉
**輸入 : *Vect, *pAngE
**輸出 : None
**使用 : Engine3D_RotateByDCM(&Vect, &AngE);
**=====================================================================================================*/
/*=====================================================================================================*/
void Engine3D_RotateByDCM( VECTOR_ST *Vect, EulerAngle *pAngE )
{
  VECTOR_ST tempVect = {0};

  float SinP = arm_sin_f32(toRad(pAngE->Pitch));
  float CosP = arm_cos_f32(toRad(pAngE->Pitch));
  float SinR = arm_sin_f32(toRad(pAngE->Roll));
  float CosR = arm_cos_f32(toRad(pAngE->Roll));
  float SinY = arm_sin_f32(toRad(pAngE->Yaw));
  float CosY = arm_cos_f32(toRad(pAngE->Yaw));

  tempVect.X = CosR*CosY*Vect->X + CosR*SinY*Vect->Y - SinR*Vect->Z;
  tempVect.Y = (CosY*SinP*SinR-CosP*SinY)*Vect->X + (SinP*SinR*SinY+CosP*CosY)*Vect->Y + CosR*SinP*Vect->Z;
  tempVect.Z = (CosP*CosY*SinR+SinP*SinY)*Vect->X + (CosP*SinR*SinY-CosY*SinP)*Vect->Y + CosP*CosR*Vect->Z;

  Vect->X = tempVect.X;
  Vect->Y = tempVect.Y;
  Vect->Z = tempVect.Z;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Engine3D_Scaling
**功能 : 縮放
**輸入 : Vect, *VectScal
**輸出 : None
**使用 : Engine3D_Scaling(&Vect, &VectScal);
**=====================================================================================================*/
/*=====================================================================================================*/
void Engine3D_Scaling( VECTOR_ST *Vect, VECTOR_ST *VectScal )
{
  Vect->X = Vect->X * VectScal->X;
  Vect->Y = Vect->Y * VectScal->Y;
  Vect->Z = Vect->Z * VectScal->Z;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Engine3D_Move
**功能 : 移動
**輸入 : Vect, *VectMove
**輸出 : None
**使用 : Engine3D_Move(&Vect, &VectMove);
**=====================================================================================================*/
/*=====================================================================================================*/
void Engine3D_Move( VECTOR_ST *Vect, VECTOR_ST *VectMove )
{
  Vect->X = Vect->X + VectMove->X;
  Vect->Y = Vect->Y + VectMove->Y;
  Vect->Z = Vect->Z + VectMove->Z;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Engine3D_RotateByNumQ
**功能 : 利用方向餘弦矩陣 DCM 旋轉
**輸入 : *VectE, VectS, *pAngE
**輸出 : FinalCordi
**使用 : Engine3D_RotateByNumQ(&VectE, VectS, &AngE);
**=====================================================================================================*/
/*=====================================================================================================*/
void Engine3D_RotateByNumQ( Quaternion *pNumQ, EulerAngle *pAngE, float* Cordi )
{
  EulerAngle tempAngE = {0};
  Quaternion tempNumQ = {0};

  Quaternion_ToNumQ(&tempNumQ, pAngE);
  Quaternion_Multiply(pNumQ, pNumQ, &tempNumQ);
  Quaternion_ToAngE(pNumQ, &tempAngE);

}
/*=====================================================================================================*/
/*=====================================================================================================*/
