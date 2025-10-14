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

  // Exibe "Exercicio 10" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 10");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Declara variáveis com nomes significativos
  int idade = 25;               // Idade de uma pessoa
  float altura = 1.75;          // Altura em metros
  char inicial = 'A';           // Inicial do nome
  double saldo = 12345.67;      // Saldo bancário
  bool ativo = true;            // Status de atividade (ativo/inativo)

  // Exibe os valores no monitor serial
  Serial.println("Exercicio 10: Nomeacao de Variaveis");
  Serial.print("Idade: ");
  Serial.println(idade);
  Serial.print("Altura: ");
  Serial.println(altura);
  Serial.print("Inicial: ");
  Serial.println(inicial);
  Serial.print("Saldo: ");
  Serial.println(saldo);
  Serial.print("Ativo: ");
  Serial.println(ativo ? "Sim" : "Nao");

  // Exibe os valores no LCD (um por vez)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Idade:");
  lcd.setCursor(0, 1);
  lcd.print(idade);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Altura:");
  lcd.setCursor(0, 1);
  lcd.print(altura);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicial:");
  lcd.setCursor(0, 1);
  lcd.print(inicial);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Saldo:");
  lcd.setCursor(0, 1);
  lcd.print(saldo);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ativo:");
  lcd.setCursor(0, 1);
  lcd.print(ativo ? "Sim" : "Nao");
  delay(2000);
}

void loop() {
  // Não é necessário repetir nada no loop
}