/* #include "algorithm_bitmap.h" */

#ifndef __ALGORITHM_BITMAP_H
#define __ALGORITHM_BITMAP_H

#include "stm32f4xx.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
// BMP檔案 = 標頭 + 調色盤 + 影像資料
typedef struct {

  // Bitmap File Header
  u16 Identifier;       // 固定為'BM'
  u32 FileSize;         // 檔案大小
  u32 Reserved;         // 保留
  u32 DataOffset;       // 影像資料在檔案中的位置

  // Bitmap Info Header
  u32 HeaderSize;       // Bitmap Info Header長度, 0x28=Windows, 0x0C=OS/2 1.x, 0xF0=OS/2 2.x
  u32 Width;            // 影像寬度
  u32 Height;           // 影像高度
  u16 Planes;           // 色彩平面數,固定為1
  u16 BitsPerPixel;     // 每點位元數, 1=(2色調色盤), 4=(16色調色盤), 8=(246色調色盤)
                        //             16=(不一定使用調色盤), 24=(不使用調色盤), 32=(不一定使用調色盤)
  u32 Compression;      // 壓縮方式, 0=不壓縮, 1=RLE8(256色), 2=RLE4(16色)
  u32 DataSize;         // 影像資料大小
  u32 H_Resolution;     // 水平解析度(per meter)
  u32 V_Resolution;     // 垂直解析度(per meter)
  u32 UsedColors;       // 實際使用的顏色數, 0：Bit_Count決定
  u32 ImportantColors;  // 重要的色彩數目, 0：都重要

} BmpHeader;
/*=====================================================================================================*/
/*=====================================================================================================*/
void BMP_ReadInfo( BmpHeader* BMP_Header, u8* ReadData );
void BMP_WriteInfo( BmpHeader* BMP_Header, u8* WriteData );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif	
