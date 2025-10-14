#include <Arduino.h>
//sensor tap TTP223
//contar a vezes que o sensor é activo


int pin = 7; // OUT do TTP223 ligado ao pino 2 do Arduino
int tapStatus;


void setup() {
  pinMode(pin, INPUT); // Não use INPUT_PULLUP para TTP223
  Serial.begin(9600);
}

void loop() {
  tapStatus = digitalRead(pin);
  if (tapStatus) { // HIGH quando tocado
    Serial.println("Sensor Ativado!");
  }
  
}