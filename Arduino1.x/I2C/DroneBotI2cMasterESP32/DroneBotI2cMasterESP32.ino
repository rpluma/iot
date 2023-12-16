/* 
1) Prueba de comunicación ESP32-ESP32
  1a) Slave script no compila 
    - https://forum.arduino.cc/t/invalid-conversion-from-void-to-void-int-when-using-wire-onreceiv/656205
    - cambiamos: void receiveEvent(int WireSize)
  1b) Conexión de pines
    - CLK = 22 (amarillo)
    - SDA = 21 (naranja)
    - 3V3 = rojo
    - GND = marrón
  1c) Desconexión de alimentación
    - quitar el cable 3V3 rojo
    - cargar esclavo con powerbank
2) Bajar la frecuencia del reloj a la de Arduino
  - Frecuencia arduino 1: 100 kHz
  - Frecuencia ESP32: 
    - Librería i2c_master.h en lugar de Wire.h
    - I2C_CLK_SRC_DEFAULT
    - Ver https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2c.html#:~:text=ESP32%20supports%20both%20I2C%20Standard,to%20100KHz%20and%20400KHz%20respectively.&text=The%20frequency%20of%20SCL%20is,to%20make%20the%20frequency%20accurate.
  
  
2) Añadir multiplexor I2C
  - Sin seleccionar el canal no funciona
  - Seleccionamos canal con TCA9548A_Select(0);
  
4) Sustituir el esclavo ESP32 por Arduino UNO

*/
#include <Wire.h>

#define SLAVE_ADDR 9
#define ANSWERSIZE 5

#define CHANNEL_ESP32 0
#define CHANNEL_ARDUINO 4

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("\n\n---\nIni Setup I2C Master");
  Wire.begin();
  Serial.println("End Setup I2C Master");
}

void TCA9548A_Select(uint8_t channel, uint8_t tca9548a_Addr=0x70, bool bVerbose = false) {
  Wire.beginTransmission(tca9548a_Addr);
  Wire.write(1 << channel);
  Wire.endTransmission();
}


void loop() {
  String response;
  
  delay(50);
  
  Serial.println("Write data to EP32 slave");
  //TCA9548A_Select(CHANNEL_ESP32);
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  Wire.endTransmission();
  Serial.println("Received data");
  Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);
  response = "";
  while(Wire.available()){
    char b = Wire.read();
    response += b;    
  }
  Serial.println(response);
  /*
  Serial.println("Write data to Arduino slave");
  TCA9548A_Select(CHANNEL_ARDUINO);
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(0);
  Wire.endTransmission();
  Serial.println("Received data");
  Wire.requestFrom(SLAVE_ADDR, ANSWERSIZE);
  response = "";
  while(Wire.available()){
    char b = Wire.read();
    response += b;    
  }
  Serial.println(response);
  */
}
