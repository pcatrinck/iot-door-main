#include <SPI.h>
#include <MFRC522.h>

CardInfo authorizedCards[] = {
    {"9ba84e43", "Paquetá Mineiro"},
    {"e5309085", "Ger Mancano"}
};

#define SS_PIN D8
#define RST_PIN D0

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];

void setup() {
  Serial.begin(115200);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  Serial.println();
  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println();
  Serial.println(F("This code scan the MIFARE Classic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}

void loop() {

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  // Store the type of the RFID card
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Check if the card is a valid type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Invalid card."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] ||
      rfid.uid.uidByte[1] != nuidPICC[1] ||
      rfid.uid.uidByte[2] != nuidPICC[2] ||
      rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));
  }

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    // Compare UID with authorized cards
    String cardUID = getUIDAsString(rfid.uid.uidByte, rfid.uid.size);
    Serial.println(cardUID);

    for (int i = 0; i < sizeof(authorizedCards) / sizeof(authorizedCards[0]); i++) {
      if (cardUID.equals(authorizedCards[i].cardUID)) {
        Serial.println("Card is authorized.");
        Serial.println("User: " + authorizedCards[i].userName);
        break;  // Exit the loop since we found a match
    }
      else {
        Serial.println("Denied access.");
      }
  }

    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


//  Print hex to serial
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");  //format output, puts a 0 if it is a single digit hex number
    Serial.print(buffer[i], HEX);
  }
}

//  Print decimal to serial
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");  //format output, puts a 0 if it is a single digit dec number
    Serial.print(buffer[i], DEC);
  }
}

// Format a string corresponding to card's uid.
String getUIDAsString(byte *uidBytes, byte uidSize) {
  String uidStr = "";
  for (byte i = 0; i < uidSize; i++) {
    if (uidBytes[i] < 0x10) {
      uidStr += "0";
    }
    uidStr += String(uidBytes[i], HEX);
  }
  return uidStr;
}
