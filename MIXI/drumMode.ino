boolean isDrumLEDS = false; //Controls colors of LEDs in this mode

//Array for saving the value of each button in the current mode
boolean drumButtonPushes[] = {false, false, false, false, false, false}; 
int drumPotVals[] = {0, 0, 0, 0}; //Array for tracking the value of each potentiometer in the current mode

int drumButtonOffset = 0; //Offset for command ID when a button is pressed
int drumPotOffset = drumButtonOffset + 8; //Offset for command ID when a potentiometer is turned

int drumPotsTolerance = 10; //Sets each button LED to the apporpriate color for the current modeolerance for sending potentimeter values

void drumMode(){ //Cyan LEDS
  //Sets each button LED to the apporpriate color for the current mode
  if(!isDrumLEDS){
    strip.setBrightness(255);
    for(int i = 0; i < 8; i++){
      if(i != 0 && i != 4){ strip.setPixelColor(i, 0, 255, 255);}   //Cyan
      else if (i == 0){ strip.setPixelColor(i, 255, 255, 0);}       //Yellow
      else if (i == 4){ strip.setPixelColor(i, 255, 255, 255);}     //White
    }
    strip.show();
    isDrumLEDS = true; //Set to true so LEDs are not contantly set
    Serial.println("Drums Ready");
  }

  updateButtons();
  updatePots();

  //Loops through each button
  for (int i = 0; i < 8; i++) {
    int thisButton = buttonStates[i]; //creats a variable and sets value equal to current button state

    if (thisButton == 1 && i != 0 && i != 4) {
      drumButtonPushes[i] = !drumButtonPushes[i]; //sets value in saved stated array to the opposite of its previous value
       
      int commandNum = i + drumButtonOffset; //creates a command ID based on current button + an offset value to send
      
      //Sends a MIDI control change command based on value of the buttons saved state
      if (drumButtonPushes[i]) {usbMIDI.sendControlChange(i + drumButtonOffset, 127, 1); Serial.println("Sent Command: " + String(commandNum) + " with val 127");}
      else { usbMIDI.sendControlChange(i + drumButtonOffset, 0, 1); Serial.println("Sent Command: " + String(commandNum) + " with val 0");}
    } 
    //Reserves these buttons for switching modes & Disables LEDS for current mode
    else if(thisButton == 1 && i == 0){ mode = 2; isDrumLEDS = false;}
    else if (thisButton == 1 && i == 4){ mode = 3; isDrumLEDS = false;}
  }

  //Loops through each potentiometer
  for(int i = 0; i < 4; i++){
    int thisPot = potStates[i]; //creates variable and sets value equal to current value of potentiometer 
    
    int commandNum = i + drumPotOffset; //creates a command ID based on current potentimeter + an offset value to send
    
    //Checks the total difference of potentiometer value change before sending a signal
    //Value change must be larger than tolerance value
    //Sends a MIDI control change command based on value of the potentiometer
    if(abs(thisPot - drumPotVals[i]) > drumPotsTolerance){
      usbMIDI.sendControlChange(i + drumPotOffset, thisPot, 1);
      Serial.println("Sent Command: " + String(commandNum) + " with val " + String(thisPot));
      
      drumPotVals[i] = thisPot; //Sets saved value to new potentiometer value
    }
  }
}
