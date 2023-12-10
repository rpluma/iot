#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#define DISTANCE_PORT_L 5
#define DISTANCE_PORT_R 3
#define TCA9548A_ADDR 0x70

Adafruit_VL53L0X loxL = Adafruit_VL53L0X();
Adafruit_VL53L0X loxR = Adafruit_VL53L0X();

void TCA9548A_Select(uint8_t channel) {
  if (channel == DISTANCE_PORT_L) {
    Serial.print("Left distance sensor: ");
  } else if (channel == DISTANCE_PORT_R) {
    Serial.print("Right distance sensor: ");
  } else {
    Serial.println("Wrong channel");
  }  
  Wire.beginTransmission(TCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  TCA9548A_Select(DISTANCE_PORT_L);
  Serial.println("Adafruit VL53L0X test");  
  if (!loxL.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  
  TCA9548A_Select(DISTANCE_PORT_R);
  Serial.println("Adafruit VL53L0X test");  
  if (!loxR.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  
  
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() { 
  VL53L0X_RangingMeasurementData_t measureL;
  VL53L0X_RangingMeasurementData_t measureR;

  TCA9548A_Select(DISTANCE_PORT_L);
  loxL.rangingTest(&measureL, false); // pass in 'true' to get debug data printout!

  if (measureL.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); 
    Serial.println(measureL.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }

  TCA9548A_Select(DISTANCE_PORT_R);
  loxR.rangingTest(&measureR, false); // pass in 'true' to get debug data printout!

  if (measureR.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); 
    Serial.println(measureR.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }

  delay(1000);
}
