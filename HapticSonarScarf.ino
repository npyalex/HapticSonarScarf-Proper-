/*
 * 
 * 
 * Syntax: Ultrasonic name(Trig, Echo)
 * By default, the distance returned by the read()
 * method is in centimeters. To get the distance in inches,
 * pass INC as a parameter.
 * Example: ultrasonic.read(INC)
 *
 * uses Ultrasonic.h
 * by Erick Simões (github: @ErickSimoes | twitter: @AloErickSimoes)
 *
 * 
 */

#include <Ultrasonic.h>

Ultrasonic ultrasonicLeft(2,3);	// An ultrasonic sensor HC-04
Ultrasonic ultrasonicRight(4,5);

// variable to hold the pin values
const int leftVibe = 12;
const int rightVibe = 11;

//variable to hold the reading from the sonar sensors
int leftResponse;
int rightResponse;

//variable to hold the rate of pulsing
int pulseL;
int pulseR;

//variable for the functioning of the timer
unsigned long leftRead = 0;
unsigned long rightRead = 0;
unsigned long leftVibeTime = 0;
unsigned long rightVibeTime = 0;
//length to hold the vibe
const long vibeLength = 1000;
//strength of the vibe (out of 255)
int vibeStrength = 200;

//if the sensor returns nothing, do nothing
bool noLeftData;
bool noRightData;

void setup() {
  Serial.begin(9600);
  pinMode(leftVibe, OUTPUT);
  pinMode(rightVibe, OUTPUT);
}

void loop() {
  
  //pass the readings from the sensors into the variables and set the maximum range
  calibrate();

  //pass the rate of pulses into each vibe
//  if(noLeftData == false){
//    pulse(pulseL, leftVibe);
  if(millis() - leftRead >= pulseL) {
//    vibe(whichPin);
      digitalWrite(leftVibe, HIGH);
        if(millis() - leftVibeTime >= vibeLength){
        digitalWrite(leftVibe, LOW);
        leftVibeTime = millis();
        }
//        Serial.println("LEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFT");
        leftRead = millis();
    }
  if(millis() - rightRead >= pulseR) {
//    vibe(whichPin);
      digitalWrite(rightVibe, HIGH);
        if(millis() - rightVibeTime >= vibeLength){
        digitalWrite(rightVibe, LOW);
        rightVibeTime = millis();
        }
//        Serial.println("RIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIGGGHT");
        rightRead = millis();
    }

 // } else {
//    Serial.print("No Left Data");
//  }
//  if(noRightData == false){
//    pulse(pulseR, rightVibe);
//  } else {
//    Serial.print("No Right Data");


  
  Serial.print(pulseL);
  Serial.print(" ");
  Serial.print(pulseR);
  delay(10);
//  
  Serial.println();
}

//void pulse(int rate, int whichPin){
//  
//  if(millis() - lastRead >= rate) {
////    vibe(whichPin);
//      digitalWrite(whichPin, HIGH);
//        if(millis() - vibeTime >= vibeLength){
//        digitalWrite(whichPin, LOW);
//        vibeTime = millis();
//        }
//      Serial.print(whichPin);
//      Serial.print("*********************************************************************/");
//      lastRead = millis();
//    }
//}

void calibrate(){
 
  leftResponse = ultrasonicLeft.read(INC);
  rightResponse = ultrasonicRight.read(INC);

  if(leftResponse >=61){
    noLeftData = true;
  } else {
    noLeftData = false;
  }
  if(rightResponse >= 61){
    noRightData= true;
  } else {
    noRightData= false;
  }
  //set the rate of pulsing - 60 inches max to 1 inch min, 6000ms max to 100ms min
  pulseL = map(leftResponse, 60, 1, 6000, 100);
  pulseR = map(rightResponse, 60, 1, 6000, 100);
}

//void vibe(int whichPin){
//  analogWrite(whichPin, vibeStrength);
//  if(millis() - lastRead >= vibeLength){
//    analogWrite(whichPin, LOW);
//  }
//}
