

BME280I2C bme;    // Default : forced mode, standby time = 1000 ms
                  // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,

                  
#define Temp_Offset -1.2

extern float BME280_Temp, BME280_Humidity, BME280_Pressure;

//////////////////////////////////////////////////////////////////
void setup_BME280()
{
  Serial.begin(SERIAL_BAUD);

  while(!Serial) {} // Wait

  Wire.begin(D1,D2);

  while(!bme.begin())
  {
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }

  // bme.chipID(); // Deprecated. See chipModel().
  switch(bme.chipModel())
  {
     case BME280::ChipModel_BME280:
       Serial.println("Found BME280 sensor! Success.");
       break;
     case BME280::ChipModel_BMP280:
       Serial.println("Found BMP280 sensor! No Humidity available.");
       break;
     default:
       Serial.println("Found UNKNOWN sensor! Error!");
  }
}

//////////////////////////////////////////////////////////////////
void loop_BME280()
{
   printBME280Data(&Serial);
}

//////////////////////////////////////////////////////////////////
void printBME280Data
(
   Stream* client
)
{
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);

   bme.read(BME280_Pressure, BME280_Temp, BME280_Humidity, tempUnit, presUnit);


   BME280_Temp = BME280_Temp + Temp_Offset;
  
   client->print("Temp: ");
   client->print(BME280_Temp);
   client->print("°"+ String(tempUnit == BME280::TempUnit_Celsius ? 'C' :'F'));
   client->print("\t\tHumidity: ");
   client->print(BME280_Humidity);
   client->print("% RH");
   client->print("\t\tPressure: ");
   client->print(BME280_Pressure);
   client->println(" Pa");
}
