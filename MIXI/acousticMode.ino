boolean isAcousticLEDS = false; //Controls colors of LEDs in this mode

//Array for saving the value of each button in the current mode
boolean acousticButtonPushes[] = {false, false, false, false, false, false};
int acousticPotVals[] = {0, 0, 0, 0}; //Array for tracking the value of each potentiometer in the current mode

int acousticButtonOffset = 20; //Offset for command ID when a button is pressed
int acousticPotOffset = acousticButtonOffset + 8; //Offset for command ID when a potentiometer is turned

int acousticPotsTolerance = 10; //Tolerance for sending potentimeter values

void acousticMode(){ //Yellow LEDS
  //Sets each button LED to the apporpriate color for the current mode
  if(!isAcousticLEDS){
    strip.setBrightness(255);
    for(int i = 0; i < 8; i++){
      if(i != 0 && i != 4){ strip.setPixelColor(i, 255, 255, 0);}   //Yellow
      else if (i == 0){ strip.setPixelColor(i, 0, 255, 255);}       //Cyan
      else if (i == 4){ strip.setPixelColor(i, 255, 255, 255);}     //White
    }
    strip.show();
    isAcousticLEDS = true; //Set to true so LEDs are not contantly set
    Serial.println("Acoustics Ready");
  }

  updateButtons();
  updatePots();

  //Loops through each button
  for (int i = 0; i < 8; i++) {
    int thisButton = buttonStates[i]; //creats a variable and sets value equal to current button state

    if (thisButton == 1 && i != 0 && i != 4) {
      acousticButtonPushes[i] = !acousticButtonPushes[i]; //sets value in saved stated array to the opposite of its previous value 
      
      int commandNum = i + acousticButtonOffset;  //creates a command ID based on current button + an offset value to send

      //Sends a MIDI control change command based on value of the buttons saved state
      if (acousticButtonPushes[i]) {usbMIDI.sendControlChange(commandNum, 127, 1); Serial.println("Sent Command: " + String(commandNum) + " with val 127");}
      else { usbMIDI.sendControlChange(commandNum, 0, 1); Serial.println("Sent Command: " + String(commandNum) + " with val 0");}
    } 
    //Reserves these buttons for switching modes & Disables LEDS for current mode
    else if(thisButton == 1 && i == 0){ mode = 1; isAcousticLEDS = false;} 
    else if (thisButton == 1 && i == 4){ mode = 3; isAcousticLEDS = false;} 
  }

  //Loops through each potentiometer
  for(int i = 0; i < 4; i++){
    int thisPot = potStates[i];  //creates variable and sets value equal to current value of potentiometer 
    
    int commandNum = i + acousticPotOffset; //creates a command ID based on current potentimeter + an offset value to send
    
    //Checks the total difference of potentiometer value change before sending a signal
    //Value change must be larger than tolerance value
    //Sends a MIDI control change command based on value of the potentiometer
    if(abs(thisPot - acousticPotVals[i]) > acousticPotsTolerance){
      usbMIDI.sendControlChange(i + acousticPotOffset, thisPot, 1);
      Serial.println("Sent Command: " + String(commandNum) + " with val " + String(thisPot));
      
      acousticPotVals[i] = thisPot; //Sets saved value to new potentiometer value
    }
  }
}
