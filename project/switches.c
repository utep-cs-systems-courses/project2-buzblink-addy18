#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "State_Machine.h"

char switch_state_down, switch_state_changed, current_state; //effectively boolean

static char switch_update_interrupt_sense(){
  char p2val = P2IN;
  //update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES); // if switch up, sense down
  P2IES &= (p2val | ~SWITCHES); // if switch down, sense up
  return p2val;
}

void switch_init(){ //set up switch
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  
  switch_update_interrupt_sense();
  switch_interrupt_handler();

}

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();
  if((p2val & SW1) ? 0 : 1){
    current_state = 1;
  }else if((p2val & SW2) ? 0 : 1){
    current_state = 2;
  }else if((p2val & SW3) ? 0 : 1){
    current_state = 3;
  }else if((p2val & SW4) ? 0 : 1){
    current_state = 4;
  }
  state_advance();
}
  
