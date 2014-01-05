/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "algorithm_bitmap.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : BMP_ReadInfo
**功能 : Read BMP Header Info
**輸入 : BMP_Header, WriteData
**輸出 : None
**使用 : BMP_ReadInfo(&BMP_HEADER, BitmapHeader);
**=====================================================================================================*/
/*=====================================================================================================*/
void BMP_ReadInfo( BmpHeader* BMP_Header, u8* ReadData )
{
  BMP_Header->Identifier      = ReadData[0]<<8   | ReadData[1];
  BMP_Header->FileSize        = ReadData[5]<<24  | ReadData[4]<<16  | ReadData[3]<<8  | ReadData[2];
  BMP_Header->Reserved        = ReadData[9]<<24  | ReadData[8]<<16  | ReadData[7]<<8  | ReadData[6];
  BMP_Header->DataOffset      = ReadData[13]<<24 | ReadData[12]<<16 | ReadData[11]<<8 | ReadData[10];

  BMP_Header->HeaderSize      = ReadData[17]<<24 | ReadData[16]<<16 | ReadData[15]<<8 | ReadData[14];
  BMP_Header->Width           = ReadData[21]<<24 | ReadData[20]<<16 | ReadData[19]<<8 | ReadData[18];
  BMP_Header->Height          = ReadData[25]<<24 | ReadData[24]<<16 | ReadData[23]<<8 | ReadData[22];
  BMP_Header->Planes          = ReadData[27]<<8  | ReadData[26];
  BMP_Header->BitsPerPixel    = ReadData[29]<<8  | ReadData[28];

  BMP_Header->Compression     = ReadData[33]<<24 | ReadData[32]<<16 | ReadData[31]<<8 | ReadData[30];
  BMP_Header->DataSize        = ReadData[37]<<24 | ReadData[36]<<16 | ReadData[35]<<8 | ReadData[34];
  BMP_Header->H_Resolution    = ReadData[41]<<24 | ReadData[40]<<16 | ReadData[39]<<8 | ReadData[38];
  BMP_Header->V_Resolution    = ReadData[45]<<24 | ReadData[44]<<16 | ReadData[43]<<8 | ReadData[42];
  BMP_Header->UsedColors      = ReadData[49]<<24 | ReadData[48]<<16 | ReadData[47]<<8 | ReadData[46];
  BMP_Header->ImportantColors = ReadData[53]<<24 | ReadData[52]<<16 | ReadData[51]<<8 | ReadData[50];
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : BMP_WriteInfo
**功能 : Write BMP Header Info
**輸入 : BMP_Header, WriteData
**輸出 : None
**使用 : BMP_WriteInfo(&BMP_HEADER, BitmapHeader);
**=====================================================================================================*/
/*=====================================================================================================*/
void BMP_WriteInfo( BmpHeader* BMP_Header, u8* WriteData )
{
  WriteData[0]  = (u8)(BMP_Header->Identifier>>8);
  WriteData[1]  = (u8)(BMP_Header->Identifier);
  WriteData[2]  = (u8)(BMP_Header->FileSize>>24);
  WriteData[3]  = (u8)(BMP_Header->FileSize>>16);
  WriteData[4]  = (u8)(BMP_Header->FileSize>>8);
  WriteData[5]  = (u8)(BMP_Header->FileSize);
  WriteData[6]  = (u8)(BMP_Header->Reserved);
  WriteData[7]  = (u8)(BMP_Header->Reserved>>8);
  WriteData[8]  = (u8)(BMP_Header->Reserved>>16);
  WriteData[9]  = (u8)(BMP_Header->Reserved>>24);
  WriteData[10] = (u8)(BMP_Header->DataOffset);
  WriteData[11] = (u8)(BMP_Header->DataOffset>>8);
  WriteData[12] = (u8)(BMP_Header->DataOffset>>16);
  WriteData[13] = (u8)(BMP_Header->DataOffset>>24);
  WriteData[14] = (u8)(BMP_Header->HeaderSize);
  WriteData[15] = (u8)(BMP_Header->HeaderSize>>8);
  WriteData[16] = (u8)(BMP_Header->HeaderSize>>16);
  WriteData[17] = (u8)(BMP_Header->HeaderSize>>24);
  WriteData[18] = (u8)(BMP_Header->Width);
  WriteData[19] = (u8)(BMP_Header->Width>>8);
  WriteData[20] = (u8)(BMP_Header->Width>>16);
  WriteData[21] = (u8)(BMP_Header->Width>>24);
  WriteData[22] = (u8)(BMP_Header->Height);
  WriteData[23] = (u8)(BMP_Header->Height>>8);
  WriteData[24] = (u8)(BMP_Header->Height>>16);
  WriteData[25] = (u8)(BMP_Header->Height>>24);
  WriteData[26] = (u8)(BMP_Header->Planes);
  WriteData[27] = (u8)(BMP_Header->Planes>>8);
  WriteData[28] = (u8)(BMP_Header->BitsPerPixel);
  WriteData[29] = (u8)(BMP_Header->BitsPerPixel>>8);

  WriteData[30] = (u8)(BMP_Header->Compression);
  WriteData[31] = (u8)(BMP_Header->Compression>>8);
  WriteData[32] = (u8)(BMP_Header->Compression>>16);
  WriteData[33] = (u8)(BMP_Header->Compression>>24);

  WriteData[34] = (u8)(BMP_Header->DataSize);
  WriteData[35] = (u8)(BMP_Header->DataSize>>8);
  WriteData[36] = (u8)(BMP_Header->DataSize>>16);
  WriteData[37] = (u8)(BMP_Header->DataSize>>24);

  WriteData[38] = (u8)(BMP_Header->H_Resolution);
  WriteData[39] = (u8)(BMP_Header->H_Resolution>>8);
  WriteData[40] = (u8)(BMP_Header->H_Resolution>>16);
  WriteData[41] = (u8)(BMP_Header->H_Resolution>>24);

  WriteData[42] = (u8)(BMP_Header->V_Resolution);
  WriteData[43] = (u8)(BMP_Header->V_Resolution>>8);
  WriteData[44] = (u8)(BMP_Header->V_Resolution>>16);
  WriteData[45] = (u8)(BMP_Header->V_Resolution>>24);

  WriteData[46] = (u8)(BMP_Header->UsedColors);
  WriteData[47] = (u8)(BMP_Header->UsedColors>>8);
  WriteData[48] = (u8)(BMP_Header->UsedColors>>16);
  WriteData[49] = (u8)(BMP_Header->UsedColors>>24);

  WriteData[50] = (u8)(BMP_Header->ImportantColors);
  WriteData[51] = (u8)(BMP_Header->ImportantColors>>8);
  WriteData[52] = (u8)(BMP_Header->ImportantColors>>16);
  WriteData[53] = (u8)(BMP_Header->ImportantColors>>24);

}
/*=====================================================================================================*/
/*=====================================================================================================*/
