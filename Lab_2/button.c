#include "button.h"

void userButtonInit(void)
{
	GPIO_InitTypeDef GPIO_Init_Button;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Init_Button.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Button.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Button.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_Init_Button);
}
