// Add mathmatical functions
#include "math.h"
#include <medianFilter.h>

// Defining Pins on the Ardunio to the respective Ultrasonic sensors
#define FRONT_TRIG 11 
#define FRONT_ECHO 10 
#define RIGHT_TRIG 9
#define RIGHT_ECHO 8
#define LEFT_TRIG 13   
#define LEFT_ECHO 12
#define TOP_TRIG 7
#define TOP_ECHO 6
#define BACK_TRIG 5
#define BACK_ECHO 4


// Filter to remove large spikes from the sensor input, which can cause irratic behavior for the drone.
medianFilter FilterFront;
medianFilter FilterBack;
medianFilter FilterRight;
medianFilter FilterLeft;
medianFilter FilterTop;



// Setting up input and outputs for the pinModes for the each sensor respectively
void setup() {                 // initializes serial communication
  Serial.begin (9600);         // Open serial monitor at 9600 baud to see ping results.

  FilterFront.begin();
  FilterBack.begin();
  FilterRight.begin();
  FilterLeft.begin();
  FilterTop.begin();
  
  pinMode(FRONT_TRIG, OUTPUT); // Output = sonar burst from the ultrasonic sensor to an object
  pinMode(FRONT_ECHO, INPUT);  // Input  = received sound wave reflected from the obstacle
  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);
  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);
  pinMode(TOP_TRIG, OUTPUT);
  pinMode(TOP_ECHO, INPUT);
  pinMode(BACK_TRIG, OUTPUT);
  pinMode(BACK_ECHO, INPUT);

}

void loop() {
  long duration, FRONT,BACK, RIGHT, LEFT, TOP; // Duration used to calculate distance of an object from each sensor

  // Top triggers.
  digitalWrite(TOP_TRIG, LOW);            // LOW triggered to ensure no interference from incoming signals, before triggering HIGH
  delayMicroseconds(2);
  digitalWrite(TOP_TRIG, HIGH);           // Send outs ultrasonic wave
  delayMicroseconds(10);                  // Delay as speicifed by datasheet
  digitalWrite(TOP_TRIG, LOW);            
  duration = pulseIn(TOP_ECHO, HIGH);     // Calculates time taken to receive signal from reflected signal, pulse is LOW when signal is received
  TOP = round((FilterTop.run((duration/2) / 29.1)/10))*10;               // Calculates distances using the time calculated above and the speed of sound (300m/s)

  // Back triggers
  digitalWrite(BACK_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(BACK_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(BACK_TRIG, LOW);
  duration = pulseIn(BACK_ECHO, HIGH);
  BACK = round((FilterBack.run((duration/2) / 29.1)/10))*10;  
  
  // Front triggers
  digitalWrite(FRONT_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(FRONT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(FRONT_TRIG, LOW);
  duration = pulseIn(FRONT_ECHO, HIGH);
  FRONT = round((FilterFront.run((duration/2) / 29.1)/10))*10;  

  // Right Triggers
  digitalWrite(RIGHT_TRIG, LOW);
  digitalWrite(RIGHT_TRIG, HIGH);  
  delayMicroseconds(2);
  delayMicroseconds(10);
  digitalWrite(RIGHT_TRIG, LOW);
  duration = pulseIn(RIGHT_ECHO, HIGH);  
  RIGHT = round((FilterRight.run((duration/2) / 29.1)/10))*10;

  // Left Triggers
  digitalWrite(LEFT_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(LEFT_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(LEFT_TRIG, LOW);
  duration = pulseIn(LEFT_ECHO, HIGH);
  LEFT = round((FilterLeft.run((duration/2) / 29.1)/10))*10;
  
  const int sensorRange = 400;

  int rangeClampedTop = 0;
  if (TOP < sensorRange) {
    rangeClampedTop = TOP;
  }
  else {
    rangeClampedTop = sensorRange;
  }

  int rangeClampedBack = 0;
  if (BACK < sensorRange) {
    rangeClampedBack = BACK;
  }
  else {
    rangeClampedBack = sensorRange;
  }
  
  int rangeClampedFront = 0;
  if (FRONT < sensorRange) {
    rangeClampedFront = FRONT;
  }
  else {
    rangeClampedFront = sensorRange;
  }
  
  int rangeClampedLeft = 0;
  if(LEFT < sensorRange) {
    rangeClampedLeft = LEFT;
  }
  else {
    rangeClampedLeft = sensorRange;
  }

  int rangeClampedRight = 0;
  if(RIGHT < sensorRange) {
    rangeClampedRight = RIGHT;
  }
  else {
    rangeClampedRight = sensorRange;
  }

  int vX1 = rangeClampedFront;
  int vX2 = rangeClampedBack;  
  int vY1 = rangeClampedLeft;
  int vY2 = rangeClampedRight;
  int Top = rangeClampedTop;

  Serial.print(vX1);
  /*
  Serial.print(" ");
  Serial.print(vX2);
  Serial.print(" ");  
  Serial.print(vY1);
  Serial.print(" ");
  Serial.print(vY2);
  Serial.print(" ");
  Serial.print(Top);
  */
  Serial.print("\n");
}
