#include <msp430.h>
#include "State_Machine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
//#include "assembly.h"

//menu options
static enum(START, MENU_0, MENU_1, MENU_2, MENU_3, assembly_help} current_state = START;
// determine the speed for each state 
char tempo; 

void state_advance(){
  // begin with both llights on 
  switch(current_state){
  case START:
    red_on =1;
    green_on = 1;
    led_update();
    // have user choose between the four buttons 
    if(switch1_state_down){
      current_state = MENU_0;
    }else if(switch2_state_down){
      current_state = MENU_1;
    }else if(switch3_state_down){
      current_state = MENU_2;
    }else if(switch4_state_down){
      current_state = MENU_3;
    }
    break;
    // flashing red light really quickly to make it dim 
  case MENU_0:
    tempo = 1;
    red_on = 1, green_on = 0;
    led_update();
    red_on = 0; green_on = 0;
    led_update();
    current_state = MENU_0;
    if(side_switch){
      current_state = START;
    }
    break;
    // will flash red and green back and fourth 
  case MENU_1:
    tempo = 75;
    red_on = 1, green_on = 0;
    // assembly is being used 
    switching_leds_assembly(); 
    led_update();
    current_state = assembly_help;
    if(switch_state_down){
      current_state = START;
    }
    break;
    //play sound 
  case MENU_2:
    tempo = 50;
    //song_one(); //found in buzzer.c
    if(switch_state_down){
      current_state = START;
      buzzer_set_period(-1);
      reset_counters();
    }
    break;
    //help assembly code flash LEDs
  case assembly_help:
   tempo = 75;
   switching_leds_assembly();
   led_update();
   current_state = assembly_help;
   if(switch_state_down){
     current_state = START;
   }
   break;
   //play song and LED will flash with it 
  case MENU_3:
   tempo = 125;
   // found in buzzer.c
   //song_two(); 
   if(switch_state_down){
     current_state = START;
     buzzer_set_period(-1);
     reset_counters();
    }
  }
}
    
