// HC-SR04-test.ino
// 
// Get distance information from Ultrasonic Ranging Module HC-SR04 and 
// send it via serial port.
//
// electronut.in

#include "Arduino.h"

// Sensor input.
int pinTrigger1 = 12;
int pinEcho1 = 11;
int pinTrigger2 = 10;
int pinEcho2 = 9;

// LED input.
int pinGreen = 2;
int pinYellow = 3;
int pinRed = 4;

void setup()
{
  // initialize serial comms
  Serial.begin(9600); 

  // set pins 
  pinMode(pinTrigger1, OUTPUT);
  pinMode(pinEcho1, INPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinYellow, OUTPUT);
  pinMode(pinRed, OUTPUT);
  
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
  int duration2 = readSensor(pinTrigger2, pinEcho2);
  float distance1 = calcDist(duration1);
  float distance2 = calcDist(duration2);
  
  Serial.print(distance1);
  Serial.print(" ");
  Serial.println(distance2);

  digitalWrite(pinGreen, LOW);
  digitalWrite(pinYellow, LOW);
  digitalWrite(pinRed, LOW);
    
  if(distance1 < 50) {
    digitalWrite(pinRed, HIGH);
  }
  else if(distance1 < 100) {
    digitalWrite(pinYellow, HIGH);
  }
  else {
    digitalWrite(pinGreen, HIGH);
  }
  // wait 
  delay(70);
}

