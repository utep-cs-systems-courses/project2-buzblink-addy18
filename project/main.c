#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "libTimer.h"

int main(void){
  conClocks();
  led_init();
  wdInterrupts();
  switch_init();
  buzzer_init();

  or_sr(0x18);
}
