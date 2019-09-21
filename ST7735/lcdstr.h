#ifndef __LCDSTR_H
#define __LCDSTR_H

#include "common.h"
#include "lcd.h"

void LCD_WriteChar(u16 x, u16 y, char ch, u16 fgcolor, u16 bgcolor);
void LCD_WriteString(u16 x, u16 y, char *str, u16 fgcolor, u16 bgcolor);

#endif