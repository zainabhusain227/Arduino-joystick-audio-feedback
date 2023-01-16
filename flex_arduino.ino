const int flexPin = A0;      // Pin connected to voltage divider output
#define OUTPUT_PIN 9    // Signal output pin

// Change these constants according to your project's design
const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 10000.0;  // resistor used to create a voltage divider
const float flatResistance = 25000.0; // resistance when flat
const float bendResistance = 100000.0;  // resistance at 90 deg

//const float  outpin=8;
//const float  freq=2000;
//const float  duration=1000/8;

int mode=1;
//mode=1 is the musical pitches
//mode=2 is white noise which transitions to beeps getting faster
//mode=3 is white noise narrowing to a constant tone
//mode=4 is linearly increasing pitches

float dutyCycle;        // Duty cycle (pulse width) percentage
int minFrequency;       // The minimum frequency of the range
int maxFrequency;       // The maximum frequency of the range
  
#include "pitches.h"


void setup() {
  Serial.begin(9600);
  pinMode(flexPin, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  // Set the duty cycle. For most
  // purposes you will want to leave the duty cycle set
  // to 50%.
  dutyCycle = 50;
  // Set the white noise frequency range
  minFrequency = 720;
  maxFrequency = 1440;
}

void mode_1(){
  int flex = analogRead(flexPin);
  //.5 < gap && gap < 1
  if (flex > 950) {
    //highest note for maximum bend
    tone(9, NOTE_D4,100);
  } 
  else if (flex > 900){
    tone(9, NOTE_C4,100);
  }
  else if (flex > 850){
    tone(9, NOTE_B3,100);
  }
  else if (flex > 700){
    tone(9, NOTE_A3,100);
  }
  else if (flex > 600){
    tone(9, NOTE_G3,100);
  }
  else if (flex > 500){
    tone(9, NOTE_F3,100);
  }
  else if (flex > 400){
    tone(9, NOTE_E3,100);
  }
  else if (flex > 200){
    tone(9, NOTE_D3,100);
  }
  else if (flex > 0){
    tone(9, NOTE_C3,100); 
  }
  delay(300);
  noTone(9); 
  Serial.println(String(flex));
  
}

void mode_2(){
  int flex = analogRead(flexPin);
  //.5 < gap && gap < 1
  if (flex > 950) {
    //highest note for maximum bend
    tone(9, NOTE_D4,100);
  } 
  else if (flex > 900){
    tone(9, NOTE_C4,100);
  }
  else if (flex > 850){
    tone(9, NOTE_B3,100);
  }
  else if (flex > 700){
    tone(9, NOTE_A3,100);
  }
  else if (flex > 600){
    tone(9, NOTE_G3,100);
  }
  else if (flex > 500){
    tone(9, NOTE_F3,100);
  }
  else if (flex > 400){
    tone(9, NOTE_E3,100);
  }
  else if (flex > 200){
    tone(9, NOTE_D3,100);
  }
  else if (flex > 10){
    tone(9, NOTE_C3,100); 
  }
  else {
    //everything below 10, set as white noise
    double frequency = random(minFrequency,maxFrequency);
    double period = 1000000 / frequency;
    double offFor = period - (period * (dutyCycle/100));
    double onFor = period - offFor;

    if( period > 16383 ) {
    // If the period is greater than 16383 then use the millisecond timer delay,
    // otherwise use the microsecond timer delay. Currently, the largest value that
    // will produce an accurate delay for the microsecond timer is 16383.

    digitalWrite(OUTPUT_PIN, HIGH);
    delay((long)onFor/1000);
    
    digitalWrite(OUTPUT_PIN, LOW);
    delay((long)offFor/1000);
  } else {
    digitalWrite(OUTPUT_PIN, HIGH);
    delayMicroseconds((long)onFor);
    
    digitalWrite(OUTPUT_PIN, LOW);
    delayMicroseconds((long)offFor);
  }
  }
  delay(300);
  noTone(8);
  Serial.println(String(flex));
}

void mode_3(){
 
  int flex = analogRead(flexPin);
  
  double period_var=1000000;
  if (flex > 800) {
    period_var=500000;
  } 
  else if (flex > 200){
    period_var=100000;
  }
  
  double frequency = random(minFrequency,maxFrequency);
  double period = period_var / frequency;
  double offFor = period - (period * (dutyCycle/100));
  double onFor = period - offFor;
  if( period > 16383 ) {
    // If the period is greater than 16383 then use the millisecond timer delay,
    // otherwise use the microsecond timer delay. Currently, the largest value that
    // will produce an accurate delay for the microsecond timer is 16383.
    digitalWrite(OUTPUT_PIN, HIGH);
    delay((long)onFor/1000);
    
    digitalWrite(OUTPUT_PIN, LOW);
    delay((long)offFor/1000);
  } else {
    digitalWrite(OUTPUT_PIN, HIGH);
    delayMicroseconds((long)onFor);
    
    digitalWrite(OUTPUT_PIN, LOW);
    delayMicroseconds((long)offFor);
  }  
  //delay(300);
  //noTone(8);
  //Serial.println(String(flex));
}


void loop() {
  // Read the ADC, and calculate voltage and resistance from it
  mode_1();
}
