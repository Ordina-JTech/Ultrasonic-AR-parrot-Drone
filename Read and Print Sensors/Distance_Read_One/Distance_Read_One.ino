// Distance_Read_One.ino
// 
// Get distance information from Ultrasonic Ranging Modules HC-SR04 and 
// send it via serial port.
//
// Authors: Robert Horvers & Evert Poots

#include "Arduino.h"
#include <medianFilter.h>

medianFilter Filter1;
medianFilter Filter2;
medianFilter Filter3;
medianFilter Filter4;

// Sensor input.
int pinTrigger1 = 11;
int pinEcho1 = 10;
int pinTrigger2 = 13;
int pinEcho2 = 12;
int pinTrigger3 = 9;
int pinEcho3 = 8; 
int pinTrigger4 = 7;
int pinEcho4 = 6;

void setup()
{
  // initialize serial comms
  Serial.begin(9600); 
  Filter1.begin();
  Filter2 .begin();
  Filter3.begin();
  Filter4.begin();
       
    
  // set pins 
  pinMode(pinTrigger1, OUTPUT);
  pinMode(pinEcho1, INPUT);
  pinMode(pinTrigger2, OUTPUT);
  pinMode(pinEcho2, INPUT);
  pinMode(pinTrigger3, OUTPUT);
  pinMode(pinEcho3, INPUT);
  pinMode(pinTrigger4, OUTPUT);
  pinMode(pinEcho4, INPUT);
}

int readSensor(int pinTrigger, int pinEcho) {
  // send a 10us+ pulse
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  
  
  //  read duration of echo 
  return pulseIn(pinEcho, HIGH);
}

float calcDist(int duration) {
  // dist = duration * speed of sound * 1/2
  // dist in cm = duration in us * 1 x 10^{-6} * 340.26 * 100 * 1/2
  // =  0.017*duration
  return 0.017 * duration;
}

void loop()
{
  
  int duration1 = readSensor(pinTrigger1, pinEcho1);
  delay(50);
  int duration2 = readSensor(pinTrigger2, pinEcho2);
  delay(50);
  int duration3 = readSensor(pinTrigger3, pinEcho3);
  delay(50);  
  int duration4 = readSensor(pinTrigger4, pinEcho4);
  delay(50);
  
  float distance1 = Filter1.run(calcDist(duration1));
  float distance2 = Filter2.run(calcDist(duration2));
  float distance3 = Filter3.run(calcDist(duration3));
  float distance4 = Filter4.run(calcDist(duration4));

  Serial.print(distance1);
  Serial.print(" ");
  Serial.print(distance2);
  Serial.print(" ");
  Serial.print(distance3);
  Serial.print(" ");
  Serial.println(distance4);
  
  
  // wait 
  //delay(70);
}

