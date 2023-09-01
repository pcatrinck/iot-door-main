/*           MFRC522         ESP8266 
 *Signal       Pin             Pin 
 * ---------------------------------
 * RST/Reset   RST             D3 
 * SPI SS      SDA(SS)         D4 
 * SPI MOSI    MOSI            D7
 * SPI MISO    MISO            D6 
 * SPI SCK     SCK             D5 
 */

#include <SPI.h>
#include <MFRC522.h>
#include <printh.h>
#include "CardInfo.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

constexpr uint8_t RST_PIN = D3;
constexpr uint8_t SS_PIN  = D4;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];

// Create an instance of the prt_h class
prt_h printer;

// Create LCD object
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

// Personalized char for 16x2 display
byte ClosedLock[] = {B01110, B01010, B01010, B11111, B10001, B10101, B10001, B11111};
byte OpenLock[] = {B01111, B01000, B01000, B11111, B10001, B10101, B10001, B11111};
byte Smile[] = {B00000, B01010, B01010, B01010, B00000, B10001, B01110, B00000};

// Bool for door control
bool allowed = false;

void setup() {
  Serial.begin(9600);

  rfid_setup();

  //display_setup();
  LCD.init();
  LCD.backlight();
  LCD.createChar(0, ClosedLock);
  LCD.createChar(1, OpenLock);
  LCD.createChar(2, Smile);
  LCD.setCursor(0, 0);
  LCD.print("SALA DO PET ");
  LCD.write(byte(2));
  LCD.setCursor(0, 1);
  LCD.write(byte(0));
  LCD.print(" INSIRA SUA TAG");
}

void loop() {

  rfid_loop();

  //display_loop();
  if (allowed) {
    LCD.setCursor(0, 0);
    LCD.write(byte(1));
    LCD.print("ACESSO LIBERADO");
    LCD.setCursor(0, 1);
    LCD.print("PATRICK CATRINCK");
    delay(3000);

    // !!!!!!!!!!!!! fazer uma função pra preencher a tela padrão
    LCD.createChar(0, ClosedLock);
    LCD.createChar(1, OpenLock);
    LCD.createChar(2, Smile);
    LCD.setCursor(0, 0);
    LCD.print("SALA DO PET ");
    LCD.write(byte(2));
    LCD.setCursor(0, 1);
    LCD.write(byte(0));
    LCD.print(" INSIRA SUA TAG");
    allowed = false;
  }
}
