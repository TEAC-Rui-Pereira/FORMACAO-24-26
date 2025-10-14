#include <Arduino.h>
#include <LiquidCrystal.h>

// Define the pins for the ultrasonic sensor
#define TRIG_PIN 9
#define ECHO_PIN 10
// Define os pinos de conexão com o LCD
const int rs = 11;
const int en = 12;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

// Inicializa o objeto LiquidCrystal com os pinos definidos
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numLeituras = 5; // Número de leituras para calcular a média
int leituras[numLeituras]; // Array para armazenar as leituras
int soma = 0;              // Soma das leituras
int media = 0;             // Média das leituras
int indice = 0;            // Índice atual no array

unsigned long previousMillis = 0; // Armazena o último tempo em que a leitura foi feita
const long interval = 500;        // Intervalo entre leituras (em milissegundos)

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the trigger pin as output and the echo pin as input
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize the LCD
  lcd.begin(16, 2); // Configura o LCD com 16 colunas e 2 linhas
  lcd.print("Media Distancia:");
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time a reading was taken
    previousMillis = currentMillis;

    // Clear the trigger pin
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Set the trigger pin high for 10 microseconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the echo pin and calculate the distance
    int distancia = pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;

    // Store the reading in the array
    leituras[indice] = distancia;

    // Increment the index
    indice++;

    // Print the current reading
    Serial.print("Leitura ");
    Serial.print(indice);
    Serial.print(": ");
    Serial.print(distancia);
    Serial.println(" cm");

    // Check if all readings have been taken
    if (indice == numLeituras) {
      // Calculate the sum of the readings
      soma = 0;
      for (int i = 0; i < numLeituras; i++) {
        soma += leituras[i];
      }

      // Calculate the average
      media = soma / numLeituras;

      // Print the average on Serial Monitor
      Serial.println("-----");
      Serial.print("Media das distancias: ");
      Serial.print(media);
      Serial.println(" cm");
      Serial.println("-----");

      // Display the average on the LCD
      lcd.setCursor(0, 1); // Move the cursor to the second row
      lcd.print("                "); // Clear the row
      lcd.setCursor(0, 1); // Move the cursor back to the start
      lcd.print(media);
      lcd.print(" cm");

      // Reset the index for new readings
      indice = 0;
    }
  }
}
