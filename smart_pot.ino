/*
 * Smart Pot - Intelligent Plant Care System
 * 
 * This system automatically monitors and maintains optimal conditions for your plants
 * by tracking soil moisture, light levels, and temperature, then watering as needed
 * based on a personalized care schedule.
 * 
 * Hardware Components:
 * - Soil Moisture Sensor (Analog)
 * - Light Sensor (LDR - Analog)
 * - DHT11/DHT22 Temperature & Humidity Sensor
 * - Water Pump with Relay Module
 * - Arduino Uno/Nano or ESP32
 * 
 * Pin Configuration:
 * - A0: Soil Moisture Sensor
 * - A1: Light Sensor (LDR)
 * - D2: DHT Temperature Sensor
 * - D3: Water Pump Relay
 * - D4: Status LED (Optional)
 */

#include <DHT.h>

// Pin Definitions
#define SOIL_MOISTURE_PIN A0
#define LIGHT_SENSOR_PIN A1
#define DHT_PIN 2
#define PUMP_RELAY_PIN 3
#define STATUS_LED_PIN 4

// DHT Sensor Configuration
#define DHT_TYPE DHT11  // Change to DHT22 if using that sensor
DHT dht(DHT_PIN, DHT_TYPE);

// Plant Care Schedule Configuration
struct PlantCareConfig {
  int soilMoistureThreshold;     // Minimum moisture level (0-1023)
  int optimalLightMin;            // Minimum light level (0-1023)
  int optimalLightMax;            // Maximum light level (0-1023)
  float optimalTempMin;           // Minimum temperature (°C)
  float optimalTempMax;           // Maximum temperature (°C)
  unsigned long wateringDuration; // Duration to run pump (ms)
  unsigned long checkInterval;    // How often to check sensors (ms)
  unsigned long minWateringInterval; // Minimum time between waterings (ms)
};

// Default configuration for common houseplants
PlantCareConfig config = {
  300,              // Soil moisture threshold (lower = drier)
  200,              // Optimal light minimum
  700,              // Optimal light maximum
  18.0,             // Optimal temp minimum (°C)
  26.0,             // Optimal temp maximum (°C)
  2000,             // Watering duration (2 seconds)
  60000,            // Check interval (1 minute)
  3600000           // Min watering interval (1 hour)
};

// Global variables
unsigned long lastCheckTime = 0;
unsigned long lastWateringTime = 0;
int soilMoistureValue = 0;
int lightValue = 0;
float temperature = 0;
float humidity = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Smart Pot Initializing...");
  
  // Initialize pins
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(PUMP_RELAY_PIN, LOW);  // Ensure pump is off
  digitalWrite(STATUS_LED_PIN, LOW);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Blink LED to indicate successful initialization
  for (int i = 0; i < 3; i++) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(200);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(200);
  }
  
  Serial.println("Smart Pot Ready!");
  Serial.println("Monitoring: Soil Moisture | Light | Temperature");
  Serial.println("----------------------------------------------");
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check sensors at configured interval
  if (currentTime - lastCheckTime >= config.checkInterval) {
    lastCheckTime = currentTime;
    
    // Read all sensors
    readSensors();
    
    // Display sensor readings
    displayReadings();
    
    // Check plant conditions and take action
    checkPlantConditions();
    
    // Determine if watering is needed
    if (needsWatering()) {
      waterPlant();
    }
  }
}

void readSensors() {
  // Read soil moisture (0 = wet, 1023 = dry)
  soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  
  // Read light level (0 = dark, 1023 = bright)
  lightValue = analogRead(LIGHT_SENSOR_PIN);
  
  // Read temperature and humidity
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  
  // Handle sensor errors
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Warning: Failed to read from DHT sensor!");
    temperature = 0;
    humidity = 0;
  }
}

void displayReadings() {
  Serial.println("\n=== Sensor Readings ===");
  
  // Soil Moisture
  int moisturePercent = map(soilMoistureValue, 1023, 0, 0, 100);
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.print("% (");
  Serial.print(soilMoistureValue);
  Serial.println(")");
  
  // Light Level
  int lightPercent = map(lightValue, 0, 1023, 0, 100);
  Serial.print("Light Level: ");
  Serial.print(lightPercent);
  Serial.print("% (");
  Serial.print(lightValue);
  Serial.println(")");
  
  // Temperature
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  // Humidity
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  
  Serial.println("=====================");
}

void checkPlantConditions() {
  bool needsAttention = false;
  
  // Check if moisture is too low
  if (soilMoistureValue > config.soilMoistureThreshold) {
    Serial.println("⚠️  Alert: Soil is too dry!");
    needsAttention = true;
  }
  
  // Check if light is outside optimal range
  if (lightValue < config.optimalLightMin) {
    Serial.println("⚠️  Alert: Light level is too low!");
    needsAttention = true;
  } else if (lightValue > config.optimalLightMax) {
    Serial.println("⚠️  Alert: Light level is too high!");
    needsAttention = true;
  }
  
  // Check if temperature is outside optimal range
  if (temperature > 0) {  // Valid reading
    if (temperature < config.optimalTempMin) {
      Serial.println("⚠️  Alert: Temperature is too low!");
      needsAttention = true;
    } else if (temperature > config.optimalTempMax) {
      Serial.println("⚠️  Alert: Temperature is too high!");
      needsAttention = true;
    }
  }
  
  // Blink LED if plant needs attention
  if (needsAttention) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(100);
    digitalWrite(STATUS_LED_PIN, LOW);
  }
}

bool needsWatering() {
  unsigned long currentTime = millis();
  
  // Check if soil is dry
  if (soilMoistureValue <= config.soilMoistureThreshold) {
    return false;  // Soil is moist enough
  }
  
  // Check if enough time has passed since last watering
  if (currentTime - lastWateringTime < config.minWateringInterval) {
    Serial.println("Info: Watering cooldown active");
    return false;
  }
  
  return true;
}

void waterPlant() {
  Serial.println("\n💧 Starting automatic watering...");
  
  // Turn on status LED
  digitalWrite(STATUS_LED_PIN, HIGH);
  
  // Activate water pump
  digitalWrite(PUMP_RELAY_PIN, HIGH);
  
  // Water for configured duration
  delay(config.wateringDuration);
  
  // Turn off pump
  digitalWrite(PUMP_RELAY_PIN, LOW);
  
  // Turn off LED
  digitalWrite(STATUS_LED_PIN, LOW);
  
  // Update last watering time
  lastWateringTime = millis();
  
  Serial.println("💧 Watering complete!");
  Serial.print("Next watering available in: ");
  Serial.print(config.minWateringInterval / 60000);
  Serial.println(" minutes");
}

// Function to update plant care configuration via Serial
void updateConfig() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    if (command.startsWith("MOISTURE:")) {
      config.soilMoistureThreshold = command.substring(9).toInt();
      Serial.println("Updated moisture threshold");
    }
    else if (command.startsWith("LIGHT_MIN:")) {
      config.optimalLightMin = command.substring(10).toInt();
      Serial.println("Updated minimum light level");
    }
    else if (command.startsWith("LIGHT_MAX:")) {
      config.optimalLightMax = command.substring(10).toInt();
      Serial.println("Updated maximum light level");
    }
    else if (command.startsWith("TEMP_MIN:")) {
      config.optimalTempMin = command.substring(9).toFloat();
      Serial.println("Updated minimum temperature");
    }
    else if (command.startsWith("TEMP_MAX:")) {
      config.optimalTempMax = command.substring(9).toFloat();
      Serial.println("Updated maximum temperature");
    }
    else if (command == "STATUS") {
      displayConfig();
    }
  }
}

void displayConfig() {
  Serial.println("\n=== Current Configuration ===");
  Serial.print("Moisture Threshold: ");
  Serial.println(config.soilMoistureThreshold);
  Serial.print("Light Range: ");
  Serial.print(config.optimalLightMin);
  Serial.print(" - ");
  Serial.println(config.optimalLightMax);
  Serial.print("Temperature Range: ");
  Serial.print(config.optimalTempMin);
  Serial.print(" - ");
  Serial.print(config.optimalTempMax);
  Serial.println(" °C");
  Serial.println("===========================");
}
