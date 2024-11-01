#include <Wire.h>           // Include Wire library for I2C communication
#include <RTClib.h>          // Include the RTC library

RTC_DS3231 rtc; // Initialize an instance of the RTC_DS3231 class

void setup() {
    Serial.begin(9600);  // Initialize Serial communication
    Wire.begin();          // Begin I2C communication

    if (!rtc.begin()) {
        Serial.println("RTC not detected");
        while (1); // Hang indefinitely if RTC is not found
    }

    // Uncomment the line below to set the RTC to the compile time
    rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
    // Read current time from the DS3231
    DateTime now = rtc.now();

    // Print the date and time
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

    delay(100); // Update every 1 second
}

// Function to print numbers with two digits
void printTwoDigits(int number) {
    if (number < 10) {
        Serial.print("0"); // Add a leading zero for single-digit numbers
    }
    Serial.print(number);
}
