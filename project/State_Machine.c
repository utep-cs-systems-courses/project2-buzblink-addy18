#include <msp430.h>
#include "State_Machine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h" 

void state_advance(){
  switch(current_state){
  case 0:
    song2();
    break;

  case 1: //blink green light
    song1();
    for(int i = 0; i < 10; i++){
      P1OUT = LED_RED;
      __delay_cycles(900000);

      P1OUT = !LED_RED;
      __delay_cycles(900000);
     }
    current_state  = 0;
    break;

  case 2: //blink red light
    song4();
    for(int i = 0; i < 10; i++){
      P1OUT = LED_GREEN;
      __delay_cycles(900000);

      P1OUT = !LED_GREEN;
      __delay_cycles(900000);
    }
    current_state = 0;
    break;

  case 3: //both lights on
    song2();
    for(int i = 0; i < 10; i++){
      P1OUT = LED_GREEN;
      __delay_cycles(850000);

      P1OUT = LED_RED;
      __delay_cycles(850000);

      P1OUT = !LED_GREEN;
      __delay_cycles(850000);

      P1OUT = !LED_RED;
      __delay_cycles(850000);
    }
    current_state = 0;
    break;

  case 4:
    song3();
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
 }
    
