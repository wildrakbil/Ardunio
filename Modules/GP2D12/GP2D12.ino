int alto = 515, bajo = 199; //valores de tensión del sharp (9cm - 30cm)
int cm = 0;                //Para almacenar el valor obtenido en cm valor=0
int analogInput = A2;            //Entrada analógica del sensor.
int led = 6;
int value;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  value = analogRead(analogInput);
  Serial.print(value);
  Serial.print(" || ");
  if (value > alto || value < bajo) {
    Serial.println("OUT"); //fuera de rango
    digitalWrite(led, LOW);
  }
  else {
    cm = (6787 / (value - 3)) - 4;      //calculo
    Serial.print(cm);
    Serial.println(" cm");
    digitalWrite(led, HIGH);
    delay(600);
  }
}
