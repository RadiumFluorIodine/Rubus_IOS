#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <RTClib.h>
#include <Adafruit_INA219.h>


// Definisikan sensor dan pin
Adafruit_INA219 ina219;
RTC_DS3231 rtc;

#define ss 5
#define dio0 27
#define DHTPIN  4
#define DHTTYPE DHT22
#define SOILPIN  25
DHT dht(DHTPIN, DHTTYPE);

// Variabel 
float humidity, temperature, voltage, current;
int soilMoisture, soilMoisturePercent;
int counter = 0;
 
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


  while (!Serial);
  Serial.println("LoRa Sender");

  // Setup LoRa transceiver module
  LoRa.setPins(ss, dio0);
  
  // Replace the LoRa.begin(---E-) argument with your location's frequency 
  // 433E6 for Asia, 868E6 for Europe, 915E6 for North America
  while (!LoRa.begin(433E6)) {
    Serial.print(".");
    delay(500);
  }
  
  // Change sync word to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // Sync word ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");


}



void loop() {
  // LoRa
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // Data DHT22
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Data INA219
  voltage = ina219.getBusVoltage_V();
  current = ina219.getCurrent_mA();

  // Data RTC DS3231
  DateTime now = rtc.now();

  // Membuat string timestamp dengan sprintf untuk format dua digit
  char timestamp[20]; // Buffer untuk menyimpan format waktu
  sprintf(timestamp, "%02d/%02d/%04d %02d:%02d:%02d", 
          now.day(), now.month(), now.year(), 
          now.hour(), now.minute(), now.second());

  

  // Data Soil Moisture
  soilMoisture = analogRead(SOILPIN);
  soilMoisturePercent = map(soilMoisture, 260, 4095, 100, 0);

  // Tamplikan Hasil Serial Monitor dalam bentuk string
  String output = "{" + timestamp + "," + "node2" + "," + String(current) + "," + String(voltage) + "," + String(temperature) + "," + String(humidity) + "," + String(soilMoisturePercent) + "}";
  Serial.println(output);  
  
  // Mengirim Paket ke Reciever
  LoRa.beginPacket();
  LoRa.print(output);
  LoRa.endPacket();

  counter++;

  delay(1000);
}
