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

  // Exibe "Exercicio 5" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 5");
  lcd.setCursor(0, 1);
  lcd.print("Tamanho dados");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Imprime no monitor serial
  Serial.println("Exercicio 5: Tamanho dos Tipos de Dados");

  // Exibe e imprime o tamanho de int
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("int:");
  lcd.setCursor(0, 1);
  lcd.print(sizeof(int));
  lcd.print(" bytes");
  Serial.print("Tamanho de int: ");
  Serial.print(sizeof(int));
  Serial.println(" bytes");
  delay(2000);

  // Exibe e imprime o tamanho de float
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("float:");
  lcd.setCursor(0, 1);
  lcd.print(sizeof(float));
  lcd.print(" bytes");
  Serial.print("Tamanho de float: ");
  Serial.print(sizeof(float));
  Serial.println(" bytes");
  delay(2000);

  // Exibe e imprime o tamanho de double
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("double:");
  lcd.setCursor(0, 1);
  lcd.print(sizeof(double));
  lcd.print(" bytes");
  Serial.print("Tamanho de double: ");
  Serial.print(sizeof(double));
  Serial.println(" bytes");
  delay(2000);

  // Exibe e imprime o tamanho de char
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("char:");
  lcd.setCursor(0, 1);
  lcd.print(sizeof(char));
  lcd.print(" bytes");
  Serial.print("Tamanho de char: ");
  Serial.print(sizeof(char));
  Serial.println(" bytes");
  delay(2000);
}

void loop() {
  // Não é necessário repetir nada no loop
}