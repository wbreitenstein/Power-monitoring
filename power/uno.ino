#include <Arduino.h>

// Pin connections
const int currentSensorPinA = A0; // Pin for current sensor A
const int currentSensorPinB = A1; // Pin for current sensor B
const int voltageSensorPin = A2; // Pin for voltage sensor

// Variables for calculations
float powerA = 0.0; // Power for phase A
float powerB = 0.0; // Power for phase B
float energyA = 0.0; // Energy for phase A
float energyB = 0.0; // Energy for phase B
float voltage = 0.0; // Voltage
unsigned long lastUpdateMillis = 0; // Timer for regular updates

void setup() {
  Serial.begin(115200); // Begin serial communication
  Serial.println("Energy Monitoring System - Serial Output");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdateMillis >= 1000) {
    lastUpdateMillis = currentMillis;
    updateMetrics();
    String jsonData = createJSONString();
    Serial.println(jsonData); // Print JSON data to serial port
  }
}

String createJSONString() {
  String data = "{";
  data += "\"powerA\":" + String(powerA) + ",";
  data += "\"powerB\":" + String(powerB) + ",";
  data += "\"energyA\":" + String(energyA) + ",";
  data += "\"energyB\":" + String(energyB) + ",";
  data += "\"voltage\":" + String(voltage);
  data += "}";
  return data;
}

void updateMetrics() {
  // Read current values from sensors
  int currentValueA = analogRead(currentSensorPinA);
  int currentValueB = analogRead(currentSensorPinB);
  int voltageValue = analogRead(voltageSensorPin);

  // Convert current values to amps
  float currentA = convertCurrent(currentValueA);
  float currentB = convertCurrent(currentValueB);

  // Convert voltage value to volts
  voltage = convertVoltage(voltageValue);

  // Calculate power
  powerA = voltage * currentA;
  powerB = voltage * currentB;

  // Calculate energy (assuming updates every second)
  energyA += powerA / 3600.0;
  energyB += powerB / 3600.0;
}

float convertCurrent(int value) {
  // Replace with your current conversion formula
  return (value * 0.1) / 1000.0; // Example conversion
}

float convertVoltage(int value) {
  // Replace with your voltage conversion formula
  return (value * 0.1) * 11.0; // Example conversion for voltage divider
}

// Note: Frequency calculation is removed for this serial output version.
// If you need frequency, the intermediary application can potentially analyze the voltage waveform if provided.