#include <msp430.h>
#include "switches.h"

//switches on P1
void __interrupt_vec(PORT1_VECTOR) Port_1(){
  if(P1IFG & SWITCHES){
    P1IFG = ~SWITCHES;
    switch_interrupt_handler();
  }
}

//switch on P2
void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
