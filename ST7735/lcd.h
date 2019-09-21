#ifndef __LCD_H
#define __LCD_H

#include "common.h"
#include "color.h"

#define ScreenX0 2
#define ScreenY0 3
#define ScreenXsize 128
#define ScreenYsize 128

#define LCD_CS PBout(12)
#define LCD_RS PBout(11)
#define LCD_LED PBout(10)

void LCD_Init(void);
void LCD_Cmd(u8 cmd);
void LCD_Data(u8 data);
void LCD_Data16(u16 data);
void LCD_Cls(void);
void LCD_Start();
void LCD_SetWindow(u16 x, u16 xsize, u16 y, u16 ysize);

#endif