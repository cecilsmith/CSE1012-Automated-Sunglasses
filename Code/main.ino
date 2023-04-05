#include <Arduino.h>
#include "Adafruit_LTR390.h"
#include <Servo.h>

#define potPin A1

Adafruit_LTR390 ltr = Adafruit_LTR390();
Servo servoOne;
Servo servoTwo;

int servoPos = 90;
int servo2Pos = 0;

int servoPin = 9;
int servoPin2 = 8;

int up = 90;  ////make sure this is actually the up position   ///this is the down position for the other servo
int down = 0; ////make sure this is actually the down position   ///this is the up position for the other servo

float uvLight;
float uvDanger = 100; // for testing purposes, find the actual dangerous levels
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
  Serial.println("Adafruit LTR-390 test");

  if (!ltr.begin())
  {
    Serial.println("Couldn't find LTR sensor!");
    while (1)
      delay(10);
  }
  Serial.println("Found LTR sensor!");

  //ltr.setMode(LTR390_MODE_ALS);
  //if (ltr.getMode() == LTR390_MODE_ALS)
  //{
  //  Serial.println("In ALS mode");
  //}
  //else
  //{
  //  Serial.println("In UVS mode");
  //}

  ltr.setGain(LTR390_GAIN_3);
  Serial.print("Gain : ");
  switch (ltr.getGain())
  {
  case LTR390_GAIN_1:
    Serial.println(1);
    break;
  case LTR390_GAIN_3:
    Serial.println(3);
    break;
  case LTR390_GAIN_6:
    Serial.println(6);
    break;
  case LTR390_GAIN_9:
    Serial.println(9);
    break;
  case LTR390_GAIN_18:
    Serial.println(18);
    break;
  }

  ltr.setResolution(LTR390_RESOLUTION_16BIT);
  Serial.print("Resolution : ");
  switch (ltr.getResolution())
  {
  case LTR390_RESOLUTION_13BIT:
    Serial.println(13);
    break;
  case LTR390_RESOLUTION_16BIT:
    Serial.println(16);
    break;
  case LTR390_RESOLUTION_17BIT:
    Serial.println(17);
    break;
  case LTR390_RESOLUTION_18BIT:
    Serial.println(18);
    break;
  case LTR390_RESOLUTION_19BIT:
    Serial.println(19);
    break;
  case LTR390_RESOLUTION_20BIT:
    Serial.println(20);
    break;
  }

  ltr.setThresholds(100, 1000);
  ltr.configInterrupt(true, LTR390_MODE_UVS);
  
}



void loop()
{
  dial = analogRead(potPin);
  Serial.print("dial: ");
  Serial.println(dial);
  Serial.print("servoPos: ");
  Serial.println(servoPos);
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
   delay(700);

Serial.println();


  if ((dial < 256) && (previousValue != 1))
  {
    servoPos = up;
    servoOne.write(servoPos);
    Serial.println(servoPos);

    servo2Pos = down;
    servoTwo.write(servo2Pos);
    Serial.println(servo2Pos);

    previousValue = 1;  
    Serial.println(previousValue);
    
  }
  else if ((dial >= 256) && (dial < 512) && (previousValue != 2)  && (uvLight > uvDanger))
  {
    // UVmode();
Serial.println("UVmode");
   delay(100);
     
      servoPos = down;
      servoOne.write(servoPos);
      Serial.println(servoPos);
      
      servo2Pos = up;
      servoTwo.write(servo2Pos);
      Serial.println(servo2Pos);
      
    previousValue = 2;
    Serial.println(previousValue);
  }

  else if ((dial >= 256) && (dial < 512) && (previousValue != 6)  && (uvLight < uvDanger))
   {
      servoPos = up;
      servoOne.write(servoPos);
      Serial.println(servoPos);
      
      servo2Pos = down;
      servoTwo.write(servo2Pos);
      Serial.println(servo2Pos);

       previousValue = 6;
    Serial.println(previousValue);
      }
      
  else if ((dial >= 512) && (dial < 768) && (previousValue != 3) && (amLight > amDanger))
  {
      Serial.println("AMmode");
         delay(100);
   
      servoPos = down;
      servoOne.write(servoPos);
      Serial.println(servoPos);
      
      servo2Pos = up;
      servoTwo.write(servo2Pos);
      Serial.println(servo2Pos);
      
      
    previousValue = 3;
    Serial.println(previousValue);
  }

  else if ((dial >= 512) && (dial < 768) && (previousValue != 5) && (amLight < amDanger))
  {
      Serial.println("AMmode");
         delay(100);
  
      servoPos = up;
      servoOne.write(servoPos);
      Serial.println(servoPos);
      
      servo2Pos = down;
      servoTwo.write(servo2Pos);
      Serial.println(servo2Pos);
      
      
    previousValue = 5;
    Serial.println(previousValue);
  }
  
  else if ((dial >= 768) && (previousValue != 4))
  {
    servoPos = down;
    servoOne.write(servoPos);
    Serial.println(servoPos);

    servo2Pos = up;
    servoTwo.write(servo2Pos);
    Serial.println(servo2Pos);

    previousValue = 4;
    Serial.println(previousValue);
  }


}




// To be added/modified
/*
void manualMode()
{
  // maybe manual mode? incorporate if buttons are used...
}

void ambientMode()
{
  // use uv code but sub in ambient light sensor
}

void UVmode()
{

  if ((uvLight > uvDanger) && (servoPos = up))
  {
    servoPos = down;
    servoOne.write(servoPos);
    Serial.println(servoPos);
  }

  else if ((uvLight < uvDanger) && (servoPos = down))
  {
    servoPos = up;
    servoOne.write(servoPos);
    Serial.println(servoPos);
  }
}
*/
