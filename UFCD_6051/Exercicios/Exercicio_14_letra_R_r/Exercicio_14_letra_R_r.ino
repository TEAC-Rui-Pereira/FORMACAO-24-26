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

  // Exibe "Exercicio 14" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 14");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara duas variáveis char com a letra R
  char letraMaiuscula = 'R';
  char letraMinuscula = 'r';

  // Exibe as letras no monitor serial
  Serial.println("Exercicio 14: Letra Maiuscula e Minuscula");
  Serial.print("Maiuscula: ");
  Serial.println(letraMaiuscula);
  Serial.print("Minuscula: ");
  Serial.println(letraMinuscula);

  // Exibe a letra maiúscula no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Maiuscula:");
  lcd.setCursor(0, 1);
  lcd.print(letraMaiuscula);
  delay(2000);

  // Exibe a letra minúscula no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Minuscula:");
  lcd.setCursor(0, 1);
  lcd.print(letraMinuscula);
  delay(2000);
}

void loop() {
  // Não é necessário repetir nada no loop
}