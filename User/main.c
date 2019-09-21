#include "common.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "ds18b20.h"
#include "buzzer.h"
#include "lcd.h"
#include "lcdstr.h"
#include "stm32f10x_tim.h"
#include <stdio.h>

#define LED PCout(13)

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	BUZZER_InitTIM3();
	BUZZER_InitTIM2CH2();

	LCD_Init();
	LCD_Cls();
	LCD_LED = 1;

	LCD_WriteString(0, 0, "DS18B20 Test.", clAqua, clBlack);

	LED = 0;
	while (DS18B20_Init())
	{
		LCD_WriteString(0, 16, "Init Error.", clRed, clBlack);
		Delay_ms(10);
	}
	LED = 1;
	LCD_WriteString(0, 16, "Init OK.   ", clGreen, clBlack);
	LCD_WriteString(0, 16 * 2, "Temp", clWhite, clBlack);
	char buf[16];
	while (1)
	{
		short temp = DS18B20_Get_Temp();
		if (temp < 0)
		{
			temp = -temp;
			sprintf(buf, "Temp -%03d.%dC", temp / 10, temp % 10);
		}
		else
		{
			if (temp > 300)
				BUZZER_Cmd(ENABLE);
			else
				BUZZER_Cmd(DISABLE);
			sprintf(buf, "Temp  %03d.%dC", temp / 10, temp % 10);
		}
		LCD_WriteString(0, 16 * 2, buf, clWhite, clBlack);
		Delay_ms(500);
	}
}
