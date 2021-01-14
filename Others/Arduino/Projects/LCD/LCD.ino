#include  <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// Arduino pin numbers
const int SW_pin = 7; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setup()
{
  lcd.begin(16, 2);
  lcd.home();
  lcd.print("Hola Mundo");
  lcd.setCursor ( 0, 1 );
  lcd.print("GEEKFACTORY");
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(250000);
}

void loop()
{
  /*int i;
    for ( int i = 0; i < 5; i++ ) {
    lcd.scrollDisplayRight();
    //lcd.leftToRight();
    delay (1000);
    }
    for ( int i = 0; i < 5; i++ ) {
    lcd.scrollDisplayLeft();
    //lcd.rightToLeft();
    delay (1000);
    }*/
  lcd.setCursor ( 20, 0 );
  lcd.print("X-axis: ");
  lcd.print(analogRead(X_pin));
  lcd.setCursor ( 20, 1 );
  lcd.print("Y-axis: ");
  lcd.print(analogRead(Y_pin));
  
  if (analogRead(X_pin) < 300) {
    lcd.scrollDisplayRight();
    delay (500);
  }
  if (analogRead(X_pin) > 600) {
    lcd.scrollDisplayLeft();
    delay (500);
  }

}
