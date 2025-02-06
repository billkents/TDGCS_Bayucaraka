#include <Arduino.h>

#define DIR_PIN 3      // Pin untuk mengontrol arah
#define STEP_PIN 4     // Pin untuk langkah
#define ENABLE_PIN 2   // Pin untuk mengaktifkan driver (opsional)

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

  digitalWrite(ENABLE_PIN, LOW);  // Aktifkan driver

  Serial.begin(9600);  // Mulai komunikasi Serial
  Serial.println("Ingin digerakkan berapa derajat:");
}

void loop() {
  if (Serial.available() > 0) {
    int newSteps = Serial.parseInt(); // Baca input sebagai integer
    steps = abs(newSteps/1.8); // Derajat convert ke steps
    if (newSteps != 0) { // Biar serial nggak ngulang
      int ikiSteps = newSteps;
      Serial.print("Motor digerakkan ");
      Serial.println(ikiSteps);
      Serial.println("°");
      digitalWrite(DIR_PIN, newSteps > 0 ? HIGH : LOW);
      moveStepper(steps);
    }
  }
}
