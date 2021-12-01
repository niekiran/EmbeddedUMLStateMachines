

#include "main.h"
#include "lcd.h"

static void protimer_event_dispatcher(protimer_t *const mobj,event_t const *const e);
static uint8_t process_button_pad_value(uint8_t btn_pad_value);
static void display_init(void);
static void protimer_state_table_init(protimer_t *const mobj);

/*Main application object */
static protimer_t protimer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  display_init();
  Serial.println("Productive timer application");
  Serial.println("===========================");
  pinMode(PIN_BUTTON1,INPUT);
  pinMode(PIN_BUTTON2,INPUT);
  pinMode(PIN_BUTTON3,INPUT);

  protimer_state_table_init(&protimer);
  protimer_init(&protimer);
}

void loop() {

  uint8_t b1,b2,b3,btn_pad_value;
  protimer_user_event_t ue;
  static uint32_t current_time = millis();
  static protimer_tick_event_t te;

  //1. read the button pad status
  b1 = digitalRead(PIN_BUTTON1); 
  b2 = digitalRead(PIN_BUTTON2);
  b3 = digitalRead(PIN_BUTTON3);

  btn_pad_value = (b1<<2)|(b2<<1)|b3;

  //software button de-bouncing 
  btn_pad_value = process_button_pad_value(btn_pad_value);

  //2. make an event 
  if(btn_pad_value){
    if(btn_pad_value == BTN_PAD_VALUE_INC_TIME){
      ue.super.sig = INC_TIME;
    }else if(btn_pad_value == BTN_PAD_VALUE_DEC_TIME){
      ue.super.sig = DEC_TIME;
    }else if(btn_pad_value == BTN_PAD_VALUE_SP){
      ue.super.sig = START_PAUSE;
    }else if(btn_pad_value == BTN_PAD_VALUE_ABRT){
      ue.super.sig = ABRT;
    }
     //3. send it to event dispatcher
    protimer_event_dispatcher(&protimer,&ue.super);
  }

  //4. dispatch the time tick event for every 100ms
  if(millis() - current_time  >= 100){
    //100ms has passed
    current_time = millis();
    te.super.sig = TIME_TICK;
    if(++te.ss > 10) te.ss = 1;
    protimer_event_dispatcher(&protimer,&te.super);
  }

}


static void protimer_event_dispatcher(protimer_t *const mobj,event_t const *const e){
  
  event_status_t status;
  protimer_state_t source, target;
  e_handler_t ehandler;
  
  source = mobj->active_state;
  ehandler = (e_handler_t) mobj->state_table[mobj->active_state * MAX_SIGNALS + e->sig];
  if(ehandler)
    status = (*ehandler)(mobj,e);

  if(status == EVENT_TRANSITION){
    target = mobj->active_state;
    event_t ee;
    //1. run the exit action for the source state
    ee.sig = EXIT;
    ehandler =(e_handler_t) mobj->state_table[source*MAX_SIGNALS + EXIT];
    if(ehandler)
      (*ehandler)(mobj,&ee);

    //2. run the entry action for the target state
    ee.sig = ENTRY;
    ehandler =(e_handler_t) mobj->state_table[target * MAX_SIGNALS + ENTRY];
    if(ehandler)
      (*ehandler)(mobj,&ee);
  }

} 


static void protimer_state_table_init(protimer_t *const mobj)
{
  static e_handler_t protimer_state_table[MAX_STATES][MAX_SIGNALS] = {
    [IDLE]	  	  = {&IDLE_Inc_time,NULL,&IDLE_Time_tick,&IDLE_Start_pause,NULL,&IDLE_Entry,&IDLE_Exit},
    [TIME_SET] 	  = {&TIME_SET_Inc_time,&TIME_SET_Dec_time,NULL,&TIME_SET_Start_pause,&TIME_SET_abrt,&TIME_SET_Entry,&TIME_SET_Exit},
    [COUNTDOWN] 	= {NULL,NULL,&COUNTDOWN_Time_tick,&COUNTDOWN_Start_pause,&COUNTDOWN_abrt,NULL,COUNTDOWN_Exit},
    [PAUSE] 		  = {&PAUSE_Inc_time,&PAUSE_Dec_time,NULL,&PAUSE_Start_pause,&PAUSE_abrt,&PAUSE_Entry,&PAUSE_Exit},
    [STAT] 		    = {NULL,NULL,&STAT_Time_tick,NULL,NULL,&STAT_Entry,STAT_Exit}
};

   mobj->state_table = (uintptr_t*) &protimer_state_table[0][0];

}


static uint8_t process_button_pad_value(uint8_t btn_pad_value)
{
  static button_state_t btn_sm_state = NOT_PRESSED;
  static uint32_t curr_time = millis();

  switch(btn_sm_state){
    case NOT_PRESSED:{
      if(btn_pad_value){
        btn_sm_state = BOUNCE;
        curr_time = millis();
      }
      break;
    }
    case BOUNCE:{
      if(millis() - curr_time >= 50 ){
        //50ms has passed 
        if(btn_pad_value){
          btn_sm_state = PRESSED;
          return btn_pad_value;
        }
        else
          btn_sm_state = NOT_PRESSED;
      }
      break;
    }
    case PRESSED:{
      if(!btn_pad_value){
        btn_sm_state = BOUNCE;
        curr_time = millis();
      }
      break;
    }

  }

  return 0;
}

static void display_init(void)
{
  lcd_begin(16,2);
  lcd_clear();
  lcd_move_cursor_L_to_R();
  lcd_set_cursor(0,0);
  lcd_no_auto_scroll();
  lcd_cursor_off();
}