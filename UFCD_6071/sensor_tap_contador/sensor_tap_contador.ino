#include <Arduino.h>
//sensor tap TTP223
//contar a vezes que o sensor é activo


int pin = 7; // OUT do TTP223 ligado ao pino 2 do Arduino
int tapStatus;
int contador = 0; // Inicializa o contador e soma 1 a cada toque


void setup() {
  pinMode(pin, INPUT); // Não use INPUT_PULLUP para TTP223
  Serial.begin(9600);
}

void loop() {
  tapStatus = digitalRead( pin);
  if (tapStatus) { // HIGH quando tocado
    contador++; // Incrementa o contador
    Serial.print("Contador: ");
    Serial.println(contador); // Imprime o contador
    Serial.println("Sensor Ativado!");
  }
  
}