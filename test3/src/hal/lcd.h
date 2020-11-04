#include "i2c.h"

#define LCD_ADDR ((0x7c) | 0)

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

void lcd_command(uint8_t);

void lcd_display(void);

void lcd_initialize(uint8_t);

void lcd_clear(void);

uint8_t lcd_write(uint8_t);

uint8_t lcd_writeStream(uint8_t *, short unsigned int);

void lcd_setCursor(uint8_t, uint8_t);

void lcd_cursorOFF(void);

void lcd_cursorON(void);

void lcd_cursorBlinkOFF(void);

void lcd_cursorBlinkOn(void);

void lcd_scrollDisplayRIGHT(void);

void lcd_scrollDisplayLEFT(void);

void lcd_leftToRight_text(void);

void lcd_rightToLeft_text(void);

void lcd_leftJustify_cursor(void);

void lcd_rightJustify_cursor(void);
