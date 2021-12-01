
enum event{
  ON,
  OFF
};

typedef enum {
  LIGHT_OFF,
  LIGHT_DIM,
  LIGHT_MEDIUM,
  LIGHT_FULL
}light_state_t;

light_state_t curr_state = LIGHT_OFF;


#define PIN_LED 9

#define LIGHT_BRIGHT_DIM   25
#define LIGHT_BRIGHT_MED   85
#define LIGHT_BRIGHT_FULL  255
#define LIGHT_BRIGHT_OFF   0

void light_state_machine(uint8_t event);
void light_change_intensity(uint8_t pin, uint8_t intensity);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Light control application");
  Serial.println("-------------------------");
  Serial.println("Send 'x' or 'o'");
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
  
  switch(curr_state)
  {
    case LIGHT_OFF:{
      switch(event){
        case ON:{
          light_change_intensity(PIN_LED,LIGHT_BRIGHT_DIM);
          curr_state = LIGHT_DIM;
          break;
        }
      }
      break;
    }
    case LIGHT_DIM:{
      switch(event){
        case ON:{
          light_change_intensity(PIN_LED,LIGHT_BRIGHT_MED);
          curr_state = LIGHT_MEDIUM;
          break;
        }
        case OFF:{
          light_change_intensity(PIN_LED,LIGHT_BRIGHT_OFF);
          curr_state = LIGHT_OFF;
          break;
        }
      }
      break;
    }
    case LIGHT_MEDIUM:{
      switch(event){
        case ON:{
          light_change_intensity(PIN_LED,LIGHT_BRIGHT_FULL);
          curr_state = LIGHT_FULL;
          break;
        }
        case OFF:{
          light_change_intensity(PIN_LED,LIGHT_BRIGHT_OFF);
          curr_state = LIGHT_OFF;         
          break;
        }
      }
      break;
    }
    case LIGHT_FULL:{
      switch(event){
        case ON:{
          light_change_intensity(PIN_LED,LIGHT_BRIGHT_DIM);
          curr_state = LIGHT_DIM;         
          break;
        }
        case OFF:{
          light_change_intensity(PIN_LED,LIGHT_BRIGHT_OFF);
          curr_state = LIGHT_OFF;          
          break;
        }
      }
      break;
    }
  }
}

void light_change_intensity(uint8_t pin, uint8_t intensity)
{
  analogWrite(pin,intensity);
}
