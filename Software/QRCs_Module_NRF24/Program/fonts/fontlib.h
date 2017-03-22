/**
  *      __            ____
  *     / /__ _  __   / __/                      __  
  *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
  *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
  *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
  *                    /_/   github.com/KitSprout    
  * 
  * @file    fontlib.h
  * @author  KitSprout
  * @date    16-Mar-2017
  * @brief   
  * 
  */

/* Define to prevent recursive inclusion ---------------------------------------------------*/
#ifndef __FONTLIB_H
#define __FONTLIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types --------------------------------------------------------------------------*/
typedef enum {
  dirH,
  dirV
} eFontType;

typedef struct {    
  const uint8_t *table;
  uint8_t height;
  uint8_t width;
  eFontType type;
} sFONT;

/* Exported constants ----------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------*/  

extern sFONT Font8x6;
extern sFONT Font16x8;

#ifdef __cplusplus
}
#endif

#endif

/*************************************** END OF FILE ****************************************/
