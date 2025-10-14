#include <Arduino.h>
//sensor tap TTP223
//contar as vezes que o sensor é ativo
//a cada 20 toques acende um led por 5 segundos (usando millis)

int pin = 7; // OUT do TTP223 ligado ao pino 7 do Arduino
int led = 8; // LED ligado ao pino 8 do Arduino
int tapStatus;
int ultimoStatus = LOW;
unsigned long contador = 0;
unsigned long ledStartTime = 0;
bool ledAceso = false;

void setup() {
  pinMode(pin, INPUT); // Não use INPUT_PULLUP para TTP223
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  tapStatus = digitalRead(pin);

  // Detecta transição de LOW para HIGH (toque)
  if (tapStatus == HIGH && ultimoStatus == LOW) {
    contador++;
    Serial.print("Contador: ");
    Serial.println(contador);
    Serial.println("Sensor Ativado!");

    // A cada 50 toques, acende o LED por 5 segundos
    if (contador % 20 == 0) {
      digitalWrite(led, HIGH);
      ledAceso = true;
      ledStartTime = millis();
    }
  }
  ultimoStatus = tapStatus;

  // Desliga o LED após 5 segundos
  if (ledAceso && (millis() - ledStartTime >= 5000)) {
        digitalWrite(led, LOW);
        ledAceso = false;
      }
    }
    