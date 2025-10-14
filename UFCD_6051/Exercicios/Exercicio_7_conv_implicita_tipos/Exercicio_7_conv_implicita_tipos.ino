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

  // Exibe "Exercicio 7" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 7");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara uma variável int e uma float
  int inteiro = 10;
  float decimal = 5.5;

  // Soma as variáveis
  float resultado = inteiro + decimal;

  // Exibe o resultado no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soma:");
  lcd.setCursor(0, 1);
  lcd.print(resultado);

  // Exibe o resultado no monitor serial
  Serial.println("Exercicio 7: Conversao Implicita de Tipos");
  Serial.print("Inteiro: ");
  Serial.println(inteiro);
  Serial.print("Float: ");
  Serial.println(decimal);
  Serial.print("Resultado (float): ");
  Serial.println(resultado);
}

void loop() {
  // Não é necessário repetir nada no loop
}