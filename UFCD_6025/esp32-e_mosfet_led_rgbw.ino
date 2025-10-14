//Made by RPP for UFCD6025 
//Trainer Miguel Barbosa
//use for esp32-e
// Define os pinos PWM para as cores do LED RGBW
const int redPin = 16;
const int greenPin = 17;
const int bluePin = 18;
const int whitePin = 19;

void setup() {
  // Configura os pinos como saídas
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(whitePin, OUTPUT);
}

void loop() {
  // Pisca o LED RGBW alternando as cores
  blinkColor(255, 0, 0, 0); // Vermelho
  blinkColor(0, 255, 0, 0); // Verde
  blinkColor(0, 0, 255, 0); // Azul
  blinkColor(0, 0, 0, 255); // Branco
  blinkColor(255, 255, 0, 0); // Amarelo
  blinkColor(0, 255, 255, 0); // Ciano
  blinkColor(255, 0, 255, 0); // Magenta
  blinkColor(255, 255, 255, 255); // Branco total
}

// Função para piscar a cor do LED RGBW
void blinkColor(int red, int green, int blue, int white) {
  setColor(red, green, blue, white);
  delay(1000); // Aguarda 500 milissegundos
  setColor(0, 0, 0, 0); // Desliga todas as cores
  delay(1000); // Aguarda 500 milissegundos
}

// Função para definir a cor do LED RGBW
void setColor(int red, int green, int blue, int white) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  analogWrite(whitePin, white);
}
