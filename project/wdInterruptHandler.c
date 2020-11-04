#include <msp430.h>
#include "State_Machine.h"

void __interrupt_vecc(WDT_VECTOR) WDT(){ //250 interrupts/sec
  static char blink_count = 0;
  if(++blink_count == 125){
    state_advance();
    blink_count = 0;
  }
}
