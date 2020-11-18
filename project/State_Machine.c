#include <msp430.h>
#include "State_Machine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h" 

char toggle_red(){
  static char state = 0;
  reset_state();
  switch(state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;
}

char toggle_green(){
  char changed = 0;
  if(red_on){
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void state_advance(){
  switch(switch_state_changed){
  case 1:
    toggle_red();
    break;
  case 2:
    toggle_green();
    break;
  case 3:
    //toggle_red();
    //toggle_green();
    //both();
    for(int i = 0; i < 1; i++){
      P1OUT = LED_GREEN;
      __delay_cycles(850000);
      P1OUT = LED_RED;
      __delay_cycles(850000);
      P1OUT = !LED_GREEN;
      __delay_cycles(850000);
      P1OUT = !LED_RED;
      __delay_cycles(850000);
    }
    break;
  case 4:
    /* toggle_red();
     toggle_green();
    */
    //dim();
    for(int i = 0; i < 100; i++){
      P1OUT = LED_RED;
      P1OUT = LED_GREEN;

      P1OUT = !LED_RED;
      P1OUT = !LED_GREEN;
    }
    break;

  default:
    break;
  }
  
  /*  switch(current_state){
  case 1: //blink green light
    song1();
    /*    for(int i = 0; i < 10; i++){
      P1OUT = LED_RED;
      __delay_cycles(900000);

      P1OUT = !LED_RED;
      __delay_cycles(900000);
     }
    
    toggle_red();
    current_state  = 0;
    break;

  case 2: //blink red light
    song4();
    /* for(int i = 0; i < 10; i++){
      P1OUT = LED_GREEN;
      __delay_cycles(900000);

      P1OUT = !LED_GREEN;
      __delay_cycles(900000);
    }
    
    current_state = 0;
    break;
  */
 }

void both(){
  char changed = 0;
  static enum {R=0, G=1} color = G;
  switch(color){
  case R:
    changed = toggle_red();
    color = G;
    break;
  case G:
    changed = toggle_green();
    color = R;
    break;
  }
  led_changed = changed;
  led_update();
}

void led_state(unsigned char g, unsigned char r){
  green_on = g;
  red_on = r;
  led_changed = 1;
  led_update();
}

void reset_state(){
  red_on = 0;
  green_on = 0;
  led_update();
}

void delay(unsigned int t){
  unsigned int i;
  for(i = t; i > 0; i--){
    __delay_cycles(1);
  }
}

void dim(){
  while(dim_on){
    unsigned int i;
    for(i = 1; i < 1200; i++){
      led_state(1,0);
      delay(i);
      led_state(0,1);
      delay(1200-i);
    }
    for(i = 1200;i > 1; i--){
      led_state(1,0);
      delay(i);
      led_state(0,1);
      delay(1200-i);
    }
  }
}
