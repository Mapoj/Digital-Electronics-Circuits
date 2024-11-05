#include "SevSeg.h" SevSeg seg;

const int reset_PB = 12; const int start_Stop_PB = 14;

bool isCounting = false; unsigned long timer = 0; unsigned long seconds = 0; unsigned long minutes = 0;

const unsigned long debounceDelay = 50;

unsigned long lastResetButtonPressTime = 0; unsigned long lastStartStopButtonPressTime = 0;

void setup() {
byte numDigits = 3;
byte digitPins[] = {22, 21, 0};
byte segmentPins[] = {23, 19, 18, 5, 17, 16, 4, 15};
bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
byte hardwareConfig = COMMON_CATHODE; // See README.md for options bool updateWithDelays = false; // Default 'false' is Recommended
bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected

seg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
seg.setBrightness(90);

pinMode(reset_PB, INPUT_PULLUP); // Set RESET button pin as input with pull- up resistor
pinMode(start_Stop_PB, INPUT_PULLUP); // Set START/STOP button pin as input with pull-up resistor
}

void loop() {
// Check if the RESET button is pressed with debounce unsigned long currentMillis = millis();
if (currentMillis - lastResetButtonPressTime >= debounceDelay) { if (digitalRead(reset_PB) == LOW) {
// Reset the timer and start counting from 0
minutes = 0;
seconds = 0; isCounting = true; timer = millis();
}
lastResetButtonPressTime = currentMillis;
}
// Check if the START/STOP button is pressed with debounce
if (currentMillis - lastStartStopButtonPressTime >= debounceDelay) { if (digitalRead(start_Stop_PB) == LOW) {
// Toggle the timer's state isCounting = !isCounting;

// If starting the timer, record the current time if (isCounting) {
timer = millis();
}
}
lastStartStopButtonPressTime = currentMillis;
}
if (isCounting) {
// Calculate and update the timer when counting unsigned long currentTime = millis();
if (currentTime - timer >= 1000) { timer += 1000;
seconds++;

if (seconds == 60) { seconds = 0; minutes++;
}
if (minutes == 10) { // Reset the timer after 9 minutes and 59 seconds minutes = 0;
seconds = 0;
}
int timeValue = minutes * 100 + seconds; seg.setNumber(timeValue, 2);
}
} else {
// Display the last recorded time when not counting int timeValue = minutes * 100 + seconds; seg.setNumber(timeValue, 2);
}
seg.refreshDisplay(); // Must run repeatedly
}
