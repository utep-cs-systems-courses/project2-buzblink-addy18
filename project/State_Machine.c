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
  }
}
    
