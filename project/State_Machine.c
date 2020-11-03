void state_advance(){
  // begin with both llights on 
  switch(current_state){
  case START:
    red_on =1;
    green_on = 1;
    led_update();
    // have user choose between the four buttons 
    if(switch1){
      current_state = MENU_0;
    }else if(switch2){
      current_state = MENU_1;
    }else if(switch3){
      current_state = MENU_2;
    }else if(switch4){
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
  case MENU_1:
  case MENU_2;
  case MENU_3;
  
  }
}
    
