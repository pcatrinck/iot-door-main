extern bool allowed;
extern bool faraday;

void display_loop()
{
  if (allowed) {
    LCD.setCursor(0, 0);
    LCD.write(byte(1));
    LCD.print(" ABERTO POR:");
    LCD.setCursor(0, 1);
    LCD.print(userName);

    if(userName == "Antonio Sant'Ana") {
      LCD.setCursor(3, 1);
      LCD.write(byte(5));
    }

    else if(userName == "Lais Decote     ") {
      LCD.setCursor(2, 1);
      LCD.write(byte(4));
      LCD.setCursor(10, 1);
      LCD.write(byte(3));
    }
    
    digitalWrite(OPEN_SIGNAL, HIGH);
    delay(3000);
    digitalWrite(OPEN_SIGNAL, LOW);

    preencherTelaPadrao();
    allowed = false;
  }

  if (faraday) {
    LCD.setCursor(0, 0);
    LCD.write(byte(1));
    LCD.print("Acesso liberado      ");
    LCD.setCursor(0, 1);
    LCD.print("por Faraday     ");
    LCD.write(byte(2));

    digitalWrite(OPEN_SIGNAL, HIGH);
    delay(3000);
    digitalWrite(OPEN_SIGNAL, LOW);

    preencherTelaPadrao();
    faraday = false;
  }
}

void preencherTelaPadrao() {
  LCD.setCursor(0, 0);
  LCD.print("SALA DO PET ");
  LCD.write(byte(2));
  LCD.setCursor(0, 1);
  LCD.write(byte(0));
  LCD.print(" INSIRA SUA TAG");
}