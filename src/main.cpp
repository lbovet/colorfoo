#include <Arduino.h>

// #define DEBUG

int level = A6;
int button = 9;

int r = 6;
int g = 3;
int b = 5;

int counter = 0;
int leds[3] = { r, g, b };
int current = 0;
int color[3] = { 0, 0, 0 };
int reading = 0;

void setup() {
    for(int i=0; i<3; i++) {
      pinMode(leds[i], OUTPUT);
    }
    pinMode(button, INPUT);
}

void out();

void loop() {
  reading = 1 && !digitalRead(button);
  #ifdef DEBUG
  Serial.print(color[0]);
  Serial.print(" ");
  Serial.print(color[1]);
  Serial.print(" ");
  Serial.print(color[2]);
  Serial.print(" ");
  Serial.println(reading);
  #endif
  if(reading) {
    counter++;
    if(counter > 10) {
      counter = 0;
      analogWrite(leds[current], 0);
      current++;
      if(current == 3) {
        current = 0;
      }
      analogWrite(leds[current], 255);
    }
    color[current] = (color[current] + 2 * analogRead(level) ) / 3 ;
  } else {
    int max = ( color[0] < color[1] ) ? 1: 0;
    max = ( color[max] < color[2] ) ? 2 : max;
    digitalWrite(r, 0);
    digitalWrite(g, 0);
    digitalWrite(b, 0);
    digitalWrite(leds[max], 255);
  }
  delay(2);
}
