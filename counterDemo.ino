/*
  Project:   counterDemo
  Source:    http://github.com/pa3hcm/counterDemo
  Authors:   Ernest Neijenhuis
  Copyright: (c) 2019 Ernest Neijenhuis PA3HCM
*/

// Tested on Arduino Duemilanove / ATmega328, works up to ~150 kHz


/////////////////////////////////////////////////////////////////////////
// Constants

// Pin labels
const int P_IN = 2;

// LCD settings
const int LCD_ROWS    = 4;    // Number of display rows
const int LCD_COLS    = 20;   // Number of display columns
const int LCD_I2CADDR = 0x27; // I2C address, in most cases this is 0x27


/////////////////////////////////////////////////////////////////////////
// Libraries

// LiquidCrystal_I2C source & info:
// https://github.com/johnrickman/LiquidCrystal_I2C
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(LCD_I2CADDR, LCD_COLS, LCD_ROWS);


/////////////////////////////////////////////////////////////////////////
// Global variables

// Used to count cycles for frequency measurement
unsigned long cycles = 0;


/////////////////////////////////////////////////////////////////////////
// setup() routine

void setup() {
  Serial.begin(9600);
  Serial.print("=== Counter ===");
  
  pinMode(P_IN, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("=== Counter ===");

}


/////////////////////////////////////////////////////////////////////////
// Main loop() routine

void loop() {
  char freq[8];

  measureFreq();
  dtostrf(cycles/1000.0, 7, 2, freq);
  lcd.setCursor(0, 1);
  lcd.print("f = ");
  lcd.print(freq);
  lcd.print(" KHz ");
  Serial.println(freq);
}


/////////////////////////////////////////////////////////////////////////
// measureFreq() routine counts the cycles during a second and returns
// the measured frequency

void measureFreq() {
  cycles = 0;
  attachInterrupt(digitalPinToInterrupt(P_IN), countCycle, RISING);
  delay(1000);
  detachInterrupt(digitalPinToInterrupt(P_IN));
}


/////////////////////////////////////////////////////////////////////////
// countCycle() interrupt service routine, triggered whenever a rising
// edge is detected on the input pin.


void countCycle() {
  cycles++;
}
