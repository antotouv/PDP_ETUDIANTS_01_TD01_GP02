#include <Arduino.h>
#include <DHT.h>

#define CAPTEUR 33
#define LED 26

#define DHTTYPE DHT11

#define MEASURE_INTERVAL 5

DHT dht(CAPTEUR, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  dht.begin();

  Serial.println("===Etape 2 : Mesures temperature et humidite + mise en veille ===");
}

void loop() {

  float humidity = dht.readHumidity();

  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Erreur de lecture du capteur DHT11 !");
  } else {
    Serial.print("Humidite : ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.print("Temperature : ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  Serial.println("Mise en veille...\n");

  esp_sleep_enable_timer_wakeup(MEASURE_INTERVAL * 1000000ULL);
  esp_deep_sleep_start();
}
