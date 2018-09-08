#include <BME280I2C.h>
#include <Wire.h>
#include <Servo.h>

#define SERIAL_BAUD 9600
#define PIN_Servo D5

#define time_SendData 30 * 1000

float BME280_Temp, BME280_Humidity, BME280_Pressure;
void setup() {
  // put your setup code here, to run once:
  setup_BME280();
  setup_Servo();
  setup_Thingspeak();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_BME280();
  loop_Servo();
  loop_Thingspeak();
  delay(500);
}

