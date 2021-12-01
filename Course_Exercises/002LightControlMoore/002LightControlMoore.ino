
enum event{
  ON,
  OFF,
};

typedef enum {
  LIGHT_OFF,
  LIGHT_DIM,
  LIGHT_MEDIUM,
  LIGHT_FULL
}light_state_t;

light_state_t curr_state;


#define PIN_LED 9

#define LIGHT_BRIGHT_DIM   25
#define LIGHT_BRIGHT_MED   85
#define LIGHT_BRIGHT_FULL  255
#define LIGHT_BRIGHT_OFF   0

void light_state_machine(uint8_t event);
void light_change_intensity(uint8_t pin, uint8_t intensity);
void run_entry_action(light_state_t state);

void light_init(void)
{
  curr_state = LIGHT_OFF;
  run_entry_action(LIGHT_OFF);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Light control application");
  Serial.println("-------------------------");
  Serial.println("Send 'x' or 'o'");

  light_init();
}

void loop() {
  uint8_t event;
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    event = Serial.read();
    if(event == 'o'){
      light_state_machine(ON);
    }else if(event == 'x'){
      light_state_machine(OFF);
    }
  }

}

void light_state_machine(uint8_t event)
{
  light_state_t prev_state;

  prev_state = curr_state;
  switch(curr_state)
  {
    case LIGHT_OFF:{
      switch(event){
        case ON:{
          curr_state = LIGHT_DIM;
          break;
        }
      }
      break;
    }
    case LIGHT_DIM:{
      switch(event){
        case ON:{
          curr_state = LIGHT_MEDIUM;
          break;
        }
        case OFF:{
          curr_state = LIGHT_OFF;
          break;
        }
      }
      break;
    }
    case LIGHT_MEDIUM:{
      switch(event){
        case ON:{
          curr_state = LIGHT_FULL;
          break;
        }
        case OFF:{
          curr_state = LIGHT_OFF;         
          break;
        }
      }
      break;
    }
    case LIGHT_FULL:{
      switch(event){
        case ON:{
          curr_state = LIGHT_DIM;         
          break;
        }
        case OFF:{
          curr_state = LIGHT_OFF;          
          break;
        }
      }
      break;
    }
  }

  if(prev_state != curr_state)
    run_entry_action(curr_state);
}

void run_entry_action(light_state_t state)
{
  switch(state)
  {
    case LIGHT_OFF:{
      light_change_intensity(PIN_LED,LIGHT_BRIGHT_OFF);
      break; 
    }
    case LIGHT_DIM:{
      light_change_intensity(PIN_LED,LIGHT_BRIGHT_DIM);
      break; 
    }
    case LIGHT_MEDIUM:{
      light_change_intensity(PIN_LED,LIGHT_BRIGHT_MED);
      break; 
    }
    case LIGHT_FULL:{
      light_change_intensity(PIN_LED,LIGHT_BRIGHT_FULL);
      break; 
    }
  }
}

void light_change_intensity(uint8_t pin, uint8_t intensity)
{
  analogWrite(pin,intensity);
}
