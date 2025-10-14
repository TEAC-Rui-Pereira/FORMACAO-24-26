#include <Arduino.h>

//RPP_6025
unsigned long previous1 = 0; // Tempo do último piscar
unsigned long fastBlinkStart = 0; // Guarda quando começou a piscar rápido
const int buttonPin1 = 5; // Terminal 5 Arduino
const int ledPin1 = 13; // Terminal 13 Arduino

enum LEDState { OFF, ON }; // Estado do LED
LEDState state1 = OFF; // Começa desligado
bool buttonPressed = false; // Indica estado do botão
bool blinkFast = false; // Indica se o LED está no modo rápido

unsigned long blinkInterval = 5000; // Pisca normalmente de 5 em 5 segundos
const unsigned long fastBlinkInterval = 500; // Pisca rápido de 0.5s em 0.5s
const unsigned long fastBlinkDuration = 5000; // Tempo do modo rápido (5 segundos)

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
}

void loop() {
  unsigned long currentMillis = millis();

  // Verifica se o botão foi pressionado
  if (digitalRead(buttonPin1) == LOW) {
    if (!buttonPressed) { 
      buttonPressed = true;
      blinkFast = true; // Ativar o modo rápido
      fastBlinkStart = currentMillis; // Guardar o tempo de início do modo rápido
      blinkInterval = fastBlinkInterval; // Mudar o tempo de piscar para rápido
    }
  } else {
    buttonPressed = false; // Permitir nova ativação do modo rápido
  }

  // Se estiver no modo rápido e passaram 5 segundos, volta ao modo normal
  if (blinkFast && (currentMillis - fastBlinkStart >= fastBlinkDuration)) {
    blinkFast = false;
    blinkInterval = 5000; // Volta ao piscar normal
  }

  // Controle do LED piscando
  if (currentMillis - previous1 >= blinkInterval) {
    previous1 = currentMillis; // Atualiza o tempo de referência
    state1 = (state1 == OFF) ? ON : OFF; // Alternar estado do LED
    digitalWrite(ledPin1, (state1 == ON) ? HIGH : LOW);
  }
}
