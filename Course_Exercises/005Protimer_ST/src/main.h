
#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>


#define PIN_BUTTON1 2
#define PIN_BUTTON2 3
#define PIN_BUTTON3 4
#define PIN_BUZZER  12

//lcd connections
#define PIN_LCD_RS  5
#define PIN_LCD_RW  6
#define PIN_LCD_EN  7
#define PIN_LCD_D4  8
#define PIN_LCD_D5  9
#define PIN_LCD_D6  10
#define PIN_LCD_D7  11

#define BTN_PAD_VALUE_INC_TIME  4
#define BTN_PAD_VALUE_DEC_TIME  2
#define BTN_PAD_VALUE_ABRT      6
#define BTN_PAD_VALUE_SP        1

typedef enum{
    NOT_PRESSED,
    BOUNCE,
    PRESSED
}button_state_t;


/* Signals of the application*/
typedef enum{
    INC_TIME,
    DEC_TIME,
    TIME_TICK,
    START_PAUSE,
    ABRT,
/* Internal activity signals */
    ENTRY,
    EXIT,
    MAX_SIGNALS
}protimer_signal_t;

/* Various States of the application*/
typedef enum{
    IDLE,
    TIME_SET,
    COUNTDOWN,
    PAUSE,
    STAT,
    MAX_STATES
}protimer_state_t;

/* Main application structure */
typedef struct {
    uint32_t curr_time;
    uint32_t elapsed_time;
    uint32_t pro_time;
    protimer_state_t active_state;
    uintptr_t *state_table;
}protimer_t;

/*Generic(Super) event structure */
typedef struct{
    uint8_t sig;
}event_t;

/* For user generated events */
typedef struct{
    event_t super;
}protimer_user_event_t;

/* For tick event */
typedef struct{
    event_t super;
    uint8_t ss;
}protimer_tick_event_t;

typedef enum{
    EVENT_HANDLED,
    EVENT_IGNORED,
    EVENT_TRANSITION
}event_status_t;


//function pointer type for event handlers
typedef event_status_t  (*e_handler_t)(protimer_t *const mobj, event_t const *const e);


void protimer_init(protimer_t *mobj);
event_status_t protimer_state_machine(protimer_t *const mobj, event_t const *const e);


//prototypes of event handlers 
event_status_t IDLE_Inc_time(protimer_t *const mobj, event_t const *const e);
event_status_t IDLE_Time_tick(protimer_t *const mobj, event_t const *const e);
event_status_t IDLE_Start_pause(protimer_t *const mobj, event_t const *const e);
event_status_t IDLE_Entry(protimer_t *const mobj, event_t const *const e);
event_status_t IDLE_Exit(protimer_t *const mobj, event_t const *const e);

event_status_t	COUNTDOWN_Start_pause(protimer_t *const mobj, event_t const *const e);
event_status_t	COUNTDOWN_abrt(protimer_t *const mobj, event_t const *const e);
event_status_t  COUNTDOWN_Exit(protimer_t *const mobj, event_t const *const e);
event_status_t  COUNTDOWN_Time_tick(protimer_t *const mobj, event_t const *const e);

event_status_t PAUSE_Inc_time(protimer_t *const mobj, event_t const *const e);
event_status_t PAUSE_Dec_time(protimer_t *const mobj, event_t const *const e);
event_status_t PAUSE_Start_pause(protimer_t *const mobj, event_t const *const e);
event_status_t PAUSE_abrt(protimer_t *const mobj, event_t const *const e);
event_status_t PAUSE_Entry(protimer_t *const mobj, event_t const *const e);
event_status_t PAUSE_Exit(protimer_t *const mobj, event_t const *const e);


event_status_t TIME_SET_Inc_time(protimer_t *const mobj, event_t const *const e);
event_status_t TIME_SET_Dec_time(protimer_t *const mobj, event_t const *const e);
event_status_t TIME_SET_Start_pause(protimer_t *const mobj, event_t const *const e);
event_status_t TIME_SET_abrt(protimer_t *const mobj, event_t const *const e);
event_status_t TIME_SET_Entry(protimer_t *const mobj, event_t const *const e);
event_status_t TIME_SET_Exit(protimer_t *const mobj, event_t const *const e);

event_status_t STAT_Time_tick(protimer_t *const mobj, event_t const *const e);
event_status_t STAT_Time_tick(protimer_t *const mobj, event_t const *const e);
event_status_t STAT_Entry(protimer_t *const mobj, event_t const *const e);
event_status_t STAT_Exit(protimer_t *const mobj, event_t const *const e);

#endif