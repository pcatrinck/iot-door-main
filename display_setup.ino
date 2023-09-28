void display_setup()
{
  LCD.init();
  LCD.backlight();
  LCD.createChar(0, ClosedLock);
  LCD.createChar(1, OpenLock);
  LCD.createChar(2, Smile);
  LCD.createChar(3, e);
  LCD.createChar(4, i);
  LCD.createChar(5, o);
  LCD.setCursor(0, 0);
  LCD.setCursor(0, 0);
  LCD.print("SALA DO PET ");
  LCD.write(byte(2));
  LCD.setCursor(0, 1);
  LCD.write(byte(0));
  LCD.print(" INSIRA SUA TAG");
}