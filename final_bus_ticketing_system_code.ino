#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pins
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 6

// Components
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

// Users data
#define NUM_USERS 6
struct User {
  byte uid[4];
  String name;
  float balance;
};

User users[NUM_USERS] = {

};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  myServo.attach(SERVO_PIN);
  myServo.write(0);
  randomSeed(analogRead(0));
  
  // Welcome sequence
  lcd.clear();
  lcd.print("Hello!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Welcome to Bus");
  delay(2000);
  lcd.clear();
  lcd.print("Please Tap Your");
  lcd.setCursor(0, 1);
  lcd.print("Card/Keychain");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    processRFID();
    delay(500); // Debounce
  }
}

void processRFID() {
  int userIndex = findUserIndex(mfrc522.uid.uidByte);
  
  if (userIndex != -1) {
    // Valid user - check balance first
    float fee = random(10, 51);
    
    if (users[userIndex].balance >= fee) {
      // Sufficient balance
      myServo.write(180); // Open gate
      users[userIndex].balance -= fee;

      // Display
      lcd.clear();
      lcd.print("Hello! "+users[userIndex].name);
      lcd.setCursor(0, 1);
      lcd.print("Paid:rs " + String(fee, 2));
      delay(1500);
      lcd.setCursor(0, 1);
      lcd.print(" Bal:rs " + String(users[userIndex].balance, 2));

      // Serial output
      Serial.print(users[userIndex].name + ",");       // Name
      Serial.print(String(fee, 2) + ",");             // Fee
      Serial.print(String(users[userIndex].balance, 2) + ","); // Balance
      printUID(mfrc522.uid.uidByte);                   // UID
      Serial.println(",ACCESS_GRANTED");     
      delay(1500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Thanks For using");
      delay(500);
      lcd.setCursor(0,1);
      lcd.print("Our Bus service");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enjoy your Ride!");

      delay(2000);
      myServo.write(0); // Close gate
    } else {
      // Insufficient balance
      lcd.clear();
      lcd.print("Not Enough Funds!");
      lcd.setCursor(0, 1);
      lcd.print("Bal:rs " + String(users[userIndex].balance, 2));
      
      Serial.print("Insufficient balance for ");
      printUID(mfrc522.uid.uidByte);
      Serial.println(" - " + users[userIndex].name);
      
      delay(2000);
    }
    showWelcomeMessage(); // Return to welcome
  } else {
    // Invalid
    lcd.clear();
    lcd.print("Invalid Card!");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");
    printUID(mfrc522.uid.uidByte);
    Serial.println(" - Invalid Card!");
    delay(1500);
    showWelcomeMessage();
  }
  mfrc522.PICC_HaltA();
}

// Helper functions
int findUserIndex(byte *uid) {
  for (int i = 0; i < NUM_USERS; i++) {
    if (memcmp(uid, users[i].uid, 4) == 0) return i;
  }
  return -1;
}

void printUID(byte *uid) {
  Serial.print("UID:");
  for (byte i = 0; i < 4; i++) {
    Serial.print(uid[i] < 0x10 ? " 0" : " ");
    Serial.print(uid[i], HEX);
  }
}

void showWelcomeMessage() {
  lcd.clear();
  lcd.print("Please Tap Your");
  lcd.setCursor(0, 1);
  lcd.print("Card/Keychain");
}