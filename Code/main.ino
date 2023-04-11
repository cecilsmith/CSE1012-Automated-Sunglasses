// Code written by Nathanael Smith, Julian Bookhout, and Samuel Helgeson
// Sample code and libraries from Adafriut--the supplier of the LTR390 sensor.

/*
The code in this program reads UV light and ambient light data from the LTR390. 
From there, thresholds are used to determine whether the sunglasses should be rotated up
or down to protect the user. A potentiometer is read and used to select modes: 'OFF', 'AMBIENT', 'UV', and 'ON'.
*/

#include <Arduino.h>
#include "Adafruit_LTR390.h"
#include <Servo.h>

#define potPin A1

Adafruit_LTR390 ltr = Adafruit_LTR390();
Servo servoOne;
Servo servoTwo;

int servoPin = 5;  // D5
int servoPin2 = 6; // D6

int up = 90;  // this is the down position for the other servo
int down = 0; // this is the up position for the other servo

int servoPos = up;
int servo2Pos = down;

float uvLight;
float uvDanger = 30; // found in testing
float amLight;
float amDanger = 100; // for testing purposes, find the actual dangerous levels

int dial = 0;

bool sunglassesState = false;

// Declare functions
void sunglassesDown();
void sunglassesUp();
void GetSensorData();

void setup()
{
  // Attach servos and write inital position (DOWN)
  servoOne.attach(servoPin);
  servoOne.write(servoPos);

  servoTwo.attach(servoPin2);
  servoTwo.write(servo2Pos);

  Serial.begin(9600);

  Serial.println("Automated Sunglasses Initialize");

  if (!ltr.begin())
  {
    Serial.println("Couldn't find LTR sensor!");
    while (1)
      delay(10);
  }
  Serial.println("Found LTR sensor!");

  // Set the settings for the LTR
  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);
}

void loop()
{
  // Get data from LTR and potentiometer
  GetSensorData();

  // Mode control
  if ((dial < 256))
  {
    // If 'OFF' sunglasses up
    sunglassesUp();
  }
  // Set servos to be in 'UV Mode' sensitive mode
  else if ((dial >= 256) && (dial < 512) && (uvLight > uvDanger))
  {
    // If UV light reaches danger levels, sunglasses down
    sunglassesDown();
  }

  else if ((dial >= 256) && (dial < 512) && (uvLight < uvDanger))
  {
    // If UV light is less than danger levels, sunglasses up
    sunglassesUp();
  }
  // Ambient light control
  else if ((dial >= 512) && (dial < 768) && (amLight > amDanger))
  {
    // If light level is greater than the comfortable level, sunglasses down
    Serial.println("AMmode");
    sunglassesDown();
  }
  else if ((dial >= 512) && (dial < 768) && (amLight < amDanger))
  {
    // If light level is less than the comfortable level, sunglasses up
    Serial.println("AMmode");
    sunglassesUp();
  }

  else if (dial >= 768)
  {
    // If 'ON' sunglasses down
    sunglassesDown();
  }
}

void GetSensorData()
{
  // Get potentiometer readings
  dial = analogRead(potPin);

  // Check for LTR data
  if (ltr.newDataAvailable())
  {
    ltr.setMode(LTR390_MODE_UVS);
    // Delay for swapping of modes
    delay(100);
    Serial.print("UV Data: ");
    uvLight = ltr.readUVS();
    Serial.println(uvLight);
    ltr.setMode(LTR390_MODE_ALS);
    // Delay for swapping of modes
    delay(100);
    Serial.print("AMBIENT Light Level: ");
    amLight = ltr.readALS();
    Serial.println(amLight);
  }
}

void sunglassesDown()
{
  // If the sunglasses are up, then...
  if (sunglassesState == false)
  {
    // Rotate the sunglasses down
    servoOne.write(down);
    servoTwo.write(up);

    // Update sunglasses state
    sunglassesState = true;
  }
  else
  {
    // Do nothing, the sunglasses are already down
  }
}

void sunglassesUp()
{
  // If the sunglasses are down, then ...
  if (sunglassesState == true)
  {
    // Rotate the sunglasses up
    servoOne.write(up);
    servoTwo.write(down);

    // Update the sunglasses state
    sunglassesState = false;
  }
  else
  {
    // Do nothing, the sunglasses are already up
  }
}
