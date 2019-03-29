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

Ultrasonic ultrasonicLeft(2,3);	// trig 2, echo 3
Ultrasonic ultrasonicRight(4,5); // trig 4, echo 5

// variable to hold the pin values
const int leftVibe = 12; //left is pin 12
const int rightVibe = 11; //right is pin 11

//variable to hold the reading from the sonar sensors
float leftResponse;
float rightResponse;

//variable to hold the rate of pulsing in ms
float pulseL;
float pulseR;

//variable for the functioning of the timer
unsigned long leftRead = 0;
unsigned long rightRead = 0;
//length to hold the vibe
const int vibeLength = 200;
//strength of the vibe (out of 255)
int vibeStrength = 100;

//if the sensor returns nothing, do nothing 
bool noLeftData;
bool noRightData;
bool leftOn;
bool rightOn;

void setup() {
  Serial.begin(9600);
  pinMode(leftVibe, OUTPUT);
  pinMode(rightVibe, OUTPUT);
}

void loop() {
  
  //pass the readings from the sensors into the variables and set the maximum range
  calibrate();

  //Left sensor controller 
   if(!leftOn && !noLeftData && millis() - leftRead >= pulseL){
          Serial.print("LEFT ON");
          leftOn = true;
          analogWrite(leftVibe, vibeStrength);
          leftRead = millis();
             } else if (leftOn && millis() - leftRead >= vibeLength){
              leftOn = false;
              digitalWrite(leftVibe, LOW);
              leftRead = millis();
             }
//          leftVibeTime = millis();


  //Right sensor controller 
    if(!rightOn && !noRightData && millis() - rightRead >= pulseR) {
          Serial.print("RIGHT ON");
          rightOn = true;
          analogWrite(rightVibe, vibeStrength);
          rightRead = millis();
            } else if(rightOn && millis() - rightRead >= vibeLength){
              rightOn = false;
              digitalWrite(rightVibe, LOW);
              rightRead = millis();
            } 
 //         rightVibeTime = millis();
     
 
  Serial.print(pulseL);
  Serial.print(" ");
  Serial.print(pulseR);
  delay(500);
//  
  Serial.println();
}

void calibrate(){
 
  leftResponse = ultrasonicLeft.read(INC);
  rightResponse = ultrasonicRight.read(INC);

  //***********************Cap the range at 8 feet (96 inches)
  if(leftResponse >=121){
    noLeftData = true;
  } else if(leftResponse <=10){
    noLeftData = true;
  } else {
    noLeftData = false;
  }
  if(rightResponse >= 121){
    noRightData= true;
  } else if(rightResponse <=4){
    noRightData = true;
  } else {
    noRightData = false;
  }
  //set the rate of pulsing - 60 inches max to 1 inch min, 6000ms max to 100ms min
  pulseL = map(leftResponse, 1, 140, 200, 2000);
  pulseR = map(rightResponse, 1, 140, 200, 2000);
} 
