#include <Arduino.h>
#include <Servo.h>
#include <SerialTransfer.h>

#define DIR_PIN 3      // Pin untuk mengontrol arah
#define STEP_PIN 4     // Pin untuk langkah
#define ENABLE_PIN 2   // Pin untuk mengaktifkan driver (opsional)

Servo myServo;

int step_delay = 500;  // Delay antar langkah dalam mikrodetik

// MPU9250 sensor data
float aX, aY, aZ, aSqrt, gX, gY, gZ, mX, mY, mZ, mDirection;

// Serial Transfer instance
SerialTransfer serialTransfer;

// Data structures for receiving and sending data
struct __attribute__((packed)) ReceiveFromSoftware {
  int32_t servo1Angle = -400; // Stepper 1 angle
  int32_t servo2Angle = -400; // Stepper 2 angle
} receive;

struct __attribute__((packed)) TransferToSoftware {
    float gps_lat = 0.0f;
    float gps_lng = 0.0f;
    float sat = 0;
    float gps_alt = 0.0f;
    float mpu_GyroX = 0.0f;
    float mpu_GyroY = 0.0f;
    float mpu_GyroZ = 0.0f;
    float mpu_MagDir = 0.0f;
} transfer;

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
  myServo.write(0);
  
  digitalWrite(ENABLE_PIN, LOW);
  
  Serial.begin(9600);  // Mulai komunikasi Serial
  serialTransfer.begin(Serial);

  Serial.println("Backend Akan Mengirimkan Random Derajat ....");
}

void loop() {
  if (serialTransfer.available()) {
    uint16_t recSize = serialTransfer.rxObj(receive, 0);

    int steps1 = abs(receive.servo1Angle); // Variable untuk servo
    int steps2 = receive.servo2Angle; // Variable untuk stepper

    Serial.print("servo 1 moved to ");
    Serial.print(steps1);
    Serial.println(" degrees.");

    Serial.print("servo 2 moved to ");
    Serial.print(steps2);
    Serial.println(" degrees.");

    // Gerak servo
    myServo.write(steps1);

    // Gerak stepper
    int steps = abs(steps2/1.8); // Dijadikan steps (200)
    digitalWrite(DIR_PIN, steps2 > 0 ? HIGH : LOW);
    moveStepper(steps);

    // Send back updated sensor and GPS data
    uint16_t sendSize = 0;
    sendSize = serialTransfer.txObj(transfer, sendSize);
    serialTransfer.sendData(sendSize);
  }

  delay(600); // Wait for a second
}
