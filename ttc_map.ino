// SETUP

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#define PIN 11 // Define Arduino pin connected to NeoPixels
#define NUMPIXELS 80 // Define total # of pixels

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL1 500
#define DELAYVAL2 225

int rideTheLineButton = 8;
int rideTheLineButtonState = 0;
int partyTimeButton = 9;
int partyTimeButtonState = 0;
int pickStationButton = 10;
int pickStationButtonState = 0;
int mode = 1;
int currentMode = 0;
int i = 0;
int k = 0;
boolean firstPass = true;
boolean firstPass2 = true;
boolean firstPass3 = true;
boolean firstPass4 = true;

void setup() {

  pixels.begin();
  Serial.begin(9600);
  pinMode(rideTheLineButton, INPUT);
  pinMode(partyTimeButton, INPUT);
  pinMode(pickStationButton, INPUT);

}

// MAIN CODE BODY

void loop() {

  int potValue = analogRead(A0);
  int brightness = map(potValue,0,1023,255,0);
  //Serial.println(brightness);
  
  pixels.clear();
  pixels.setBrightness(brightness);
  
  if (i<NUMPIXELS && i != 36 && i != 37 && i != 53 && i != 64 && i != 20 && i != 18) {
    i++;
  } else if (i == 36 || i == 37) {
    i = 39;
  } else if (i == 53) {
    i = 20;
  } else if (i == 64) {
    i = 18;
  } else if (i == 20 && firstPass == true) {
    i = 21;
    firstPass = false;
  } else if (i == 20 && firstPass == false) {
    i = 54;
    firstPass = true;
  } else if (i == 18 && firstPass2 == true) {
    i = 19;
    firstPass2 = false;
  } else if (i == 18 && firstPass2 == false) {
    i = 65;
    firstPass2 = true;
  } else {
    i = 0;
  }

  rideTheLineButtonState = digitalRead(rideTheLineButton);
  partyTimeButtonState = digitalRead(partyTimeButton);
  pickStationButtonState = digitalRead(pickStationButton);

  //Serial.print(mode);

  if (rideTheLineButtonState == HIGH) {
    mode = 1;
  } else if (partyTimeButtonState == HIGH) {
    mode = 2;
  } else if (pickStationButtonState == HIGH) {
    if (k<NUMPIXELS && k != 36 && k != 37 && k != 53 && k != 64 && k != 20 && k != 18) {
    k++;
    } else if (k == 36 || k == 37) {
      k = 39;
    } else if (k == 53) {
      k = 20;
    } else if (k == 64) {
      k = 18;
    } else if (k == 20 && firstPass3 == true) {
      k = 21;
      firstPass3 = false;
    } else if (k == 20 && firstPass3 == false) {
      k = 54;
      firstPass3 = true;
    } else if (k == 18 && firstPass4 == true) {
      k = 19;
      firstPass4 = false;
    } else if (k == 18 && firstPass4 == false) {
      k = 65;
      firstPass4 = true;
    } else {
      k = 0;
    } 
    mode = 3;
  }
  
  switch(mode) {
    case 1:
      rideTheLine(i); 
      break;
    case 2:
      partyTime(brightness);
      break;
    case 3:
      pickStation(k);
      break;
    }

}


void rideTheLine(int i) {

  pixels.fill(pixels.Color(0, 255, 0), 0, NUMPIXELS-1); // Make entire strip red
  pixels.setPixelColor(i, pixels.Color(255, 0, 0));
  pixels.show();
  delay(DELAYVAL1);
       
}

void partyTime(int brightness) {
  
  int Count = 25;
  int SpeedDelay = 10;
  boolean OnlyOne = false;
  
  setAll(0,50,0,brightness);
 
  for (int i=0; i<Count; i++) {
     setPixel(random(NUMPIXELS),0,255,0,brightness);
     showStrip();
     delay(SpeedDelay);
     if(OnlyOne) {
       setAll(0,0,0,brightness);
     }
   }
 
  delay(SpeedDelay);
  
}

void pickStation(int k) {

  pixels.fill(pixels.Color(0, 255, 0), 0, NUMPIXELS-1); // Make entire strip red
  pixels.setPixelColor(k, pixels.Color(255, 0, 0));
  pixels.show();
  delay(DELAYVAL2);
  
}

// Functions for partyTime

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 /*#ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif*/
}

void setPixel(int Pixel, byte red, byte green, byte blue, int brightness) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setBrightness(brightness);
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 /*#ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif*/
}

void setAll(byte red, byte green, byte blue, int brightness) {
  for(int i = 0; i < NUMPIXELS; i++ ) {
    setPixel(i, red, green, blue, brightness);
  }
  showStrip();
}
