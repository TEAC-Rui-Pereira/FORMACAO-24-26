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

// Define a constante PI
#define PI 3.14159

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Inicializa o LCD
  lcd.begin(16, 2); // Configura o LCD com 16 colunas e 2 linhas

  // Exibe "Exercicio 6" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 6");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara o raio e calcula a área do círculo
  int raio = 5;
  float area = PI * raio * raio;

  // Exibe a área no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Raio: ");
  lcd.print(raio);
  lcd.setCursor(0, 1);
  lcd.print("Area: ");
  lcd.print(area);

  // Exibe a área no monitor serial
  Serial.println("Exercicio 6: Utilizar Constantes");
  Serial.print("Raio: ");
  Serial.println(raio);
  Serial.print("Area: ");
  Serial.println(area);
}

void loop() {
  // Não é necessário repetir nada no loop
}