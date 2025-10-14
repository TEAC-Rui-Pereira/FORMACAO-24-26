#include <Arduino.h>
const int pinoLDR = A0;
const int pinoToque = 2;
const int led1 = 8;
const int led2 = 9;

// Define o limite de tensão abaixo do qual consideramos "escuro"
const float limiteTensaoEscuro = 1.0; // por exemplo, < 1V = escuro

void setup() {
  pinMode(pinoLDR, INPUT);
  pinMode(pinoToque, INPUT_PULLUP); // Ativa pull-up interno
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int valLDR = analogRead(pinoLDR);
  float tensaoLDR = valLDR * 5.0 / 1023.0;
  int toque = digitalRead(pinoToque);

  Serial.print("Tensão LDR: ");
  Serial.print(tensaoLDR);
  Serial.print(" V  | Toque: ");
  Serial.println(toque == LOW ? "Sim" : "Não");

  // Estado 3: escuro e toque
  if (tensaoLDR < limiteTensaoEscuro && toque == LOW) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  // Estado 1: apenas escuro
  else if (tensaoLDR < limiteTensaoEscuro) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  // Estado 2: apenas toque
  else if (toque == LOW) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
  // Nenhuma condição
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }

  delay(1000);
}