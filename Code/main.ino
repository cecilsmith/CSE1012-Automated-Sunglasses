#include <Arduino.h>
#include "Adafruit_LTR390.h"
#include <Servo.h>

#define potPin A1

Adafruit_LTR390 ltr = Adafruit_LTR390();
Servo servoOne;
Servo servoTwo;

int servoPos = 90;
int servo2Pos = 0;

int servoPin = 5;  // D5
int servoPin2 = 6; // D6

int up = 90;  ////make sure this is actually the up position   ///this is the down position for the other servo
int down = 0; ////make sure this is actually the down position   ///this is the up position for the other servo

float uvLight;
float uvDanger = 30; // found in testing
float amLight;
float amDanger = 100; // for testing purposes, find the actual dangerous levels

int dial = 0;
int previousValue = 0;

void setup()
{
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

  ltr.setGain(LTR390_GAIN_3);
  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);
}

// Control loop
void loop()
{
  // Get data from LTR and potentiometer
  GetSensorData();

  // Mode selector
  // Set the servos to be in 'OFF' postion
  if ((dial < 256) && (previousValue != 1))
  {
    delay(50);
    // Set the servos to be in the correct position
    servoPos = up;
    servoOne.write(servoPos);
    servo2Pos = down;
    servoTwo.write(servo2Pos);

    // Note which mode we were just in
    previousValue = 1;
  }
  // Set servos to be in 'UV Mode' sensitive mode
  else if ((dial >= 256) && (dial < 512) && (previousValue != 2) && (uvLight > uvDanger))
  {

    Serial.println("UVmode");
    delay(50);

    servoPos = down;
    servoOne.write(servoPos);

    servo2Pos = up;
    servoTwo.write(servo2Pos);

    previousValue = 2;
  }

  else if ((dial >= 256) && (dial < 512) && (previousValue != 6) && (uvLight < uvDanger))
  {
    delay(50);
    servoPos = up;
    servoOne.write(servoPos);

    servo2Pos = down;
    servoTwo.write(servo2Pos);

    previousValue = 6;
  }

  else if ((dial >= 512) && (dial < 768) && (previousValue != 3) && (amLight > amDanger))
  {
    Serial.println("AMBmode");
    delay(50);

    servoPos = down;
    servoOne.write(servoPos);

    servo2Pos = up;
    servoTwo.write(servo2Pos);

    previousValue = 3;
  }

  else if ((dial >= 512) && (dial < 768) && (previousValue != 4) && (amLight < amDanger))
  {

    Serial.println("AMmode");
    delay(50);

    servoPos = up;
    servoOne.write(servoPos);

    servo2Pos = down;
    servoTwo.write(servo2Pos);

    previousValue = 4;
  }

  else if ((dial >= 768) && (previousValue != 5))
  {
    delay(50);
    servoPos = down;
    servoOne.write(servoPos);

    servo2Pos = up;
    servoTwo.write(servo2Pos);

    previousValue = 5;
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
    delay(100);
    Serial.print("UV data: ");
    Serial.println(ltr.readUVS());
    uvLight = ltr.readUVS();
    ltr.setMode(LTR390_MODE_ALS);
    delay(100);
    Serial.print("AMBIENT LIGHT: ");
    Serial.println(ltr.readALS());
    amLight = ltr.readALS();
  }
}
