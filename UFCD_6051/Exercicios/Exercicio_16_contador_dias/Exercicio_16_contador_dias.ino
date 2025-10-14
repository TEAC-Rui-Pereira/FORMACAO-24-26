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

  // Exibe "Exercicio 16" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 16");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara uma variável para armazenar o número de dias
  int dias = 16; // Exemplo: 10 dias

  // Calcula semanas e dias restantes
  int semanas = dias / 7;
  int diasRestantes = dias % 7;

  // Exibe os resultados no monitor serial
  Serial.println("Exercicio 16: Contador de Dias");
  Serial.print(dias);
  Serial.print(" dias = ");
  Serial.print(semanas);
  Serial.print(" semana(s) e ");
  Serial.print(diasRestantes);
  Serial.println(" dia(s)");

   // Exibe o número de dias no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DIAS:");
  lcd.setCursor(0, 1);
  lcd.print(dias);
  delay(2000);

  // Exibe o número de semanas no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Semanas:");
  lcd.setCursor(0, 1);
  lcd.print(semanas);
  delay(2000);

  // Exibe os dias restantes no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dias Restantes:");
  lcd.setCursor(0, 1);
  lcd.print(diasRestantes);
  delay(2000);
}

void loop() {
  // Não é necessário repetir nada no loop
}