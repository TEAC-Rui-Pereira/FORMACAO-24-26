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

  // Exibe "Exercicio 17" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 17");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara duas variáveis do tipo char
  char char1 = 'A';
  char char2 = 'B';

  // Cria uma string para concatenar os caracteres
  char juntas[3]; // Tamanho 3: 2 caracteres + '\0' (terminador nulo)
  juntas[0] = char1;
  juntas[1] = char2;
  juntas[2] = '\0'; // Finaliza a string

  // Exibe os caracteres no monitor serial
  Serial.println("Exercicio 17: Junta Dois Caracteres");
  Serial.print("Caracter 1: ");
  Serial.println(char1);
  Serial.print("Caracter 2: ");
  Serial.println(char2);
  Serial.print("Juntos: ");
  Serial.println(juntas);

  // Exibe os caracteres A no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Letra:");
  lcd.setCursor(0, 1);
  lcd.print(char1);
delay (2000);
  // Exibe  mais no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("mais");
  lcd.setCursor(0, 1);
delay (2000);

 // Exibe os caracteres B no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Letra:");
  lcd.setCursor(0, 1);
  lcd.print(char2);
delay (2000);
  // Exibe os caracteres juntos no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Juntas:");
  lcd.setCursor(0, 1);
  lcd.print(juntas);
}

void loop() {
  // Não é necessário repetir nada no loop
}