/*  
 
 PHMetro con Arduino.
 Progetto Tecnopolo in una bottiglia.    
 Marzo 2019 - maurizio.conti@fablabromagna.org
 
 Visualizza su una striscia di led, un colore diverso a seconda del PH misurato.

 Colori del PH
 https://it.wikipedia.org/wiki/PH
*/

#include <Adafruit_NeoPixel.h>

#include <Wire.h>
#include "rgb_lcd.h"

#define PIN 6
#define NUMPIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
rgb_lcd lcd;


int sensorValue = 0;        
int ph = 0;

void setup() {
  Serial.begin(9600);
  pixels.begin(); 
  lcd.begin(16, 2);
}

void loop() {
  
  // Legge il sensore del PH 
  sensorValue = analogRead(A0);

  // fa la proporzione
  // ph 4 -> 250
  // ph 8 -> 500
  ph = map(sensorValue, 250, 500, 40, 80);

  // Visualizza il valore
  lcd.print( ph );
  
  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(ph);

  if( ph > 65  && ph < 75 ) {
    pixels.setPixelColor(1, pixels.Color(0,150,0) );
    lcd.setRGB(0, 255, 0);
    Serial.println("verde");
  }
  else if ( ph > 0  && ph < 65 ) {
    pixels.setPixelColor(1, pixels.Color(150,0,0)); // Moderately bright green color.
    lcd.setRGB(255, 0, 0);
    Serial.println("rosso");
  }
  else if ( ph > 75  && ph < 140 ) {
    pixels.setPixelColor(1, pixels.Color(0,0,150)); // Moderately bright green color.
    lcd.setRGB(0, 0, 255);
    Serial.println("blu");  
  }
  
  
  // visualizza sui led esterni
  pixels.show(); 

  // rallenta un po' il giro
  delay(200);
}
