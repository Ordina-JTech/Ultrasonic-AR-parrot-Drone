// HC-SR04-test.ino
// 
// Get distance information from Ultrasonic Ranging Module HC-SR04 and 
// send it via serial port.
//
// electronut.in

#include "Arduino.h"

int pinTrigger = 12;
int pinEcho = 11;

void setup()
{
  // initialize serial comms
  Serial.begin(9600); 

  // set pins 
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void loop()
{
  // send a 10us+ pulse
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(20);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(20);
  
  //  read duration of echo 
  int duration = pulseIn(pinEcho, HIGH);

  if(duration > 0) {
    // dist = duration * speed of sound * 1/2
    // dist in cm = duration in us * 1 x 10^{-6} * 340.26 * 100 * 1/2
    // =  0.017*duration
    float dist = 0.017 * duration;
    Serial.println(dist);
  }
  
  // wait 
  delay(70);
}
