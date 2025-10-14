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

  // Exibe "Exercicio 19" no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Exercicio 19");
  delay(2000); // Aguarda 2 segundos para exibir o título

  // Instruções para o usuário no monitor serial
  Serial.println("Exercicio 19: Verificar Numero Par ou Impar");
  Serial.println("Digite um numero inteiro:");
}

void loop() {
  static bool leituraConcluida = false; // Controla se a leitura foi feita
  static int numero = 0;                // Armazena o número lido

  if (Serial.available() > 0 && !leituraConcluida) {
    // Lê o número inteiro do monitor serial
    numero = Serial.parseInt();
    leituraConcluida = true;

    // Verifica se o número é par ou ímpar
    bool isPar = (numero % 2 == 0);

    // Exibe o resultado no monitor serial
    Serial.print("O numero ");
    Serial.print(numero);
    if (isPar) {
      Serial.println(" e par.");
    } else {
      Serial.println(" e impar.");
    }

    // Exibe o resultado no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Numero: ");
    lcd.print(numero);
    lcd.setCursor(0, 1);
    if (isPar) {
      lcd.print("E par");
    } else {
      lcd.print("E impar");
    }
    delay(3000); // Aguarda 3 segundos para exibir o resultado

    // Reinicia a leitura
    leituraConcluida = false;
    Serial.println("\nDigite um numero inteiro:");
  }
}