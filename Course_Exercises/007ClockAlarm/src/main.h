#ifndef MAIN_H
#define MAIN_H

#define PIN_BUTTON1 2
#define PIN_BUTTON2 3
#define PIN_BUZZER  12

#define BTN_PAD_VALUE_SET       2
#define BTN_PAD_VALUE_OK        1
#define BTN_PAD_VALUE_ABRT      3


typedef enum{
    NOT_PRESSED,
    BOUNCE,
    PRESSED
}button_state_t;



#endif