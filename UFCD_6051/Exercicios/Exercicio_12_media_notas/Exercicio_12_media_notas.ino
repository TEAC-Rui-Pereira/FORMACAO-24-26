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

  // Exibe "Exercicio 12" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 12");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara três variáveis float para armazenar as notas
  float nota1 = 8.5;
  float nota2 = 7.3;
  float nota3 = 9.0;

  // Calcula a média
  float media = (nota1 + nota2 + nota3) / 3;

  // Exibe as notas e a média no monitor serial
  Serial.println("Exercicio 12: Media de Notas");
  Serial.print("Nota 1: ");
  Serial.println(nota1, 2);
  Serial.print("Nota 2: ");
  Serial.println(nota2, 2);
  Serial.print("Nota 3: ");
  Serial.println(nota3, 2);
  Serial.print("Media: ");
  Serial.println(media, 2);

  // Exibe a média no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Media:");
  lcd.setCursor(0, 1);
  lcd.print(media, 2); // Exibe a média com 2 casas decimais
}

void loop() {
  // Não é necessário repetir nada no loop
}