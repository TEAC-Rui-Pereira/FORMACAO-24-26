#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

// --- Credenciais Wi-Fi ---
const char* ssid = "IEFP-Formacao";
const char* password = "";

// --- Credenciais da interface web ---
const char* http_username = "admin";
const char* http_password = "1234";
//leds 
const int ledVerde = 21;
const int ledAmarelo = 22;
const int ledVermelho = 23;
// --- GPIOs ---
const int output26 = 26;
const int output27 = 25;
String output26State = "off";
String output27State = "off";

// --- Sensor DHT11 ---
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temperature = 0.0;
float humidity = 0.0;

// --- Servidor web ---
WebServer server(1974);


//acende led
void atualizaLEDs() {
  // Desliga todos primeiro
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  if (temperature <= 22.0) {
    digitalWrite(ledVerde, HIGH);
  } else if (temperature > 22.0 && temperature < 30.0) {
    digitalWrite(ledAmarelo, HIGH);
  } else {
    digitalWrite(ledVermelho, HIGH);
  }
}
// --- Leitura do sensor DHT ---
void readDHT() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler do sensor DHT!");
    humidity = 0.0;
    temperature = 0.0;
  }
  atualizaLEDs(); // Atualiza os LEDs conforme a nova temperatura
}

// --- Página principal ---
void handleRoot() {
  if (!server.authenticate(http_username, http_password)) {
    return server.requestAuthentication();
  }

  readDHT();

  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>";
  html += "@font-face { font-family: 'ArtDeco'; src: url('ArtDeco.woff') format('woff'); }";
  html += "body { background-color: #f5f0e6; color: #2d2d2d; font-family: 'ArtDeco', 'Georgia', serif; text-align: center; margin: 0; padding: 0; }";
  html += "h1 { font-size: 48px; margin-top: 30px; letter-spacing: 2px; color: #b29400; }";
  html += ".button { background-color: #000000; border: 4px double #b29400; color: #f5f0e6; padding: 14px 36px; text-decoration: none; font-size: 28px; margin: 10px; cursor: pointer; font-weight: bold; transition: 0.3s; }";
  html += ".button2 { background-color: #b29400; color: #000000; border: 4px double #000000; }";
  html += ".button:hover { background-color: #b29400; color: #000000; border-color: #000000; }";
  html += ".button2:hover { background-color: #000000; color: #f5f0e6; border-color: #b29400; }";
  html += "</style></head>";

  html += "<body>";
  html += "<h1>Rui Pais Pereira Web Server</h1>";
  html += "<a class=\"button\" href=\"/on\">LIGAR</a>";
  html += "<a class=\"button button2\" href=\"/off\">DESLIGAR</a>";

  html += "<p>GPIO 26 - Estado: " + output26State + "</p>";
  html += (output26State == "off") ?
    "<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>" :
    "<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>";

  html += "<p>GPIO 27 - Estado: " + output27State + "</p>";
  html += (output27State == "off") ?
    "<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>" :
    "<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>";

  html += "<h2>Temperatura e Humidade (atualiza a cada 1 min)</h2>";
  html += "<p>Temperatura: <span id=\"temp\">" + String(temperature, 1) + "</span> &deg;C</p>";
  html += "<p>Humidade: <span id=\"hum\">" + String(humidity, 1) + "</span> %</p>";
  html += "<p>Última atualização: <span id=\"timestamp\">--:--:--</span></p>";

  html += "<script>";
  html += "function atualizaDHT() {";
  html += "fetch('/dht')"
          ".then(res => res.json())"
          ".then(data => {"
          " document.getElementById('temp').textContent = data.temperature.toFixed(1);"
          " document.getElementById('hum').textContent = data.humidity.toFixed(1);"
          " let agora = new Date();"
          " document.getElementById('timestamp').textContent = agora.toLocaleTimeString();"
          "});"
          "}";
  html += "setInterval(atualizaDHT, 60000);";
  html += "atualizaDHT();";
  html += "</script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// --- Rota JSON para JavaScript ---
void handleDHTJson() {
  readDHT();
  String json = "{";
  json += "\"temperature\":" + String(temperature, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1);
  json += "}";
  server.send(200, "application/json", json);
}

// --- Manipuladores GPIO ---
void handleAllOn() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "on";
  output27State = "on";
  digitalWrite(output26, HIGH);
  digitalWrite(output27, HIGH);
  handleRoot();
}

void handleAllOff() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "off";
  output27State = "off";
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  handleRoot();
}

void handleGPIO26On() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "on";
  digitalWrite(output26, HIGH);
  handleRoot();
}

void handleGPIO26Off() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "off";
  digitalWrite(output26, LOW);
  handleRoot();
}

void handleGPIO27On() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output27State = "on";
  digitalWrite(output27, HIGH);
  handleRoot();
}

void handleGPIO27Off() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output27State = "off";
  digitalWrite(output27, LOW);
  handleRoot();
}

// --- Setup ---
void setup() {
  Serial.begin(115200);

  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  dht.begin();

  Serial.print("A ligar a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi ligado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Rotas do servidor
  server.on("/", handleRoot);
  server.on("/on", handleAllOn);
  server.on("/off", handleAllOff);
  server.on("/26/on", handleGPIO26On);
  server.on("/26/off", handleGPIO26Off);
  server.on("/27/on", handleGPIO27On);
  server.on("/27/off", handleGPIO27Off);
  server.on("/dht", handleDHTJson);

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

// --- Loop principal ---
void loop() {
  server.handleClient();
}
