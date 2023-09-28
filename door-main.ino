#include <printh.h>
#include <string.h>



//********************  MFRC522 ***************************
#include <SPI.h>
#include <MFRC522.h>
#include "CardInfo.h"

constexpr uint8_t RST_PIN = 22;
constexpr uint8_t SS_PIN  = 21;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
byte nuidPICC[4];     // Init array that will store new NUID
prt_h printer;        // Create an instance of the prt_h class
//**********************************************************



//******************** LCD DISPLAY *************************
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2C_SDA 33
#define I2C_SCL 32

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);                      // Create LCD object

// Personalized char for 16x2 display
byte ClosedLock[] = {B01110, B01010, B01010, B11111, B10001, B10101, B10001, B11111};
byte OpenLock[] = {B01111, B01000, B01000, B11111, B10001, B10101, B10001, B11111};
byte Smile[] = {B00000, B01010, B01010, B01010, B00000, B10001, B01110, B00000};
byte e[] = {B00010,B00100,B01110,B10001,B11111,B10000,B01110,B00000};
byte i[] = {B00001,B00010,B01100,B00100,B00100,B00100,B01110,B00000};
byte o[] = {B00100,B01010,B01110,B10001,B10001,B10001,B01110,B00000};
//**********************************************************



//******************** wifi connection *********************
#include <WiFi.h>
 
const char* ssid = "*************";
const char* password = "*************";

WiFiServer server(80);
//**********************************************************



//********************* CODE ASSISTENCE **********************
int OPEN_SIGNAL = 32;
bool allowed = false;       // Bool for door control
bool faraday = false;       // Bool for door control
String  userName = "";      // String for user name
//************************************************************


void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);

  Serial.begin(9600);
  pinMode(32, OUTPUT);
  
  wifi_setup();
  rfid_setup();
  display_setup();
}

void loop() {
  Serial.println("IP adress: ");
  Serial.println(WiFi.localIP());
  wifi_loop();     //set faraday true
  rfid_loop();     //set allowed true
  display_loop();  //open door
}
