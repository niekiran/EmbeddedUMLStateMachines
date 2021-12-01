#ifndef LCD_H
#define LCD_H
#include<Arduino.h>

void lcd_clear(void);
void lcd_print_char(char c);
void lcd_scroll_left(void);
void lcd_scroll_right(void);
void lcd_set_cursor(int c, int r);
void lcd_no_auto_scroll(void);
void lcd_begin(uint8_t cols, uint8_t rows);
void lcd_move_cursor_R_to_L(void);
void lcd_move_cursor_L_to_R(void);
void lcd_cursor_off(void);
void lcd_cursor_blinkoff(void);
void lcd_print_number(int num);
void lcd_print_string(String s);
void lcd_cursor_blink(void);
void lcd_cursor_show(void);

#endif 