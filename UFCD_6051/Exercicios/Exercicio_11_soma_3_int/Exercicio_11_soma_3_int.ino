#include <Arduino.h>
#include <LiquidCrystal.h>
//TEAC_24.0366 Rui Pais Pereira
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

  // Exibe "Exercicio 11" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 11");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara três variáveis do tipo int e atribui valores
  int num1 = 10;
  int num2 = 20;
  int num3 = 30;

  // Calcula a soma total
  int soma = num1 + num2 + num3;

  // Exibe os valores e a soma no monitor serial
  Serial.println("Exercicio 11: Soma de Tres Inteiros");
  Serial.print("Numero 1: ");
  Serial.println(num1);
  Serial.print("Numero 2: ");
  Serial.println(num2);
  Serial.print("Numero 3: ");
  Serial.println(num3);
  Serial.print("Soma Total: ");
  Serial.println(soma);

  // Exibe os valores e a soma no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soma:");
  lcd.print("10+20+30=");
  lcd.setCursor(0, 1);
  lcd.print(soma);
}

void loop() {
  // Não é necessário repetir nada no loop
}