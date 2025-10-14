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

// Declara duas variáveis do tipo float
float num1 = 5.5;
float num2 = 2.2;

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Inicializa o LCD
  lcd.begin(16, 2); // Configura o LCD com 16 colunas e 2 linhas
}

void loop() {
  // Calcula as operações
  float soma = num1 + num2;
  float subtracao = num1 - num2;
  float multiplicacao = num1 * num2;
  float divisao = num1 / num2;


// Exercicio 2
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 2");
  lcd.setCursor(0, 1);
  delay(2000);

  // Exibe a soma no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soma:");
  lcd.setCursor(0, 1);
  lcd.print(soma);
  delay(2000);

  // Exibe a subtração no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Subtracao:");
  lcd.setCursor(0, 1);
  lcd.print(subtracao);
  delay(2000);

  // Exibe a multiplicação no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Multiplicacao:");
  lcd.setCursor(0, 1);
  lcd.print(multiplicacao);
  delay(2000);

  // Exibe a divisão no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Divisao:");
  lcd.setCursor(0, 1);
  lcd.print(divisao);
  delay(2000);

  // Exibe os resultados no monitor serial
  Serial.println("Operacoes com numeros decimais:");
  Serial.println("Exercicio 2");
  Serial.print("Soma: ");
  Serial.println(soma);
  Serial.print("Subtracao: ");
  Serial.println(subtracao);
  Serial.print("Multiplicacao: ");
  Serial.println(multiplicacao);
  Serial.print("Divisao: ");
  Serial.println(divisao);
}