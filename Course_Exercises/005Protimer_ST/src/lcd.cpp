

#include "lcd.h"
#include "main.h"
#include<LiquidCrystal.h>

LiquidCrystal lcd(PIN_LCD_RS,PIN_LCD_RW,PIN_LCD_EN,PIN_LCD_D4,PIN_LCD_D5,PIN_LCD_D6,PIN_LCD_D7);

void lcd_clear(void){
    lcd.clear();
}
void lcd_print_char(char c){
    lcd.print(c);
}

void lcd_scroll_left(void){
    lcd.scrollDisplayLeft();
}
void lcd_scroll_right(void){
    lcd.scrollDisplayRight();
}
void lcd_set_cursor(int c, int r){
    lcd.setCursor(c,r);
}
void lcd_no_auto_scroll(void){
    lcd.noAutoscroll();
}
void lcd_begin(uint8_t cols , uint8_t rows){
    lcd.begin(cols,rows);
}
void lcd_move_cursor_R_to_L(void){
    lcd.rightToLeft();
}
void lcd_move_cursor_L_to_R(void){
    lcd.leftToRight();
}
void lcd_cursor_off(void){
    lcd.noCursor();
}
void lcd_cursor_blinkoff(void){
    lcd.noBlink();
}
void lcd_print_number(int num){
    lcd.print(num);
}
void lcd_print_string(String s){
    lcd.print(s);
}

void lcd_cursor_show(void)
{
    lcd.cursor();
}

void lcd_cursor_blink(void)
{
    lcd.blink();
}