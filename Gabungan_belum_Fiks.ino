#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>
#include <Adafruit_INA219.h>
 
// Mendeklarasikan Pin
#define DHTPIN 13       
#define DHTTYPE DHT22
#define SOILPIN 14 

// Menginisiasikan Objek Sensor
Adafruit_INA219 sensor219; 
RTC_DS3231 rtc; 
DHT dht(DHTPIN, DHTTYPE);
   
// Variabel Data Sensor 
float humiditydht;
float temperaturedht;
int soilMoisture;
float soilMoisturePercent;

void setup() {
  Serial.begin(115200);
  sensor219.begin();
  dht.begin();
  
  // Mengatur waktu saat ini
  rtc.adjust(DateTime(__DATE__, __TIME__));


}

void loop() {
  // Membaca data dan menyimpannya ke dalam variabel
 /// DHT22
  humiditydht = dht.readHumidity();
  temperaturedht = dht.readTemperature(); 
  
  /// Variabel Soil Moisture
  soilMoisture = analogRead(SOILPIN);
  soilMoisturePercent = map(soilMoisture, 260, 520, 100, 0); 

  /// INA219
  busVoltage = sensor219.getBusVoltage_V();
  current = sensor219.getCurrent_mA();
  
  /// RTC DS3231
  DateTime now = rtc.now();

  
  // Menampilkan Hasil
  /// Hasil RTC DS3231
  Serial.print("Tanggal: ");
  Serial.print(now.year(), DEC);
  Serial.print("/");
  printTwoDigits(now.month());
  Serial.print("/");
  printTwoDigits(now.day());
  Serial.print(" Waktu: ");
  printTwoDigits(now.hour());
  Serial.print(":");
  printTwoDigits(now.minute());
  Serial.print(":");
  printTwoDigits(now.second());
  Serial.println();

  /// Hasil INA219
  Serial.print("Voltage:   "); 
  Serial.print(busVoltage); 
  Serial.println(" V");  
  Serial.print("Current:       "); 
  Serial.print(current); 
  Serial.println(" mA");

  /// Hasil Soil Moisture
  Serial.print("Soil Moisture Value: ");
  Serial.print(soilMoisture);
  Serial.print(" - Soil Moisture Percentage: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");

  /// Hasil DHT22
  Serial.print("Humidity: ");
  Serial.print(humiditydht);
  Serial.print(" %, Temp: ");
  Serial.print(temperaturedht);
  Serial.println(" Celsius");

  delay(1000); // Tunggu 1 detik sebelum pembacaan berikutnya



    


}

// Fungsi untuk menampilkan bilangan digit dua
void printTwoDigits(int number) {
    if (number < 10) {
        Serial.print("0"); // Add a leading zero for single-digit numbers
    }
    Serial.print(number);
}
