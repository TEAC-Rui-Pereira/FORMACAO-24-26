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

// Declara uma variável do tipo char
char letra_R = 'R';

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Inicializa o LCD
  lcd.begin(16, 2); // Configura o LCD com 16 colunas e 2 linhas

  // Exibe "Exercicio 3:" no LCD
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 3:");
  delay(2000); // Exibe por 2 segundos
}

void loop() {
  // Limpa o LCD
  lcd.clear();

  // Exibe a mensagem no LCD
  lcd.setCursor(0, 0);
  lcd.print("O caractere e:");
  lcd.setCursor(0, 1);
  lcd.print(letra_R);

  // Exibe a mensagem no monitor serial
  Serial.print("O caractere e: ");
  Serial.println(letra_R);

  // Aguarda 2 segundos antes de repetir
  delay(2000);
}