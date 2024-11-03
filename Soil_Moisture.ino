// Pin konfigurasi
const int soilMoisturePin = 34; // Pin ADC untuk pembacaan analog dari sensor kelembaban tanah
const int outputPin = 13;       // Pin output untuk kontrol perangkat

// Nilai kalibrasi (sesuaikan setelah kalibrasi sensor)
int minValue = 3200; // Nilai analog ketika tanah benar-benar kering
int maxValue = 1500; // Nilai analog ketika tanah benar-benar basah

void setup() {
  Serial.begin(9600);
  pinMode(soilMoisturePin, INPUT); // Mengatur pin sensor sebagai input
  pinMode(outputPin, OUTPUT);       // Mengatur pin output sebagai output
}

void loop() {
  // Membaca nilai dari sensor kelembaban tanah
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Menghitung persentase kelembaban
  int soilMoisturePercent = map(soilMoistureValue, minValue, maxValue, 0, 100);
  
  // Memastikan persentase berada dalam rentang 0-100
  soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

  // Menampilkan nilai kelembaban di Serial Monitor
  Serial.print("Soil Moisture Value: ");
  Serial.print(soilMoistureValue);
  Serial.print(" - Soil Moisture Percentage: ");
  Serial.print(soilMoisturePercent);
  Serial.println("%");

  delay(1000); // Tunggu 1 detik sebelum pembacaan berikutnya
}
