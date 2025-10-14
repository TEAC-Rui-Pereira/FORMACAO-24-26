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

  // Exibe "Exercicio 18" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 18");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara uma variável int com valor inicial 10
  int valor = 10;

  // Exibe o valor inicial no monitor serial
  Serial.println("Exercicio 18: Alterar Valores com Operadores");
  Serial.print("Valor inicial: ");
  Serial.println(valor);

  // Exibe o valor inicial no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicial:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  delay(2000);

  // Usa o operador +=
  valor += 5; // Adiciona 5
  Serial.print("Apos += 5: ");
  Serial.println(valor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("+= 5:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  delay(2000);

  // Usa o operador -=
  valor -= 3; // Subtrai 3
  Serial.print("Apos -= 3: ");
  Serial.println(valor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-= 3:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  delay(2000);

  // Usa o operador *=
  valor *= 2; // Multiplica por 2
  Serial.print("Apos *= 2: ");
  Serial.println(valor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*= 2:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  delay(2000);

  // Usa o operador /=
  valor /= 4; // Divide por 4
  Serial.print("Apos /= 4: ");
  Serial.println(valor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("/= 4:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  delay(2000);

  // Usa o operador ++
  valor++; // Incrementa 1
  Serial.print("Apos ++: ");
  Serial.println(valor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("++:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  delay(2000);

  // Usa o operador --
  valor--; // Decrementa 1
  Serial.print("Apos --: ");
  Serial.println(valor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("--:");
  lcd.setCursor(0, 1);
  lcd.print(valor);
  delay(2000);
}

void loop() {
  // Não é necessário repetir nada no loop
}