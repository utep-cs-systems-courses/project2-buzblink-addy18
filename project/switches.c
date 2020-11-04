#include <msp430.h>
#include "switches.h"
#include "led.h"

char switch_state_down, switch_state_changed, switch1, switch2, switch3, switch4; //effectively boolean

static char switch_Update_interrupt_sense(){
  char p1val = P1IN;
  //update switch interrupt to detect changes from current buttons
  P1IES |= (p1val & SWITCHES); // if switch up, sense down
  P1IES &= (p1val | ~SWITCHES); // if switch down, sense up
  return p1val;
}

void switch_init(){ //set up switch
  P1REN |= SWITCHES;
  P1IE |= SWITCHES;
  P1OUT |= SWITCHES;
  P1DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();

}

void switch_interrupt_handler(){
  char p1val = switch_update_interrupt_sense();
  switch_state_down = (p1val & SW1) ? 0 : 1; //0 when SW1 is up
  switch_state_changed = 1;
  led_update();
}
  
