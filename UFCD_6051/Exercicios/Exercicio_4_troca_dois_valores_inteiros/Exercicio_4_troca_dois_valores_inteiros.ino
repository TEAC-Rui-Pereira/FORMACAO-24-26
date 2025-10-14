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

  // Exibe "Exercicio 4" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 4");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara duas variáveis inteiras
  int a = 5;
  int b = 10;

  // Exibe os valores antes da troca no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Antes:");
  lcd.setCursor(0, 1);
  lcd.print("a=");
  lcd.print(a);
  lcd.print(" b=");
  lcd.print(b);
  delay(3000); // Aguarda 3 segundos para exibir

  // Troca os valores usando uma variável temporária
  int temp = a;
  a = b;
  b = temp;

  // Exibe os valores depois da troca no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Depois:");
  lcd.setCursor(0, 1);
  lcd.print("a=");
  lcd.print(a);
  lcd.print(" b=");
  lcd.print(b);
  delay(3000); // Aguarda 3 segundos para exibir

  // Exibe os valores no monitor serial
  Serial.println("Exercicio 4");
  Serial.println("Antes da troca:");
  Serial.print("a = ");
  Serial.println(5);
  Serial.print("b = ");
  Serial.println(10);

  Serial.println("Depois da troca:");
  Serial.print("a = ");
  Serial.println(a);
  Serial.print("b = ");
  Serial.println(b);
}

void loop() {
  // Não é necessário repetir nada no loop
}