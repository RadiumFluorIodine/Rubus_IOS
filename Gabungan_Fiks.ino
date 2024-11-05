#include <Wire.h>
#include <DHT.h>
#include <RTClib.h>
#include <Adafruit_INA219.h>


// Definisikan sensor dan pin
Adafruit_INA219 ina219;
RTC_DS3231 rtc;

#define DHTPIN  13
#define DHTTYPE DHT22
#define SOILPIN  14
DHT dht(DHTPIN, DHTTYPE);

// Variabel 
float humidity, temperature, voltage, current;
int soilMoisture, soilMoisturePercent;
 
void setup() {
  Serial.begin(9600);
  ina219.begin();
  dht.begin();
  Wire.begin();
   
  if (!rtc.begin()) {
        Serial.println("RTC not detected");
        while (1); 
    }

  // Waktu
  rtc.adjust(DateTime(__DATE__, __TIME__));
  

}

void loop() {
  // Data DHT22
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Data INA219
  voltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();

  // Data RTC DS3231
  DateTime now = rtc.now();

  // Data Soil Moisture
  soilMoisture = analogRead(SOILPIN);
  soilMoisturePercent = map(soilMoisture, 260, 520, 100, 0);

  // Tamplikan Hasil Serial Monitor
  String output = "{node2" + String(current) + "," + String(voltage) + "," + String(temperature) + "," + String(humidity) + "," + String(soilMoisturePercent) + "}";
  Serial.print(output);
  delay(1000);
}
