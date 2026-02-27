// ==================================================
//       SMART HOME MANAGER SYSTEM – FINAL VERSION
// ==================================================

// --- LED PINS ---
const int fanLED        = A2;    // Green
const int lightLED      = 3;     // Yellow
const int acLED         = 4;     // Blue
const int fridgeLED     = 5;     // White
const int alarmLED      = 6;     // Red

// --- BUTTON PINS ---
const int fanButton     = 8;
const int lightButton   = 9;
const int fridgeButton  = 10;

// --- TEMPERATURE SENSOR ---
const int tempSensor = A0;
const float tempThreshold = 30.0;  // AC turns ON at 30°C or higher

void setup() {
  // Initialize all LEDs as OUTPUT
  pinMode(fanLED, OUTPUT);
  pinMode(lightLED, OUTPUT);
  pinMode(acLED, OUTPUT);
  pinMode(fridgeLED, OUTPUT);
  pinMode(alarmLED, OUTPUT);

  // Initialize buttons with internal pull-up resistors
  pinMode(fanButton, INPUT_PULLUP);
  pinMode(lightButton, INPUT_PULLUP);
  pinMode(fridgeButton, INPUT_PULLUP);

  // Start serial communication
  Serial.begin(9600);
  Serial.println("✅ Smart Home Manager – Ready!");
}

void loop() {
  // === READ & CONVERT TEMPERATURE (TMP36) ===
  int sensorValue = analogRead(tempSensor);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;  // TMP36 formula: (V - 0.5V) * 100

  // === SERIAL MONITOR DEBUG OUTPUT ===
  Serial.print("🌡️ Temp: ");
  Serial.print(temperatureC);
  Serial.print("°C | ");

  Serial.print("Fan: ");
  Serial.print(digitalRead(fanButton));
  Serial.print(" | Light: ");
  Serial.print(digitalRead(lightButton));
  Serial.print(" | Fridge: ");
  Serial.println(digitalRead(fridgeButton));

  // === AC: AUTOMATIC CONTROL (NO BUTTON) ===
  if (temperatureC >= tempThreshold) {
    digitalWrite(acLED, HIGH);   // Turn ON if hot
  } else {
    digitalWrite(acLED, LOW);    // Turn OFF if cool
  }

  // === FAN: MANUAL MOMENTARY CONTROL ===
  if (digitalRead(fanButton) == LOW) {
    digitalWrite(fanLED, HIGH);
  } else {
    digitalWrite(fanLED, LOW);
  }

  // === LIGHT: MANUAL MOMENTARY CONTROL ===
  if (digitalRead(lightButton) == LOW) {
    digitalWrite(lightLED, HIGH);
  } else {
    digitalWrite(lightLED, LOW);
  }

  // === FRIDGE: MANUAL MOMENTARY CONTROL ===
  if (digitalRead(fridgeButton) == LOW) {
    digitalWrite(fridgeLED, HIGH);
  } else {
    digitalWrite(fridgeLED, LOW);
  }

  // === ALARM: RESERVED (OFF FOR NOW) ===
  digitalWrite(alarmLED, LOW);

  // Small delay for smooth response
  delay(100);
}