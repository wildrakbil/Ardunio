#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//HC-SR04 pins
int trig = 3;
int echo = 4;
long tiempo;
float dist;
//LED's pins
int ledfull = 5;
int ledempty = 6;
int ledrun = 7;
//Niveles del tanque
float lleno = 11;
float medio = 16;
float vacio = 19;
//Bomba
int bomba_auto = 13;
int bomba_manual = 12;
//vanderas
boolean start = false;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  lcd.backlight();
  lcd.init();
  pinMode(ledfull, OUTPUT);
  pinMode(ledempty, OUTPUT);
  pinMode(ledrun, OUTPUT);
  pinMode(bomba_manual, OUTPUT);
  pinMode(bomba_auto, OUTPUT);
  digitalWrite(bomba_manual, HIGH);
}

void loop() {
  // Nivel tanque de reserva
  digitalWrite(trig, 0);//Iniciamos en LOW el trig
  delayMicroseconds(1000);
  digitalWrite(trig, HIGH);//Iniciamos el trig
  tiempo = pulseIn(echo, HIGH);//lo que tarda en ir regresar la ondateniendo
  dist = float (0.0340 * tiempo ) / 2;
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Estado:");
  lcd.setCursor(0, 1);
  lcd.print("Nivel:");
  lcd.print(dist);
  Serial.println(dist);
  
  if (dist <= lleno) {
    start = false;
  } else if (dist >= vacio) {
    start = true;
  }
  if (start) {
    lcd.setCursor(8, 0);
    lcd.print("Llenar");
    digitalWrite(ledfull, LOW);
    digitalWrite(ledempty, HIGH);
    digitalWrite(ledrun, LOW);
    digitalWrite(bomba_auto, LOW);
  } else {
    lcd.setCursor(8, 0);
    lcd.print("Va|  !   c++ciar");
    digitalWrite(ledfull, HIGH);
    digitalWrite(ledempty, LOW);
    digitalWrite(ledrun, LOW);
    digitalWrite(bomba_auto, HIGH);
  }
}
