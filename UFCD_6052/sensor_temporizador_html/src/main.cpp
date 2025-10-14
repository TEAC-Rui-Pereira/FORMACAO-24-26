#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "FS.h"
#include "SPIFFS.h"

// --- Credenciais Wi-Fi ---
const char* ssid = "IEFP-Formacao";
const char* password = "";

// --- Interface Web ---
const char* http_username = "admin";
const char* http_password = "1234";

// --- GPIOs ---
const int ledVerde = 21;      // led verde
const int ledAmarelo = 22;    // led amarelo
const int ledVermelho = 23;   // led vermelho 
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

// --- Web server ---
WebServer server(1974);

void atualizaLEDs() {
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

// --- Lê o sensor DHT11 ---
void readDHT() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Falha ao ler do sensor DHT!");
    humidity = 0.0;
    temperature = 0.0;
  }
  atualizaLEDs();
}

// --- Página HTML ---
void handleRoot() {
  if (!server.authenticate(http_username, http_password)) {
    return server.requestAuthentication();
  }

  readDHT();

  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="pt">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <title>SmarTogether Web</title>
  <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&display=swap" rel="stylesheet" />
  <style>
    body {
      font-family: 'Roboto', sans-serif;
      background-color: #f4f6f8;
      color: #333;
      margin: 0;
      padding: 20px;
      text-align: center;
    }

    h1 {
      color: #2c3e50;
      font-size: 2.5rem;
      margin-bottom: 30px;
    }

    .card {
      background-color: #ffffff;
      border-radius: 12px;
      box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
      margin: 20px auto;
      max-width: 400px;
      padding: 20px;
    }

    .btn {
      display: inline-block;
      margin: 10px 5px;
      padding: 12px 24px;
      font-size: 1rem;
      font-weight: bold;
      border-radius: 8px;
      text-decoration: none;
      cursor: pointer;
      transition: 0.3s;
    }

    .btn-on {
      background-color: #2ecc71;
      color: white;
      border: none;
    }

    .btn-on:hover {
      background-color: #27ae60;
    }

    .btn-off {
      background-color: #e74c3c;
      color: white;
      border: none;
    }

    .btn-off:hover {
      background-color: #c0392b;
    }

    .label {
      font-weight: bold;
      margin-bottom: 10px;
      display: block;
    }

    .sensor {
      margin-top: 10px;
      font-size: 1.1rem;
    }

    #countdown {
      font-weight: bold;
      color: #e67e22;
    }

    @media (max-width: 480px) {
      .btn {
        width: 90%;
        font-size: 1.1rem;
      }
    }
  </style>
</head>
<body>

  <h1>RPP Web Control</h1>

  <div class="card">
    <span class="label">Controlo Geral</span>
    <a class="btn btn-on" href="/on">LIGAR TUDO</a>
    <a class="btn btn-off" href="/off">DESLIGAR TUDO</a>
  </div>

  <div class="card">
    <span class="label">GPIO 26 - Estado: )rawliteral" + output26State + R"rawliteral(</span>
    <a class="btn btn-on" href="/26/on">ON</a>
    <a class="btn btn-off" href="/26/off">OFF</a>
  </div>

  <div class="card">
    <span class="label">GPIO 27 - Estado: )rawliteral" + output27State + R"rawliteral(</span>
    <a class="btn btn-on" href="/27/on">ON</a>
    <a class="btn btn-off" href="/27/off">OFF</a>
  </div>

  <div class="card">
    <span class="label">Leituras do Sensor DHT11</span>
    <div class="sensor">🌡️ Temperatura: <span id="temp">)rawliteral" + String(temperature, 1) + R"rawliteral(</span> °C</div>
    <div class="sensor">💧 Humidade: <span id="hum">)rawliteral" + String(humidity, 1) + R"rawliteral(</span> %</div>
    <div class="sensor">⏱️ Última atualização: <span id="timestamp">--:--:--</span></div>
    <div class="sensor">🔄 Atualiza em <span id="countdown">60</span> segundos</div>
  </div>

  <div class="card">
    <span class="label">Estado do LED de Temperatura</span>
    <div id="led-indicador" style="font-size: 2rem;">🔲</div>
    <div class="sensor">Cor atual: <span id="led-status">--</span></div>
  </div>

  <script>
    let countdown = 10;

    function atualizaDHT() {
      fetch('/dht')
        .then(res => res.json())
        .then(data => {
          document.getElementById('temp').textContent = data.temperature.toFixed(1);
          document.getElementById('hum').textContent = data.humidity.toFixed(1);
          document.getElementById('timestamp').textContent = new Date().toLocaleTimeString();

          // Atualiza ícone e texto conforme estado do LED
          let icon = '🔲';
          let corTexto = '--';
          if (data.led === 'verde') {
            icon = '🟢';
            corTexto = 'Verde';
          } else if (data.led === 'amarelo') {
            icon = '🟡';
            corTexto = 'Amarelo';
          } else if (data.led === 'vermelho') {
            icon = '🔴';
            corTexto = 'Vermelho';
          }

          document.getElementById('led-indicador').innerHTML = icon;
          document.getElementById('led-status').textContent = corTexto;

          countdown = 10;
        });
    }

    function updateCountdown() {
      if (countdown > 0) countdown--;
      document.getElementById('countdown').textContent = countdown;
      if (countdown === 0) atualizaDHT();
    }

    setInterval(updateCountdown, 1000);
    atualizaDHT();
  </script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

// --- JSON para AJAX ---
void handleDHTJson() {
  readDHT();

  String ledStatus;
  if (temperature <= 22.0) {
    ledStatus = "verde";
  } else if (temperature < 30.0) {
    ledStatus = "amarelo";
  } else {
    ledStatus = "vermelho";
  }

  String json = "{";
  json += "\"temperature\":" + String(temperature, 1) + ",";
  json += "\"humidity\":" + String(humidity, 1) + ",";
  json += "\"led\":\"" + ledStatus + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

// --- Manipulação dos GPIOs ---
void handleAllOn() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "on"; output27State = "on";
  digitalWrite(output26, HIGH); digitalWrite(output27, HIGH);
  handleRoot();
}

void handleAllOff() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "off"; output27State = "off";
  digitalWrite(output26, LOW); digitalWrite(output27, LOW);
  handleRoot();
}

void handleGPIO26On() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "on"; digitalWrite(output26, HIGH);
  handleRoot();
}

void handleGPIO26Off() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output26State = "off"; digitalWrite(output26, LOW);
  handleRoot();
}

void handleGPIO27On() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output27State = "on"; digitalWrite(output27, HIGH);
  handleRoot();
}

void handleGPIO27Off() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  output27State = "off"; digitalWrite(output27, LOW);
  handleRoot();
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);

  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  dht.begin();

  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }

  WiFi.begin(ssid, password);
  Serial.print("A ligar à rede Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi ligado.");
  Serial.println("Endereço IP: " + WiFi.localIP().toString());

  // Removido server.serveStatic("/", SPIFFS, "/");

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

void loop() {
  server.handleClient();
}
