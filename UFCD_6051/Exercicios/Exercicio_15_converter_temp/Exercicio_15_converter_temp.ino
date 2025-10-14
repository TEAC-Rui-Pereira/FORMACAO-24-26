#include <Arduino.h>
#include <LiquidCrystal.h>

// Define os pinos de conexão com o LCD
const int rs = 11;
const int en = 12;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

// Inicializa o objeto LiquidCrystal com os pinos definidos
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Inicializa o LCD
  lcd.begin(16, 2); // Configura o LCD com 16 colunas e 2 linhas

  // Exibe "Exercicio 15" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 15");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Instruções para o usuário no monitor serial
  Serial.println("Exercicio 15: Temperatura em Celsius e Fahrenheit");
  Serial.println("Digite a temperatura em Celsius:");
}

void loop() {
  static bool leituraConcluida = false; // Controla se a leitura foi feita
  static float celsius = 0.0;           // Armazena a temperatura em Celsius

  if (Serial.available() > 0 && !leituraConcluida) {
    // Lê a temperatura em Celsius do monitor serial
    celsius = Serial.parseFloat();
    leituraConcluida = true;

    // Converte para Fahrenheit
    float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;

    // Exibe os valores no monitor serial
    Serial.print("Temperatura em Celsius: ");
    Serial.println(celsius, 2);
    Serial.print("Temperatura em Fahrenheit: ");
    Serial.println(fahrenheit, 2);

    // Exibe a temperatura em Celsius no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Celsius:");
    lcd.setCursor(0, 1);
    lcd.print(celsius, 2);
    lcd.print(" C");
    delay(2000);

    // Exibe a temperatura em Fahrenheit no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fahrenheit:");
    lcd.setCursor(0, 1);
    lcd.print(fahrenheit, 2);
    lcd.print(" F");
    delay(2000);

    // Reinicia a leitura
    leituraConcluida = false;
    Serial.println("\nDigite a temperatura em Celsius:");
  }
}