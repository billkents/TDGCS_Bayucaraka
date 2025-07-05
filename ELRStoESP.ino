// ELRS to ESP32 via Crossfire (CRSF) Serial Protocol

#include <Arduino.h>
#include <HardwareSerial.h>
#include "AlfredoCRSF.h"

HardwareSerial CRSFSerial(1);

AlfredoCRSF crsf;

void setup() {
  Serial.begin(115200);
  CRSFSerial.begin(460800, SERIAL_8N1, 16, 17); // RX:16, TX:17

  crsf.begin(CRSFSerial);
  Serial.println("CRSF Ready!");
}

void loop() {
  crsf.update();

  Serial.print("Roll: ");
  Serial.println(crsf.getChannel(1));

  Serial.print("Pitch: ");
  Serial.println(crsf.getChannel(2));

  Serial.print("Throttle: ");
  Serial.println(crsf.getChannel(3));

  Serial.print("Yaw: ");
  Serial.println(crsf.getChannel(4));

  Serial.println("----------------------");

  delay(200);
}