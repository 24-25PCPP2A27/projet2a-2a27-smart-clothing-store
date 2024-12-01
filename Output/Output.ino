#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD: Set your I2C address (common ones are 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.init(); // Initialize the LCD
    lcd.backlight(); // Turn on the backlight
    lcd.setCursor(0, 0);
    lcd.print("Waiting for ID"); // Initial message
    Serial.begin(9600); // Initialize Serial communication
}

void loop() {
    if (Serial.available() > 0) {
        String receivedData = Serial.readStringUntil('\n'); // Read the incoming data

        if (receivedData.startsWith("ERROR")) {
            // Display error message
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Error: ID not");
            lcd.setCursor(0, 1);
            lcd.print("found");
        } else if (receivedData.startsWith("QUANTITY")) {
            // Display the quantity
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Quantity:");
            lcd.setCursor(0, 1);
            lcd.print(receivedData.substring(9)); // Extract quantity value
        } else {
            // Unexpected data handling
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Invalid Input");
        }
    }
}