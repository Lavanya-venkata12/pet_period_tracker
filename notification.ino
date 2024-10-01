#define BLYNK_TEMPLATE_ID "TMPL3zfYE1lEz"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "4bGW4uAWxw2V0A4RNU5R5D6-yrm6FgFU"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_ADXL345_U.h>

char ssid[] = "iQOO";
char password[] = "kalyani1234";

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

BlynkTimer timer;

void sendsensordata() {

  float ambientTemp = mlx.readAmbientTempC();
  float objectTemp = mlx.readObjectTempC();
  
  if (isnan(ambientTemp) || isnan(objectTemp)) {
    Serial.println("Failed to read temperature data");
    return;
  }

  Blynk.virtualWrite(V2, ambientTemp);
  Blynk.virtualWrite(V3, objectTemp);

  if (objectTemp > 39) {
    Blynk.logEvent("pet_alert","Pet got a fever");
  }
}

void setup() {
  Serial.begin(115200);
  
  // Initialize Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  
  // Initialize sensors
  if (!mlx.begin()) {
    Serial.println("Failed to initialize MLX90614!");
    while (1);
  }

  if (!accel.begin()) {
    Serial.println("Failed to initialize ADXL345!");
    while (1);
  }

  // Set timer for sensor data
  timer.setInterval(1000, sendsensordata);
}

void loop() {
  Blynk.run();
  timer.run();
}
