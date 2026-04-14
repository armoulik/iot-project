#include <SoftwareSerial.h>
#include <DHT.h>

/* =========================
   Pins
   ========================= */
#define TURBIDITY_PIN A0
#define DHTPIN D4
#define DHTTYPE DHT11

SoftwareSerial phSerial(D5, D6); // RX, TX
DHT dht(DHTPIN, DHTTYPE);

/* =========================
   Variables
   ========================= */
int turbidityValue = 0;
float temperature = 0;
float humidity = 0;
float phValue = 0;

void setup() {
  Serial.begin(9600);
  phSerial.begin(9600);
  dht.begin();

  Serial.println("Water Quality Monitoring System Started...");
}

void loop() {

  /* -------- Turbidity -------- */
  turbidityValue = analogRead(TURBIDITY_PIN);

  /* -------- DHT11 -------- */
  temperature = dht.readTemperature();
  humidity    = dht.readHumidity();

  // Check if DHT failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT Sensor Error!");
    temperature = 0;
    humidity = 0;
  }

  /* -------- pH Sensor -------- */
  if (phSerial.available()) {
    String data = phSerial.readStringUntil('\n');
    data.trim(); // remove unwanted characters
    phValue = data.toFloat();
  }

  /* -------- Serial Output -------- */
  Serial.println("\n===== Water Quality =====");

  Serial.print("Turbidity: ");
  Serial.print(turbidityValue);
  Serial.println(" NTU");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("pH Value: ");
  Serial.println(phValue);

  Serial.println("=========================");

  delay(2000);
}
