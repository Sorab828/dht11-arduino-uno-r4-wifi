#include <Arduino.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
    Serial.println("DHT11 Sensor Initialized");
}

void loop() {
// write your code here
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        delay(2000);
        return;
    }
    Serial.println("Humidity: ");
    Serial.println(humidity);
    Serial.println(" %  |  ");
    Serial.println("Temperature: ");
    Serial.println("Temperature: ");
    Serial.println(temperature);
    Serial.println(" C ");
    delay(2000);

}