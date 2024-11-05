#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(7, 8, 9,10,11,12);

const byte ROWS = 4;
const byte COLS = 4;
char keys [ROWS ] [ COLS ] = {
{'1', '2', '3', 'A'},
{'4','5','6','B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}

byte rowPins [ROWS] = {A3, A2, A1, A0};
byte colPins [COLS] = {2, 3, 4, 5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
Serial.begin(9600);
lcd.begin(16, 2);
lcd.print("Waiting for file ");

};
void loop() {
if (Serial.available() > 0) {
lcd.clear();

// Receive the text file from PC via Serial
String receivedText[3];
for (int j = 0; j < 3; j++) {
while (!Serial.available()) (}
receivedText[j] = Serial.readStringUntil('\n');

receivedText[j].replace("#Student name and surname", "Ramolatela Lebaea");
receivedText[j].replace("#student number", "221064591");
receivedText[j].replace("#goal", "to finish this degree with an average
of atleast 70%");

lcd.clear();
lcd.print("File received!");
delay(2000);
lcd.clear();
lcd.print("Press key A");
while (keypad. getkey() != 'A') {}
delay(1000);
lcd.clear();
lcd.print("Changing");
for(int k=0; k <= 2; k++){
lcd.print(".");
delay(500);

lcd.clear();
lcd.print("Change complete!");
delay(2000);
lcd.clear();
lcd.print("Press key B");
// Wait for key B to be pressed on the keypad
while (keypad. getkey() != 'B') {
// Do nothing, wait for key B to be pressed

// Send the modified text file back to PC via Serial
for (int j = 0; j < 3; j++) {
Serial.println(receivedText[j]);

lcd.clear();
lcd.print("File sent!");
delay(2000);

// End the loop to prevent repeating the communication stages
//while (true) {lcd.clear(); 
delay(500); 
lcd.print("Waiting for file"); 
} 
} 