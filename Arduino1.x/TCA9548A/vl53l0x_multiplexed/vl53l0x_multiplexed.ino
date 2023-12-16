//------------ TCA9548A I2C Multiplexer

#include <Wire.h>
#define DISTANCE_PORT_L 5
#define DISTANCE_PORT_R 3

void TCA9548A_Select(uint8_t channel, uint8_t tca9548a_Addr=0x70, bool bVerbose = false) {
  if (bVerbose) {
    if (channel == DISTANCE_PORT_L) {
      Serial.print("Left distance sensor: ");
    } else if (channel == DISTANCE_PORT_R) {
      Serial.print("Right distance sensor: ");
    } else {
      Serial.println("Wrong channel");
    } 
  }
  Wire.beginTransmission(tca9548a_Addr);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

//----------- VL53L0X ToF Distance Sensor
#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X loxL = Adafruit_VL53L0X();
Adafruit_VL53L0X loxR = Adafruit_VL53L0X();


//----------- Simulink Initialization
int PieroInit(void) {
  Wire.begin();
  TCA9548A_Select(DISTANCE_PORT_L);
  if (!loxL.begin()) {
    return DISTANCE_PORT_L;
  } else {
    loxL.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
  }
  
  TCA9548A_Select(DISTANCE_PORT_R);
  if (!loxR.begin()) {
    return DISTANCE_PORT_R;
  } else {
    loxR.configSensor(Adafruit_VL53L0X::VL53L0X_SENSE_HIGH_ACCURACY);
  }
  
  return 0;
}

//----------- Simulink Update
void PieroUpdate(uint16_t *distL, uint16_t *distR) {
  VL53L0X_RangingMeasurementData_t measureL;
  VL53L0X_RangingMeasurementData_t measureR;
  static uint16_t lastL = 0, lastR = 0;
  static unsigned nextVL53L0X = 0;
  const unsigned pollVL53L0X = 500;
  const uint16_t OutOfRangeVL53L0X = 2001;

  if (nextVL53L0X < millis()){
    nextVL53L0X = millis() + pollVL53L0X;
    
    TCA9548A_Select(DISTANCE_PORT_L);
    loxL.rangingTest(&measureL, false); // pass in 'true' to get debug data printout!
    lastL = (measureL.RangeStatus != 4) ? measureL.RangeMilliMeter: OutOfRangeVL53L0X;

    TCA9548A_Select(DISTANCE_PORT_R);
    loxR.rangingTest(&measureR, false); // pass in 'true' to get debug data printout!
    lastR = (measureR.RangeStatus != 4) ? measureR.RangeMilliMeter: OutOfRangeVL53L0X;    
  }  
  *distL = lastL;
  *distR = lastR;
}

void setup() {
  Serial.begin(115200);    
  while (! Serial) { // wait until serial port opens for native USB devices
    delay(1);
  }
  Serial.println("Adafruit VL53L0X + TCA9548A I2C Multiplexer test\n--------------- Setup...");
  if (int err=PieroInit() != 0)
  {
    Serial.print(F("Failed to initialize, error code="));
    Serial.println(err);
    while(1);
  }
  
  Serial.println(F("--------------- ... setup completed!\n\n\n")); 
}


void loop() { 
  static uint16_t distL=0;
  static uint16_t distR=0;
  PieroUpdate(&distL, &distR);
  Serial.print("0 ");
  Serial.print(distL);
  Serial.print(" ");
  Serial.print(distR);
  Serial.println(" 2001");
  delay(1000);
}
