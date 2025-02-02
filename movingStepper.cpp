#include <Arduino.h>
#include <Servo.h>

#define DIR_PIN 3      // Pin untuk mengontrol arah
#define STEP_PIN 4     // Pin untuk langkah
#define ENABLE_PIN 2   // Pin untuk mengaktifkan driver (opsional)

Servo myServo;

float ikiSteps; // INPUT
float steps;       // OUTPUT
int step_delay = 500;  // Delay antar langkah dalam mikrodetik

void moveStepper(int stepCount) {
  for (int i = 0; i < stepCount; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(step_delay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(step_delay);
  }
}

void setup() {
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  myServo.attach(7);

  digitalWrite(ENABLE_PIN, LOW);  // Aktifkan driver

  Serial.begin(9600);  // Mulai komunikasi Serial
  Serial.println("Masukkan jumlah step:");
  myServo.write(0);
}

void loop() {
  gerakServo();
  //gerakStepper();
}

void gerakStepper() {
  if (Serial.available() > 0) {
    int newSteps = Serial.parseInt(); // Baca input sebagai integer
    steps = abs(newSteps/1.8);
    if (newSteps != 0) {
      ikiSteps = newSteps;
      Serial.print("Derajat stepper: ");
      Serial.println(ikiSteps);
      digitalWrite(DIR_PIN, newSteps > 0 ? HIGH : LOW);
      moveStepper(steps);
    }
  }
}

void gerakServo() {
  int inputAngle = Serial.parseInt(); // Baca input sebagai integer
  int servoAngle = abs(inputAngle);
  if (inputAngle >= 0) {
    Serial.print("Derajat servo: ");
    Serial.println(servoAngle);
    myServo.write(servoAngle);
  }
}
