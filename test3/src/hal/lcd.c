
#include "lcd.h"
#include <util/twi.h>
#include <util/delay.h>

static uint8_t displayControl;
static uint8_t displayMode;

uint8_t lcd_write(uint8_t val)
{

    unsigned char dta[2] = {0x40, val};
    i2c_writeStream(dta, 2);

    return 1;
}

uint8_t lcd_writeStream(uint8_t *arra, short unsigned int length)
{
    i2c_start_wait(LCD_ADDR);

    short unsigned int i = 1;
    uint8_t dta[length + 1];
    dta[0] = 0x40;
    while (i < length + 1)
    {
        dta[i] = *(arra + (i - 1));
        i++;
    }
    i2c_writeStream(dta, length + 1);

    i2c_stop();

    return 0;
}

void lcd_command(uint8_t commandVal)
{
    unsigned char dta[2] = {0x80, commandVal};
    i2c_writeStream(dta, 2);
}

void lcd_display(void)
{
    i2c_start(LCD_ADDR);
    displayControl &= ~LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | displayControl);
    i2c_stop();
}

void lcd_initialize(uint8_t addr)
{
    uint8_t funcSetArra[4];
    funcSetArra[0] = 0x28;
    funcSetArra[1] = 0xF;
    funcSetArra[2] = 0x01;
    funcSetArra[3] = 0x01;
    i2c_init();
    i2c_start(addr);
    _delay_ms(100);
    i2c_writeStream(funcSetArra, 4);
    i2c_stop();
}

void lcd_clear(void)
{
    i2c_start(LCD_ADDR);

    lcd_command(LCD_CLEARDISPLAY);
    _delay_ms(2000);
    i2c_stop();
}

void lcd_setCursor(uint8_t col, uint8_t row)
{
    i2c_start(LCD_ADDR);
    col = (row == 0 ? col | 0x80 : col | 0xc0);
    unsigned char dta[2] = {0x80, col};

    i2c_writeStream(dta, 2);
    i2c_stop();
}

void lcd_leftJustify_cursor(void)
{
    i2c_start(LCD_ADDR);
    displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | displayMode);
    i2c_stop();
}

void lcd_rightJustify_cursor(void)
{
    i2c_start(LCD_ADDR);
    displayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    lcd_command(LCD_ENTRYMODESET | displayMode);
    i2c_stop();
}

//For text that flows left < right
void lcd_rightToLeft_text(void)
{
    i2c_start(LCD_ADDR);
    displayMode &= ~LCD_ENTRYLEFT;
    lcd_command(LCD_ENTRYMODESET | displayMode);
    i2c_stop();
}

//For text that flows left > right
void lcd_leftToRight_text(void)
{
    i2c_start(LCD_ADDR);
    displayMode |= LCD_ENTRYLEFT;

    lcd_command(LCD_ENTRYMODESET | displayMode);
    i2c_stop();
}
//These two functions shift the display without changing the RAM
void lcd_scrollDisplayLEFT(void)
{
    i2c_start(LCD_ADDR);
    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
    i2c_stop();
}

void lcd_scrollDisplayRIGHT(void)
{
    i2c_start(LCD_ADDR);
    lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
    i2c_stop();
}

void lcd_cursorBlinkON(void)
{
    i2c_start(LCD_ADDR);
    displayControl &= ~LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | displayControl);
    i2c_stop();
}

void lcd_cursorBlinkOFF(void)
{
    i2c_start(LCD_ADDR);
    displayControl |= LCD_BLINKON;
    lcd_command(LCD_DISPLAYCONTROL | displayControl);
    i2c_stop();
}

void lcd_cursorON(void)
{
    i2c_start(LCD_ADDR);
    displayControl |= LCD_CURSORON;

    lcd_command(LCD_DISPLAYCONTROL | displayControl);
    i2c_stop();
}

void lcd_cursorOFF(void)
{
    i2c_start(LCD_ADDR);
    displayControl &= ~LCD_CURSORON;

    lcd_command(LCD_DISPLAYCONTROL | displayControl);
    i2c_stop();
}
