// === Libraries ===
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_SSD1306.h>

// === Objects ===
Adafruit_INA219 ina219;
Adafruit_SSD1306 display(128, 64, &Wire);

// === Pins ===
#define HALL_PIN      2     // RPM Sensor
#define LOAD_CELL_DT  3     // HX711 DT
#define LOAD_CELL_SCK 4     // HX711 SCK
#define SPRING_PIN    A0    // Potentiometer for spring deflection

// === Libraries for other sensors ===
#include "HX711.h"
HX711 scale;

// === RPM Variables ===
volatile int rpmCount = 0;
unsigned long lastRPMTime = 0;
float rpm = 0;

void IRAM_ATTR rpmISR() {
  rpmCount++;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // === INA219 Setup ===
  ina219.begin();

  // === OLED Setup ===
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // === RPM Setup ===
  pinMode(HALL_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), rpmISR, FALLING);

  // === Load Cell Setup ===
  scale.begin(LOAD_CELL_DT, LOAD_CELL_SCK);
  scale.set_scale(); // Adjust with calibration factor
  scale.tare();
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);

  // === Read INA219 ===
  float voltage = ina219.getBusVoltage_V();
  float current = ina219.getCurrent_mA() / 1000.0;
  float power   = ina219.getPower_mW() / 1000.0;

  display.print("V:"); display.print(voltage, 1); display.print("V ");
  display.print("I:"); display.print(current, 2); display.println("A");
  display.print("P:"); display.print(power, 1); display.println("W");

  // === RPM Calculation ===
  unsigned long currentTime = millis();
  if (currentTime - lastRPMTime >= 1000) {
    rpm = rpmCount * 60.0; // assuming 1 pulse/rev
    rpmCount = 0;
    lastRPMTime = currentTime;
  }
  display.print("RPM:"); display.println(rpm);

  // === Load Cell ===
  float weight = scale.get_units();
  display.print("Wt:"); display.print(weight, 1); display.println("kg");

  // === Spring Deflection ===
  int rawDeflect = analogRead(SPRING_PIN);
  float deflection = map(rawDeflect, 0, 1023, 0, 50); // example range in mm
  display.print("Defl:"); display.print(deflection); display.println("mm");

  display.display();
  delay(500);
}
