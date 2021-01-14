void printLCD(String above , String down) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(above);
  lcd.setCursor(0, 1);
  lcd.print(down);
}
