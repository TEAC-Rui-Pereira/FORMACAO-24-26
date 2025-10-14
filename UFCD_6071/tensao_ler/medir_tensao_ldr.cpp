//RPP
#include <Arduino.h>
const int pinoLDR = A0;  // Pino analógico onde está ligado o sensor

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
}

void loop() {
  int valorAnalogico = analogRead(pinoLDR); // Lê o valor analógico (0 a 1023)

  // Converte para tensão (0 a 5V)
  float tensao = (valorAnalogico * 5.0) / 1023.0;

  // Mostra o valor no monitor serial
  Serial.print("Valor analógico: ");
  Serial.print(valorAnalogico);
  Serial.print("  |  Tensão: ");
  Serial.print(tensao);
  Serial.println(" V");

  delay(500); // Espera 0,5 segundo
}
