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

  // Exibe "Exercicio 13" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 13");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara duas variáveis do tipo double
  double num1 = 15.75;
  double num2 = 4.25;

  // Realiza as operações
  double soma = num1 + num2;
  double subtracao = num1 - num2;
  double multiplicacao = num1 * num2;
  double divisao = num1 / num2;
  int resto = (int)num1 % (int)num2; // O operador `%` só funciona com inteiros

  // Exibe os resultados no monitor serial
  Serial.println("Exercicio 13: Operacoes com double");
  Serial.print("Soma: ");
  Serial.println(soma, 2);
  Serial.print("Subtracao: ");
  Serial.println(subtracao, 2);
  Serial.print("Multiplicacao: ");
  Serial.println(multiplicacao, 2);
  Serial.print("Divisao: ");
  Serial.println(divisao, 2);
  Serial.print("Resto: ");
  Serial.println(resto);

  // Exibe os resultados no LCD (um por vez)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soma:");
  lcd.setCursor(0, 1);
  lcd.print(soma, 2);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Subtracao:");
  lcd.setCursor(0, 1);
  lcd.print(subtracao, 2);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Multiplicacao:");
  lcd.setCursor(0, 1);
  lcd.print(multiplicacao, 2);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Divisao:");
  lcd.setCursor(0, 1);
  lcd.print(divisao, 2);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Resto:");
  lcd.setCursor(0, 1);
  lcd.print(resto);
  delay(2000);
}

void loop() {
  // Não é necessário repetir nada no loop
}