int potPin = A0; // Potentiometer connected to analog pin A0
int pwmPin = 9; // PWM output pin

void setup() {
  pinMode(pwmPin, OUTPUT); // Set PWM pin as output
}

void loop() {
  int potValue = analogRead(potPin); // Read potentiometer value (0-1023)
  int pwmValue = map(potValue, 0, 1023, 0, 255); // Map to PWM range (0-255)
  analogWrite(pwmPin, pwmValue); // Output PWM signal
  delay(10); // Small delay for stability
}