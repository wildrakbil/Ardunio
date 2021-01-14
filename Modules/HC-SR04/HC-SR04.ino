//#include <ESP8266WiFi.h>

int TRIGGER = 3;
int ECHO = 2;
long tiempo;
float dist;
void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);

}
void loop() {

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  tiempo = pulseIn(ECHO, HIGH);
  dist = float (tiempo / 2) / 29.1;
  Serial.print("Distancia: ");
  Serial.println(dist);

  delay(1000);  //1s


}
