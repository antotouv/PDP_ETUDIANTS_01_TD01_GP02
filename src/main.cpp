#include <Arduino.h>
#include <DHT.h>

#define CAPTEUR 33
#define LED 26

#define DHTTYPE DHT11

#define SLEEP_TIME 5

DHT dht(CAPTEUR, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  dht.begin();

  Serial.println("=== Etape 3 - Gestion de l'alimentation ===");

  float humidity = dht.readHumidity();

  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erreur de lecture du capteur DHT11");
  } else {
    Serial.print("Humidite : ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  Serial.println("Passage en deep sleep...");
  Serial.println();

  esp_sleep_enable_timer_wakeup(SLEEP_TIME * 1000000ULL);

  esp_deep_sleep_start();
}

void loop() {
}
