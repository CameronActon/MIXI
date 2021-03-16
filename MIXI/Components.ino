//Initializes LEDs in buttons
void initLEDs(){
  strip.begin();
  strip.clear();
  strip.show();
}

//Initializes Buttons on board
void initButtons(){
  for (int i = 0; i < 8; i++){
    buttons[i].attach(buttonPins[i] , INPUT_PULLUP);
    buttons[i].interval(25);  
  }
}

//Loops through each button and updates the states array with the current state of the button
void updateButtons(){
  for (int i = 0; i < 8; i++){
    buttons[i].update();
    if(buttons[i].rose()){buttonStates[i] = 1;}
    else{buttonStates[i] = 0;}
  }
}

//Loops through each potentiometer and updates the states array with the current value of the potentiometers
void updatePots(){
  for (int i = 0; i < 4; i++){
    int thisPot = analogRead(potPins[i]);
    int mapPot = map(thisPot, 0, 1023, 0, 127);
    potStates[i] = mapPot;
  }
}
