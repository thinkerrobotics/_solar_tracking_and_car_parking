#include <Servo.h>

Servo myservo1;
Servo servo;

int IR1 = 2;
int IR2 = 4;

int Slot = 4;           //Enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

#define LDR1 A0
#define LDR2 A1
#define error 10
int Spoint = 90;

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  myservo1.attach(3);
  myservo1.write(100);

  servo.attach(11);
  servo.write(Spoint);
  delay(1000);
}

void loop() {
  // Solar Tracking System
  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);
  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);

  if ((value1 <= error) || (value2 <= error)) {
    // LDR values are within the error range, do nothing
  } else {
    if (ldr1 > ldr2) {
      Spoint--;
    } else {
      Spoint++;
    }
  }
  servo.write(Spoint);

  // Car Parking System
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0);
        Slot = Slot - 1;
      }
    }
  }

  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo1.write(0);
      Slot = Slot + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo1.write(100);
    flag1 = 0;
    flag2 = 0;
  }
}
