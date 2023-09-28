extern bool allowed;
extern String userName;

void rfid_loop()
{
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
    //********* check if this is still needed
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    // Compare UID with authorized cards
    String cardUID = printer.getUIDAsString(rfid.uid.uidByte, rfid.uid.size);
    Serial.println(cardUID);

    for (int i = 0; i < sizeof(authorizedCards) / sizeof(authorizedCards[0]); i++) {
      if (cardUID.equals(authorizedCards[i].cardUID)) {
        Serial.println("Card is authorized.");
        Serial.println("User: " + authorizedCards[i].userName);
        Serial.println("");
        allowed = true;
        userName = authorizedCards[i].userName;
        break;  // Exit the loop since we found a match
    }
      else {
        Serial.println("Denied access.");
        Serial.println("");
      }
  }

    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printer.printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

}
