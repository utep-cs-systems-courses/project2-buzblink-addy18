#include <msp430.h>
#include "switches.h"
#include "led.h"

char switch_state_down, switch_state_changed, switch1, switch2, switch3, switch4; //effectively boolean

static char switch_update_interrupt_sense(){
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

  switch_interrupt_handler();

}

void switch_interrupt_handler(){
  char p1val = switch_update_interrupt_sense();
  switch1 = (p1val & SW1) ? 0 : 1;
  swicth2 = (p1val & SW2) ? 0 : 1;
  swicth3 = (p1val & SW3) ? 0 : 1;
  swicth4 = (p1val & SW4) ? 0 : 1;

  switch_state_changed =1;
}
  
