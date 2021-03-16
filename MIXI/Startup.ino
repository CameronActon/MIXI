//Plays simple startup animation while board is Mixi is prepared to be used
void startUp(){
  fadeUp(1);    //White
  delay(100);
  fadeDown(1);  //White
  delay(100);
  fadeUp(2);    //Yellow
  delay(100);
  fadeDown(2);  //Yellow
  delay(100);
  fadeUp(0);    //Cyan
  delay(100);
  fadeDown(0);  //Cyan
  delay(200);
  popIn();
  
  delay(1000);
  mode = 1; //immediately sends program into first state (drumState) as animation is completed
}

//Gradually increases brightness of strip, takes in value which determines color of LEDs fading in
void fadeUp(int c){
  for (int j = 0; j < 256; j+= 5) {
    for (int i = 0; i <=strip.numPixels(); i++) {
      if(c == 0){strip.setPixelColor(i,j,j,j);}         //White
      else if(c == 1){strip.setPixelColor(i,0,j,j);}    //Cyan
      else if(c == 2){strip.setPixelColor(i,j,j,0);}    //Yellow
    }
    strip.show();
    delay(10);
  }
}

//Gradually decreases brightness of strip, takes in value which determines color of LEDs fading out
void fadeDown(int c) {
  for (int j = 255; j > 0; j-=5) {
    for (int i = 0; i <=strip.numPixels(); i++) {
      if(c == 0){strip.setPixelColor(i,j,j,j);}         //White
      else if(c == 1){strip.setPixelColor(i,0,j,j);}    //Cyan
      else if(c == 2){strip.setPixelColor(i,j,j,0);}    //Yellow
    }
    strip.show();
    delay(10);
  }
}

//Randomly turns on NeoPixels until board is lit with colors of drumState
void popIn(){
  strip.clear();
  strip.show();
  strip.setBrightness(255);

  for(int i = 0; i < 14; i++){
    int r = int(random(9));
  
    if(r == 0){strip.setPixelColor(r, 255, 255, 0);}         //Yellow
    else if( r == 4){strip.setPixelColor(r, 255, 255, 255);} //White
    else{strip.setPixelColor(r, 0, 255, 255);}               //Cyan
    strip.show();
    delay(250);
  }
}
