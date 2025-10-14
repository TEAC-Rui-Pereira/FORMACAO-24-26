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

  // Exibe "Exercicio 8" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 8");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara um float com valor 7.8
  float valorOriginal = 7.8;

  // Faz o cast para int
  int valorConvertido = (int)valorOriginal;

  // Exibe os valores no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Original: ");
  lcd.print(valorOriginal);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Convertido: ");
  lcd.print(valorConvertido);
  delay(2000);

  // Exibe os valores no monitor serial
  Serial.println("Exercicio 8: Conversao Explicita (Casting)");
  Serial.print("Valor Original (float): ");
  Serial.println(valorOriginal);
  Serial.print("Valor Convertido (int): ");
  Serial.println(valorConvertido);
}

void loop() {
  // Não é necessário repetir nada no loop
}