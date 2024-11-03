#include <Wire.h>
#include <DHT.h>
#include <Adafruit_INA219.h>
#include <RTClib.h> 

Adafruit_INA219 sensor219; // Deklarasi INA219
RTC_DS3231 rtc; // Deklarasi RTC DS3231

// Konstanta
#define DHTPIN 13       
#define DHTTYPE DHT22
#define SOIL_SENSOR_PIN 14     
DHT dht(DHTPIN, DHTTYPE);



// Variabel
float humiditydht;
float temperaturedht;


// Nilai kalibrasi 
int minValue = 3200; // Nilai analog ketika tanah kering
int maxValue = 1500; // Nilai analog ketika tanah basah



void setup() {
  Serial.begin(9600);
  sensor219.begin();
  dht.begin();
  Wire.begin();
  pinMode(SOIL_SENSOR_PIN, INPUT);
  
  // Mengatur waktu saat ini
  rtc.adjust(DateTime(__DATE__, __TIME__));


}

void loop() {
  // Membaca data dan menyimpannya ke dalam variabel
  /// Variabel INA219
  float busVoltage = 0;
  float current = 0; // Measure in milli amps
  float power = 0;

  busVoltage = sensor219.getBusVoltage_V();
  current = sensor219.getCurrent_mA();
  power = busVoltage * (current/1000);

  /// Variabel DHT22
  humiditydht = dht.readHumidity();
  temperaturedht = dht.readTemperature();

  /// Variabel RTC DS3231
  DateTime now = rtc.now();

  /// Variabel Soil Moisture
  int soilMoistureValue = analogRead(SOIL_SENSOR_PIN);
  int soilMoisturePercent = map(soilMoistureValue, minValue, maxValue, 0, 100);
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  // Menampilkan Hasil
  /// Hasil RTC DS3231
  Serial.print("Current Date: ");
  Serial.print(now.year(), DEC);
  Serial.print("/");
  printTwoDigits(now.month());
  Serial.print("/");
  printTwoDigits(now.day());
  Serial.print(" Current Time: ");
  printTwoDigits(now.hour());
  Serial.print(":");
  printTwoDigits(now.minute());
  Serial.print(":");
  printTwoDigits(now.second());
  Serial.println();

  /// Hasil INA219
  Serial.print("Bus Voltage:   "); 
  Serial.print(busVoltage); 
  Serial.println(" V");  
  Serial.print("Current:       "); 
  Serial.print(current); 
  Serial.println(" mA");

  /// Hasil Soil Moisture
  Serial.print("Soil Moisture Value: ");
  Serial.print(soilMoistureValue);
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