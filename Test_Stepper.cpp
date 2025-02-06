#include <Arduino.h>

#define DIR_PIN 3      // Pin untuk mengontrol arah
#define STEP_PIN 4     // Pin untuk langkah
#define ENABLE_PIN 2  // Pin untuk mengaktifkan driver (opsional)

int steps = 200;       // Langkah yang diinginkan (disesuaikan dengan kebutuhan)
int step_delay = 500;  // Delay antar langkah dalam mikrodetik (semakin kecil, semakin cepat)

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

  digitalWrite(ENABLE_PIN, LOW);  // Aktifkan driver (LOW untuk aktif)
}

void loop() {
  // Gerak maju
  digitalWrite(DIR_PIN, HIGH);
  moveStepper(steps);

  delay(1000);  // Tunggu 1 detik

  // Gerak mundur
  digitalWrite(DIR_PIN, LOW);
  moveStepper(steps);

  delay(1000);  // Tunggu 1 detik
}
