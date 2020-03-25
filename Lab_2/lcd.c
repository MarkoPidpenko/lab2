#include "lcd.h"


const unsigned char lcdAddLut[2] = {0x80, 0xC0};
unsigned char address, currentLine;

void lcdPinInit(void) {
	GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = LCD_PIN_RS | LCD_PIN_RW | LCD_PIN_EN | LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_RW);
}


void lcdWriteByte(uint8_t data) {
	GPIO_SetBits(LCD_PORT, ((data & 0x0F)) << LCD_PIN_OFFSET);
	GPIO_SetBits(LCD_PORT, LCD_PIN_EN);
	lcd_delay_func(100);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_EN);
	GPIO_ResetBits(LCD_PORT, 0x0F<<LCD_PIN_OFFSET);
	
	GPIO_SetBits(LCD_PORT, (((data>>4) & 0x0F)) << LCD_PIN_OFFSET);
	GPIO_SetBits(LCD_PORT, LCD_PIN_EN);
	lcd_delay_func(100);
	GPIO_ResetBits(LCD_PORT, LCD_PIN_EN);
	GPIO_ResetBits(LCD_PORT, 0x0F<<LCD_PIN_OFFSET);
}

void lcdInit(void) {
	lcdWriteByte(0x20);
	lcd_delay_func(100);
	lcdWriteByte(0x28);
	lcd_delay_func(100);
	lcdWriteByte(0x28);
	lcd_delay_func(100);
	lcdWriteByte(0x0f);
	lcd_delay_func(100);
	lcdWriteByte(0x01);
	lcd_delay_func(100);
	lcdWriteByte(0x06);
	lcd_delay_func(100);
}


void lcd_delay_func(unsigned int p) {
	unsigned long i;
	for(i=0;i<(p*10);i++){
	  __nop();
	}
}

void lcdSetLine(char line) {
		GPIO_ResetBits(LCD_PORT, LCD_PIN_RS);
		address = lcdAddLut[line-1];
		lcdWriteByte(address);
		GPIO_SetBits(LCD_PORT, LCD_PIN_RS);
		address = 0;
		currentLine = line;
}

void lcdClear(void) {
		GPIO_ResetBits(LCD_PORT, LCD_PIN_RS);
		lcdWriteByte(0x01);
		lcd_delay_func(100);
		GPIO_SetBits(LCD_PORT, LCD_PIN_RS);
		lcdSetLine(1);
}

void lcdShowChar(char c) {
	GPIO_SetBits(LCD_PORT, LCD_PIN_RS);
	lcdWriteByte(c);
	address++;
	switch (address)
	{
		case 20: lcdSetLine(2); break;
		case 40: lcdSetLine(3); break;
		case 60: lcdSetLine(4); break;
		case 80: lcdSetLine(1); break;
	}
}

void lcdShowString(char *s)
{
	while (*s != 0) lcdShowChar(*s++);
}




