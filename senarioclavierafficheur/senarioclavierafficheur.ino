#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Keypad configuration
const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {10, 11, 7, 6}; 
byte colPins[COLS] = {5, 4, 3}; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Global variables
String code = "";

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter ID:");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '*') {
      code = "";  // Clear the code
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter ID:");
    } else if (key == '#') {
      if (code.length() > 0) {
        Serial.println(code); // Send the ID to Qt
        code = ""; // Clear code after sending
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("ID Sent!");
      }
    } else {
      code += key; // Append key to code
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ID: ");
      lcd.print(code); // Display code in real-time
    }
  }

  // Check for messages from Qt
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    lcd.clear();
    if (message.length() <= 16) {
        lcd.setCursor(0, 0);
        lcd.print(message);
    } else {
        lcd.setCursor(0, 0);
        lcd.print(message.substring(0, 16));
        lcd.setCursor(0, 1);
        lcd.print(message.substring(16));
    }
}
}
