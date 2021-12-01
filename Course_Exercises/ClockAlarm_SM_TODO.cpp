#define GET_HOUR(seconds)     (seconds/3600UL)
#define GET_MIN(seconds)      ((seconds/60UL)%60UL)
#define GET_SEC(seconds)      (seconds % 60UL)
#define DIGIT1(d)       	  (d/10U)
#define DIGIT2(d)       	  (d%10U)

/*
 * Description : Displays current time depending upon the time mode
 * param1: 'me' pointer
 * param2 : row number of the LCD
 * param3: column number of the LCD
 */
void display_curr_time(Clock_Alarm *me,uint8_t row, uint8_t col){
    String time_as_string;
    uint32_t time_;

    uint32_t time24h = Clock_Alarm_get_curr_time()/10; //convert to number of seconds 
    uint8_t ss = time24h % 10U;       //extract sub-second to append later

    time_ = (me->time_mode == MODE_24H)?time24h:convert_24hformat_to_12h(time24h);
    time_as_string = integertime_to_string(time_); //hh:mm:ss
    time_as_string.concat('.');
    time_as_string.concat(ss);

    /*if mode is 12H , concatenate  am/pm information */
    if(me->time_mode == MODE_12H){
        time_as_string.concat(' ');
        time_as_string.concat(get_am_or_pm(time24h));
    }

    display_write(time_as_string,row,col);
}


/*
 * Description : Decodes AM/PM information from given time in 24H format
 * param1: Integer time in 24H format
 * return : A string value("AM" or "PM")
 */
String get_am_or_pm(uint32_t time24h){
    String ampm;
    uint8_t h = GET_HOUR(time24h);
    if(h == 0U){
        ampm = "AM";
    }else if( h > 12U){
        ampm = "PM";
    }else if (h == 12U)
        ampm = "PM";
    else
        ampm = "AM";
    return ampm;
}

/*
 * Description: Writes a message to the LCD at given row and column number
 * param1 : Message to write in 'String' format
 * param2 : row number of the LCD
 * param2 : column number of the LCD
 */
void  display_write(String str_, uint8_t r, uint8_t c){
    lcd_set_cursor(c,r);
    lcd_print_string(str_);
}

/*
 * Description: converts an 'integer' time to 'String' time
 * param1 : time represented in terms of number of seconds
 * return : time as 'String' value in the format HH:MM:SS
 */
String integertime_to_string(uint32_t time_){
    uint8_t h,m,s;
    char buf[10]; //00:00:00+null
    h = GET_HOUR(time_); /* Extract how many hours the 'time_' represent */
    m = GET_MIN(time_);  /* Extract how many minutes the 'time_' represent */
    s = GET_SEC(time_);	 /* Extract how many seconds the 'time_' represent */
    sprintf(buf,"%02d:%02d:%02d",h,m,s);
    return (String)buf;
}

/*
 * Description: Converts given integer time in 12H format to integer time 24H format
 * param1 : Integer time in 12H format
 * param2 : time format of type time_format_t
 * return : Integer time in 24H format
 */
uint32_t convert_12hformat_to_24h(uint32_t time12h, time_format_t ampm){
    uint8_t hour;
    uint32_t time24h;
    hour = GET_HOUR(time12h);
    if(ampm == FORMAT_AM){
        time24h = (hour == 12)? (time12h-(12UL * 3600UL)) : time12h;
    }else{
        time24h = (hour == 12)? time12h : (time12h +(12UL * 3600UL));
    }
    return time24h;
}

/*
 * Description: Converts given integer time in 24H format to integer time 12H format
 * param1 : Integer time in 24H format
 * return : Integer time in 12H format
 */
uint32_t convert_24hformat_to_12h(uint32_t time24h){
    uint8_t hour;
    uint32_t time12h;
    hour = GET_HOUR(time24h);

    if(hour == 0)
        time12h = time24h + (12UL * 3600UL);
    else{
        if((hour < 12UL) || (hour == 12UL))
            return time24h;
        else
            time12h = time24h - (12UL * 3600UL);
    }
    return time12h;
}


/*
 * Description : Displays current time depending upon the time mode
 * param1: 'me' pointer
 * param2 : row number of the LCD
 * param3: column number of the LCD
 */
void display_clock_setting_time(Clock_Alarm *me,uint8_t row, uint8_t col){
	String time_as_string;

	time_as_string = integertime_to_string(me->temp_time); //hh:mm:ss

	/*concatenate  am/pm information */
	if(me->temp_format != FORMAT_24H){
		time_as_string.concat(' ');
		if(me->temp_format == FORMAT_AM)
			time_as_string.concat("AM");
		else
			time_as_string.concat("PM");
	}

	display_write(time_as_string,row,col);
}



 /*.${HSMs::Clock_Alarm::SM::Clock::Ticking::SET} */
me->temp_time = Clock_Alarm_get_curr_time()/10;
if(me->time_mode == MODE_12H){
	if(get_am_or_pm(me->temp_time).equals("AM")){
		me->temp_format = FORMAT_AM;
	}
	else{
		me->temp_format = FORMAT_PM;
	}
	me->temp_time = convert_24hformat_to_12h(me->temp_time);
}
else
	me->temp_format = FORMAT_24H;
       

/* ${HSMs::Clock_Alarm::SM::Clock::Settings::Clock_Setting} */
Clock_Alarm_display_clock_setting_time(me,0,2);
display_cursor_on_blinkon();

/* ${HSMs::Clock_Alarm::SM::Clock::Settings::Clock_Setting::cs_hour_d1} */
display_set_cursor(CS_ROW,CS_HOUR_D1_COL);
me->temp_digit = DIGIT1(GET_HOUR(me->temp_time));

/*${HSMs::Clock_Alarm::SM::Clock::Settings::Clock_Setting::cs_hour_d1::SET} */
++me->temp_digit;
me->temp_digit %= 3;
me->temp_time -=  DIGIT1(GET_HOUR(me->temp_time)) * 10UL * 3600UL;
me->temp_time += (me->temp_digit * 10UL ) * 3600UL;
Clock_Alarm_display_clock_setting_time(me,0,2);
display_set_cursor(CS_ROW,CS_HOUR_D1_COL);


void display_cursor_on_blinkon(){
    lcd_cursor_show();
    lcd_cursor_blink();
}

void display_cursor_off_blinkoff(){
    lcd_cursor_off();
    lcd_cursor_blinkoff();
}


void display_set_cursor(uint8_t r, uint8_t c){
     lcd_set_cursor(c,r);
}

bool is_time_set_error(uint32_t time_,time_format_t format){
    uint8_t h = GET_HOUR(time_);
    return ((h > 23) || ((h > 12 || (h == 0))&& format != FORMAT_24H) );
}

${HSMs::Clock_Alarm::SM::Clock::Settings::Clock_Setting::cs_format}
display_set_cursor(CLOCK_SETTING_TIME_ROW,CLOCK_SETTING_TIME_FMT_COL);
String msg[3] = {"24H","AM ","PM "};
display_write(msg[me->temp_format],CLOCK_SETTING_TIME_ROW,CLOCK_SETTING_TIME_FMT_COL);
display_set_cursor(CLOCK_SETTING_TIME_ROW,CLOCK_SETTING_TIME_FMT_COL);

${HSMs::Clock_Alarm::SM::Clock::Settings::Clock_Setting::cs_format::SET}
String msg;
if(me->temp_format == FORMAT_24H){
    me->temp_format = FORMAT_AM;
    msg = "AM ";
}
else if(me->temp_format == FORMAT_AM){
    me->temp_format = FORMAT_PM;
    msg = "PM ";
}
else if (me->temp_format == FORMAT_PM){
    me->temp_format = FORMAT_24H;
    msg = "24H";
}
display_write(msg,CLOCK_SETTING_TIME_ROW,CLOCK_SETTING_TIME_FMT_COL);
display_set_cursor(CLOCK_SETTING_TIME_ROW,CLOCK_SETTING_TIME_FMT_COL);


void display_erase_block(uint8_t row,uint8_t col_start,uint8_t col_stop)
{
    uint8_t len = col_stop - col_start;
    do{
        lcd_set_cursor(col_start++,row);
        lcd_print_char(' ');
    }while(len--);
}

/* ${HSMs::Clock_Alarm::SM::Clock::Settings::OK} */
	uint8_t save_sreg;
	
	if(me->temp_format != FORMAT_24H){
		me->temp_time = convert_12hformat_to_24h( me->temp_time,(time_format_t)me->temp_format);
		me->time_mode = MODE_12H;
	}else{
		me->time_mode = MODE_24H;
	}

	me->temp_time *= 10UL;
	save_sreg = SREG;
	cli();
	TCCR1B &= ~(0x7U); //Stop the TIMER1
	TCNT1 = 0U;    
	Clock_Alarm_curr_time = me->temp_time;
	TCCR1B |= 0x4U;
	SREG = save_sreg;