/**
 ******************************************************************************
 * @file    fonts.h
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    18-February-2014
 * @brief   Header for fonts.c file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FONTS_H
#define __FONTS_H

/* Max size of bitmap will based on a font24 (17x24) */
#define MAX_HEIGHT_FONT 63
#define MAX_WIDTH_FONT 40
#define OFFSET_BITMAP 54

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
  // #include <avr/pgmspace.h>
  // ASCII
  typedef struct _tFont
  {
    const uint8_t *table;
    uint16_t Width;
    uint16_t Height;

  } sFONT;

  // GB2312
  typedef struct // 汉字字模数据结构
  {
    unsigned char index[3];                                  // 汉字内码索引
    const char matrix[MAX_HEIGHT_FONT * MAX_WIDTH_FONT / 8]; // 点阵码数据
  } CH_CN;

  typedef struct
  {
    const CH_CN *table;
    uint16_t size;
    uint16_t ASCII_Width;
    uint16_t Width;
    uint16_t Height;

  } cFONT;

  // extern sFONT Font24;
  // extern sFONT Font20;
  // extern sFONT Font16;
  // extern sFONT Font12;
  // extern sFONT Font8;
  // extern sFONT testFont48;

  // Tisch Dashboard fonts 
  // Orbitron Regular
  extern sFONT OrbitronRegular8;
  extern sFONT OrbitronRegular12;
  extern sFONT OrbitronRegular16;
  extern sFONT OrbitronRegular20;
  extern sFONT OrbitronRegular24;
  extern sFONT OrbitronRegular30;
  extern sFONT OrbitronRegular35;
  extern sFONT OrbitronRegular40;
  extern sFONT OrbitronRegular45;
  extern sFONT OrbitronRegular50;
  extern sFONT OrbitronRegular55;
  extern sFONT OrbitronRegular60;

  // Orbitron Bold
  extern sFONT OrbitronBold10;
  extern sFONT OrbitronBold12;
  extern sFONT OrbitronBold16;
  extern sFONT OrbitronBold18;
  extern sFONT OrbitronBold20;
  extern sFONT OrbitronBold22;
  extern sFONT OrbitronBold25;
  extern sFONT OrbitronBold40;
  extern sFONT OrbitronBold45;
  extern sFONT OrbitronBold50;
  extern sFONT OrbitronBold55;
  extern sFONT OrbitronBold60;
  extern sFONT OrbitronBold65;
  extern sFONT OrbitronBold70;


  // extern cFONT Font12CN;
  // extern cFONT Font24CN;
  // extern const unsigned char Font16_Table[];

#ifdef __cplusplus
}
#endif

#endif /* __FONTS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
