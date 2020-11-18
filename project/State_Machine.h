#ifndef stateMachine_included
#define stateMachine_included

//extern char tempo;
void state_advance();

void reset_state();
void led_state(unsigned char g, unsigned char r);
void delay(unsigned int t);
void dim();

#endif
