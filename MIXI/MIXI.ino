/*
  "MIXI"
  MIDI Mixer
  Cameron Acton
*/

#include <Bounce2.h>
int buttonPins[] = {5, 6, 7, 8, 9, 10, 11, 12}; //Pin Assignment for all buttons
int buttonStates[] = {0, 0, 0, 0, 0, 0, 0, 0};  //State of buttons
Bounce * buttons = new Bounce[8];

int potPins[] = {A0, A1, A2, A3}; //Pin Assignment for all Potentiometers
int potStates[] = {0, 0, 0, 0};   //Value of potentiometers

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(8, 4, NEO_RGB + NEO_KHZ800); //Declare NeoPixel "strip" for all NeoPixels in buttons

int mode = 0; //Current mode of buttons 

void setup() {
  Serial.begin(9600); //Open Serial Communication

  initLEDs();
  initButtons();

  delay(1000);
  Serial.println("Starting Up...");
}

void loop() {
  switch (mode) {
    case 0: startUp();  break;
    case 1: drumMode(); break;
    case 2: acousticMode(); break;
    case 3: synthMode(); break;
  }
}
