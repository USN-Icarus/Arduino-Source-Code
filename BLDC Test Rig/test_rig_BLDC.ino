/*
 * Values from the  potentiometer
 */

#include <Servo.h>

Servo motor1;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  motor1.attach(7, 1000, 2000);
}

bool emergency = false;
void loop() {
  if (Serial.available()) {
    emergency = true;
  }
  if (emergency){
    motor1.writeMicroseconds(0);
    Serial.println("Emergency! Motor pulse: 0");
  }
  int analogValue = analogRead(A0);
  int motorPulse = map(analogValue, 0, 1023, 900, 2100);
  motorPulse = constrain(motorPulse, 1000, 2000);
  motor1.writeMicroseconds(motorPulse);
  Serial.print("Motor pulse: ");
  Serial.println(motorPulse);
}

/*
 * Values from computer
 */
 /*
#include <Servo.h>

Servo motor1;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  motor1.attach(7, 1000, 2000);
}


void loop() {
  if (Serial.available()) {
    int motorPulse = Serial.parseInt();
    motor1.writeMicroseconds(motorPulse);
    Serial.print("Motor pulse: ");
    Serial.println(motorPulse);
  }
}
*/
