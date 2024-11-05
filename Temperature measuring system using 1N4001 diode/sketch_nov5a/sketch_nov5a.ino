#include <EEPROM.h> #include <LiquidCrystal.h>

const int ANALOG_PIN = A0; const int BUTTON_PIN = 2; const int EEPROM_SIZE = 1024;
const int NUM_TEMPERATURE_VALUES = 15;
const unsigned long MEASUREMENT_INTERVAL = 60000; // 1 minute in milliseconds

LiquidCrystal lcd(9,8,7,6,5,4);//rs/en/d4/d5/d6/d7

float temperatureValues[NUM_TEMPERATURE_VALUES]; int currentIndex = 0;

void setup() { Serial.begin(9600); lcd.begin(16, 2);
pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
static unsigned long lastMeasurementTime = 0; static unsigned long lastButtonPressTime = 0; unsigned long currentTime = millis();

// Read temperature
if (currentTime - lastMeasurementTime >= MEASUREMENT_INTERVAL) { float temperature = readTemperature(); saveTemperature(temperature); displayTemperature(temperature);
lastMeasurementTime = currentTime;
}

// Read button press and display last 15 temperatures if (digitalRead(BUTTON_PIN) == LOW) {
displayLastTemperatures();
//lastButtonPressTime = currentTime;
}
}

float readTemperature() {
int analogValue = analogRead(ANALOG_PIN);
// Calculate temperature using the diode equation (customize coefficients as needed)
float temperature = analogValue * 0.1; // Adjust the coefficient as per your diode characteristics
return temperature;
}

void saveTemperature(float temperature) { EEPROM.put(currentIndex * sizeof(float), temperature); currentIndex = (currentIndex + 1) % NUM_TEMPERATURE_VALUES;
}

void displayTemperature(float temperature) { lcd.clear();
lcd.setCursor(0, 0); lcd.print("Temp: ");
lcd.print(roundTemperature(temperature)); lcd.print(" C");
lcd.setCursor(0, 1); lcd.print("Time: ");
lcd.print(millis() / 60000); // Convert milliseconds to minutes lcd.print(" min");
}

int roundTemperature(float temperature) {
return static_cast<int>(temperature + 0.5); // Round to nearest integer
}

void displayLastTemperatures() { lcd.clear();
//lcd.home();
lcd.print("Last 15 Temps: ");
//lcd.setCursor(0, 1);
for (int i = 0; i < NUM_TEMPERATURE_VALUES; i++) {

float temperature;
EEPROM.get(i * sizeof(float), temperature); lcd.print(roundTemperature(temperature)); lcd.print(" ");
}
delay(3000); // Display for 3 seconds
}
