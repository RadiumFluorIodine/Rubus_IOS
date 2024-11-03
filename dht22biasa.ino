#include <DHT.h>

// Constants
#define DHTPIN 13         // what pin we're connected to
#define DHTTYPE DHT22     // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// Variables
int chk;
float humiditydht;
float temperaturedht;

void setup()
{
    Serial.begin(9600);
    dht.begin();
}

void loop()
{
    // Read data and store it to variables humiditydht and temperaturedht
    humiditydht = dht.readHumidity();
    temperaturedht = dht.readTemperature();
    // Print temperaturedht and humiditydhtidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humiditydht);
    Serial.print(" %, Temp: ");
    Serial.print(temperaturedht);
    Serial.println(" Celsius");
    delay(1000); // Delay 2 sec.
}