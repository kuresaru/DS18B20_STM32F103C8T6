#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "lcd.h"

//液晶IO初始化配置
void LCD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;//SPI3 SCK MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11 | GPIO_Pin_10;//CS RS LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  
	SPI_StructInit(&SPI_InitStructure);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_Init(SPI2, &SPI_InitStructure);

	SPI_Cmd(SPI2, ENABLE);
}
//向SPI总线传输一个8位数据
void  SPI_WriteData(u8 data)
{
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
	SPI_I2S_SendData(SPI2, data);
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) != RESET);
}

//向液晶屏写一个8位指令
void LCD_Cmd(u8 cmd)
{
   //SPI 写命令时序开始
   LCD_CS = 0;
   LCD_RS = 0;
	 SPI_WriteData(cmd);
   LCD_CS = 1;
}

//向液晶屏写一个8位数据
void LCD_Data(u8 data)
{
   LCD_CS = 0;
   LCD_RS = 1;
   SPI_WriteData(data);
   LCD_CS = 1; 
}
//向液晶屏写一个16位数据
void LCD_Data16(u16 data)
{
   LCD_CS = 0;
   LCD_RS = 1;
	 SPI_WriteData(data>>8); 	//写入高8位数据
	 SPI_WriteData(data); 			//写入低8位数据
   LCD_CS = 1; 
}

void Lcd_WriteReg(u8 cmd,u8 data)
{
	LCD_Cmd(cmd);
  LCD_Data(data);
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void LCD_Init(void)
{	
	LCD_GPIO_Init();

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	LCD_Cmd(0x11);//Sleep exit 
	Delay_ms (120);
		
	//ST7735R Frame Rate
	LCD_Cmd(0xB1); 
	LCD_Data(0x01); 
	LCD_Data(0x2C); 
	LCD_Data(0x2D); 

	LCD_Cmd(0xB2); 
	LCD_Data(0x01); 
	LCD_Data(0x2C); 
	LCD_Data(0x2D); 

	LCD_Cmd(0xB3); 
	LCD_Data(0x01); 
	LCD_Data(0x2C); 
	LCD_Data(0x2D); 
	LCD_Data(0x01); 
	LCD_Data(0x2C); 
	LCD_Data(0x2D); 
	
	LCD_Cmd(0xB4); //Column inversion 
	LCD_Data(0x07); 
	
	//ST7735R Power Sequence
	LCD_Cmd(0xC0); 
	LCD_Data(0xA2); 
	LCD_Data(0x02); 
	LCD_Data(0x84); 
	LCD_Cmd(0xC1); 
	LCD_Data(0xC5); 

	LCD_Cmd(0xC2); 
	LCD_Data(0x0A); 
	LCD_Data(0x00); 

	LCD_Cmd(0xC3); 
	LCD_Data(0x8A); 
	LCD_Data(0x2A); 
	LCD_Cmd(0xC4); 
	LCD_Data(0x8A); 
	LCD_Data(0xEE); 
	
	LCD_Cmd(0xC5); //VCOM 
	LCD_Data(0x0E); 
	
	LCD_Cmd(0x36); //MX, MY, RGB mode 
	LCD_Data(0xC8); 
	
	//ST7735R Gamma Sequence
	LCD_Cmd(0xe0); 
	LCD_Data(0x0f); 
	LCD_Data(0x1a); 
	LCD_Data(0x0f); 
	LCD_Data(0x18); 
	LCD_Data(0x2f); 
	LCD_Data(0x28); 
	LCD_Data(0x20); 
	LCD_Data(0x22); 
	LCD_Data(0x1f); 
	LCD_Data(0x1b); 
	LCD_Data(0x23); 
	LCD_Data(0x37); 
	LCD_Data(0x00); 	
	LCD_Data(0x07); 
	LCD_Data(0x02); 
	LCD_Data(0x10); 

	LCD_Cmd(0xe1); 
	LCD_Data(0x0f); 
	LCD_Data(0x1b); 
	LCD_Data(0x0f); 
	LCD_Data(0x17); 
	LCD_Data(0x33); 
	LCD_Data(0x2c); 
	LCD_Data(0x29); 
	LCD_Data(0x2e); 
	LCD_Data(0x30); 
	LCD_Data(0x30); 
	LCD_Data(0x39); 
	LCD_Data(0x3f); 
	LCD_Data(0x00); 
	LCD_Data(0x07); 
	LCD_Data(0x03); 
	LCD_Data(0x10);  
	
	LCD_Cmd(0x2a);
	LCD_Data(0x00);
	LCD_Data(0x00);
	LCD_Data(0x00);
	LCD_Data(0x7f);

	LCD_Cmd(0x2b);
	LCD_Data(0x00);
	LCD_Data(0x00);
	LCD_Data(0x00);
	LCD_Data(0x9f);
	
	LCD_Cmd(0xF0); //Enable test command  
	LCD_Data(0x01); 
	LCD_Cmd(0xF6); //Disable ram power save mode 
	LCD_Data(0x00); 
	
	LCD_Cmd(0x3A); //65k mode 
	LCD_Data(0x05); 
	
	
	LCD_Cmd(0x29);//Display on	 
}

void LCD_Start()
{
	LCD_Cmd(0x2C);
}
void LCD_SetWindow(u16 x, u16 xsize, u16 y, u16 ysize)
{
	x += ScreenX0;
	y += ScreenY0;
	LCD_Cmd(0x2A);
	LCD_Data(x >> 8);
	LCD_Data(x);
	x = x + xsize - 1;
	LCD_Data(x >> 8);
	LCD_Data(x);

	LCD_Cmd(0x2B);
	LCD_Data(y >> 8);
	LCD_Data(y);
	y = y + ysize - 1;
	LCD_Data(y >> 8);
	LCD_Data(y);
}
// Fill rectangle area with given color
void LCD_Fill(s16 x, s16 y, s16 xsize, s16 ysize, u16 color)
{
	u32 tmp;
	LCD_SetWindow(x, xsize, y, ysize);
	LCD_Start();
	tmp = (u32)xsize * (u32)ysize;
	while (tmp--)
	{
		LCD_Data((color >> 8) & 0xFF);
		LCD_Data(color & 0xFF);
	}
}
// Clear screen
void LCD_Cls(void)
{
	LCD_Fill(0, 0, ScreenXsize, ScreenYsize, clBlack);
}
