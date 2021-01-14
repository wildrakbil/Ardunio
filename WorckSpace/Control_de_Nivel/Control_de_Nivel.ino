#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2) ;
int trig = 3;
int echo = 4;
int bombaauto=13;
int bombamanual=12;
int ledfull=5;
int ledempty=6;
int ledrun=7;
int alarma=A0;
int botonauto=8;
int botonmanual=9;
long tiempo;
float dist;
int encendido = 0;
int mililitro;

void setup() {
Serial.begin(9600);
lcd.backlight();
lcd.init();
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(bombamanual, OUTPUT);
pinMode(bombaauto, OUTPUT);
pinMode(ledfull, OUTPUT);
pinMode(ledempty, OUTPUT);
pinMode(ledrun, OUTPUT);
pinMode(botonauto, INPUT);
pinMode(botonmanual, INPUT);
pinMode(alarma,OUTPUT);
digitalWrite(bombamanual,HIGH);
digitalWrite(bombaauto,HIGH);
}

void loop() {

digitalWrite(trig, 0);//Iniciamos en LOW el trig
delayMicroseconds(5);//Esperamos 5 microsegundos antes de mandar la primera onda, asi evitamos que se combinen y erroneas lecturas.
digitalWrite(trig, HIGH);//Iniciamos el trig
tiempo= pulseIn(echo, HIGH);//Almacenamos en la variable tiempo, lo que tarda en ir regresar la ondateniendo asi el tiempo doble (ida y vuelta) se debe quitar la mitad
//Velocidad del Sonido es 349.2 m/s (a 30ºc al nivel del mar)->0.0349cm/microsegundo, Si V=d/t entonces d=(v*(t/2))
dist= float (0.0340*(tiempo/2));//Almacenamos el resultado de la operacion en la varible dist
mililitro= float (24.1-dist)*123.247;//Almacenamos en la variable mililitro el resultado de la resta de:(la distancia maxima que mide el sensor del deposito vacio) -(la distancia del sensor)*(los mililitros aprox que hay en un cm de altura) varia segun su contenedor
float distrue=24.1-dist;//Almacenamos en la variable distrue la dstancia maxima del deposito vacio menos la distancia, obteniendo asi la altura del liquido 
delay(600);//delay de 600 milisegundos(Cada 600 milisegundos mandara una onda ultrasonica para actualizar la dist)
lcd.clear(); 
lcd.setCursor(0,0);
lcd.print("Estado:");  
Serial.println(dist);


if(digitalRead(botonmanual) == HIGH){

if(dist<=11.8){ 
lcd.setCursor(8,0);
lcd.print("Lleno"); 
lcd.setCursor(0,1);
lcd.print("Manual DENEGADO");  
digitalWrite(ledfull, HIGH);
digitalWrite(ledrun, LOW);
digitalWrite(ledempty, LOW);
digitalWrite(bombamanual,HIGH);
analogWrite(alarma,255);}

if((dist<21.7)&&(dist>11.8)){
lcd.setCursor(8,0);
lcd.print("Llenando"); 
lcd.setCursor(0,1);
lcd.print("Manual ACTIVADO"); 
digitalWrite(ledfull, LOW);
digitalWrite(ledempty, LOW); 
digitalWrite(ledrun, HIGH);
digitalWrite(bombamanual,LOW);
analogWrite(alarma,LOW);}

if(dist>=21.7){
lcd.setCursor(8,0);
lcd.print("Bajo"); 
lcd.setCursor(0,1);
lcd.print("Manual ACTIVADO"); 
digitalWrite(ledfull, LOW); 
digitalWrite(ledrun, HIGH);
digitalWrite(bombamanual,LOW);
digitalWrite(ledempty, HIGH);
analogWrite(alarma,LOW);} 

}
else{
digitalWrite(bombamanual,HIGH);
analogWrite(alarma,LOW);

if(digitalRead(botonauto) == 1){
      encendido= !encendido;}
      
if(encendido==1){

if(dist<=11.8){ 
lcd.setCursor(8,0);
lcd.print("Lleno");
lcd.setCursor(0,1);
lcd.print(mililitro); 
lcd.setCursor(4,1);
lcd.print("ml");
lcd.setCursor(9,1);
lcd.print(distrue);
lcd.setCursor(14,1);
lcd.print("cm");
digitalWrite(ledfull, HIGH);
digitalWrite(ledempty, LOW);
digitalWrite(ledrun, LOW);
digitalWrite(bombaauto,HIGH);
}

if((dist<21.7)&&(dist>11.8)){
lcd.setCursor(8,0);
lcd.print("Llenando");
lcd.setCursor(0,1);
lcd.print(mililitro); 
lcd.setCursor(4,1);
lcd.print("ml");
lcd.setCursor(9,1);
lcd.print(distrue);
lcd.setCursor(14,1);
lcd.print("cm");
digitalWrite(bombaauto,LOW);
digitalWrite(ledfull, LOW);
digitalWrite(ledempty, LOW);
digitalWrite(ledrun, HIGH);}

if(dist>21.7){
lcd.setCursor(8,0);
lcd.print("Bajo");
lcd.setCursor(0,1);
lcd.print(mililitro); 
lcd.setCursor(4,1);
lcd.print("ml");
lcd.setCursor(9,1);
lcd.print(distrue);
lcd.setCursor(14,1);
lcd.print("cm");
digitalWrite(bombaauto,LOW);
digitalWrite(ledfull, LOW);
digitalWrite(ledempty, HIGH);
digitalWrite(ledrun, HIGH);}

if(dist>=23){
lcd.setCursor(8,0);
lcd.print("Vacio"); 
lcd.setCursor(0,1);
lcd.print(mililitro); 
lcd.setCursor(4,1);
lcd.print("ml");
lcd.setCursor(9,1);
lcd.print(distrue);
lcd.setCursor(14,1);
lcd.print("cm");
digitalWrite(bombaauto,LOW);
digitalWrite(ledfull, LOW);
digitalWrite(ledempty, HIGH);
digitalWrite(ledrun, HIGH);}
}

else {
lcd.setCursor(8,0);
lcd.print("Apagado");
lcd.setCursor(0,1);
lcd.print("CONTROL DE NIVEL");
digitalWrite(bombamanual,HIGH);
digitalWrite(bombaauto,HIGH);
digitalWrite(ledfull, LOW);
digitalWrite(ledempty, LOW);
digitalWrite(ledrun, LOW);
analogWrite(alarma,LOW);} 
 
} 

}
