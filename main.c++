#include <SR04.h>
#include <Servo.h>
#define trig 12
#define echo 11
#define button 8
SR04 sr04 = SR04(echo,trig);
long duration, distance, TargetAngle;
int pos = 0;
long ClosestTarget = 10000;
Servo servo1;


void setup()
{
  Serial.begin(9600);
  servo1.attach(9);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(button, INPUT);
}

void loop() {

  if(digitalRead(button) == LOW) { // look around for the closest object
   for (pos = 0; pos <= 180; pos += 3) 
   {
    servo1.write(pos);
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
  
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance=sr04.Distance();

     if (distance < ClosestTarget)
     {
      ClosestTarget = distance;
      TargetAngle = pos;
     }
  }

    distance=sr04.Distance();
    Serial.print("Closest Target = ");
    Serial.print(ClosestTarget);
    Serial.println(" ");
    Serial.print("Target Angle = ");
    Serial.print(TargetAngle);
    Serial.println(" ");


    servo1.write(TargetAngle); // look towards the closest object
    delay(100);


  }

    }
