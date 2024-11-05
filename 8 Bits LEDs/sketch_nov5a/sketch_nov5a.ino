// Constants for LED pins
const int ledPins[] = {23, 25, 27, 29, 31, 33, 35, 37};
const int greenLEDPins[] = {52, 53, 51};
const int yellowLEDPins[] = {49, 47};
const int redLEDPins[] = {45, 43, 41}; const int dimmerLEDPin = 3;

// Potentiometer input pin const int potPin = A0;

void setup() { Serial.begin(9600);
// Set LED pins as OUTPUT for (int i = 0; i < 8; i++) {
pinMode(ledPins[i], OUTPUT);
}
for (int i = 0; i < 3; i++) { pinMode(greenLEDPins[i], OUTPUT);
}
for (int i = 0; i < 2; i++) { pinMode(yellowLEDPins[i], OUTPUT);
}
for (int i = 0; i < 3; i++) { pinMode(redLEDPins[i], OUTPUT);
}
pinMode(dimmerLEDPin, OUTPUT);
}

void loop() {
// Read analog voltage from potentiometer int potValue = analogRead(potPin);

int BinValue = map(potValue, 0, 1023, 0, 255); Serial.println(BinValue);
// Display binary value on LED array for (int i = 0; i < 8; i++) {
digitalWrite(ledPins[i], bitRead(BinValue, i));
}

// Display level on indicator LEDs if (potValue <= 341) {
// Lower levels
for (int i = 0; i < 3; i++) { digitalWrite(greenLEDPins[i], HIGH); digitalWrite(redLEDPins[i], LOW);
}
for (int i = 0; i < 2; i++) { digitalWrite(yellowLEDPins[i], LOW);
}
} else if (potValue <= 682) {
// Middle levels
for (int i = 0; i < 3; i++) { digitalWrite(greenLEDPins[i], HIGH); digitalWrite(redLEDPins[i], LOW);
}
for (int i = 0; i < 2; i++) { digitalWrite(yellowLEDPins[i], HIGH);
}
} else {
// Upper levels
for (int i = 0; i < 3; i++) { digitalWrite(greenLEDPins[i], HIGH); digitalWrite(redLEDPins[i], HIGH);
}
for (int i = 0; i < 2; i++) { digitalWrite(yellowLEDPins[i], HIGH);
}
}

// Generate PWM signal for light dimmer
// int pwmValue = map(potValue, 0, 1023, 0, 255); analogWrite(dimmerLEDPin,potValue/4);
}
