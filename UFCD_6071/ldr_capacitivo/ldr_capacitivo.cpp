#include <Arduino.h>
const int pinoLDR = A0;       // LDR
const int pinoTouch = 2;      // Sensor metálico

void setup() {
  Serial.begin(9600);
  pinMode(pinoTouch, INPUT);
}

void loop() {
  // Leitura LDR
  int valLDR = analogRead(pinoLDR);
  float tensao = valLDR * 5.0 / 1023.0;

  // Leitura sensor metálico
  int toque = digitalRead(pinoTouch);

  // Mostrar no Serial
  Serial.print("LDR: ");
  Serial.print(valLDR);
  Serial.print(" → ");
  Serial.print(tensao, 2);
  Serial.print(" V");
  
  Serial.print("  |  Toque: ");
  Serial.println(toque == HIGH ? "TOCADO" : "NÃO TOCADO");

  delay(500);
}
