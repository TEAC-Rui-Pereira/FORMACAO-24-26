#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include "FS.h"
#include "SPIFFS.h"
#include <ESPmDNS.h>

// *************** CONFIGURAÇÕES ***************
// Wi-Fi
const char* ssid = "IEFP-Formacao";
const char* password = "";
const char* hostname = "TEAC-SmartControl";

// Autenticação Web
const char* http_username = "admin";
const char* http_password = "securePass123";

// Pinos GPIO
const int LED_VERDE = 21;
const int LED_AMARELO = 22;
const int LED_VERMELHO = 23;
const int RELE_1 = 26;
const int RELE_2 = 25;

// Sensor DHT
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variáveis de estado
String rele1State = "off";
String rele2State = "off";
float temperature = 0.0;
float humidity = 0.0;

// Servidor Web
WebServer server(1974);

// *************** FUNÇÕES AUXILIARES ***************
void listSPIFFSFiles() {
  Serial.println("\n[SPIFFS] Listando arquivos:");
  File root = SPIFFS.open("/");
  if(!root) {
    Serial.println("[ERRO] Falha ao abrir diretório raiz");
    return;
  }
  
  File file = root.openNextFile();
  while(file) {
    Serial.printf("  %s (%d bytes)\n", file.name(), file.size());
    file = root.openNextFile();
  }
  Serial.println("-------------------------------------");
}

void atualizarLEDsTemperatura() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  if (temperature <= 22.0) {
    digitalWrite(LED_VERDE, HIGH);
  } else if (temperature > 22.0 && temperature < 30.0) {
    digitalWrite(LED_AMARELO, HIGH);
  } else {
    digitalWrite(LED_VERMELHO, HIGH);
  }
}

void lerSensorDHT() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("[ERRO] Falha ao ler sensor DHT!");
    humidity = 0.0;
    temperature = 0.0;
    return;
  }
  
  atualizarLEDsTemperatura();
  Serial.printf("[DHT] Temperatura: %.1f°C | Umidade: %.1f%%\n", temperature, humidity);
}

String getLEDStatus() {
  if (digitalRead(LED_VERDE)) return "verde";
  if (digitalRead(LED_AMARELO)) return "amarelo";
  if (digitalRead(LED_VERMELHO)) return "vermelho";
  return "desligado";
}

String getJSONData() {
  return "{\"temperature\":" + String(temperature, 1) + 
         ",\"humidity\":" + String(humidity, 1) + 
         ",\"led\":\"" + getLEDStatus() + "\"" +
         ",\"uptime\":" + String(millis()) + "}";
}

// *************** HANDLERS WEB ***************
void handleRoot() {
  if (!server.authenticate(http_username, http_password)) {
    return server.requestAuthentication();
  }

  lerSensorDHT();

  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>TEAC Smart Control</title>
  <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600&display=swap" rel="stylesheet">
  <style>
    :root {
      --primary: #4361ee;
      --secondary: #3f37c9;
      --success: #4cc9f0;
      --danger: #f72585;
      --warning: #f8961e;
      --dark: #212529;
      --light: #f8f9fa;
    }
    * {
      box-sizing: border-box;
      margin: 0;
      padding: 0;
    }
    body {
      font-family: 'Poppins', sans-serif;
      background-color: #f5f7fa;
      color: var(--dark);
      line-height: 1.6;
      padding: 20px;
    }
    .container {
      max-width: 800px;
      margin: 0 auto;
    }
    header {
      text-align: center;
      margin-bottom: 30px;
    }
    h1 {
      color: var(--primary);
      font-weight: 600;
      margin-bottom: 10px;
    }
    .card {
      background: white;
      border-radius: 10px;
      box-shadow: 0 4px 6px rgba(0,0,0,0.1);
      padding: 25px;
      margin-bottom: 20px;
    }
    .card-title {
      color: var(--secondary);
      margin-bottom: 15px;
      font-size: 1.2rem;
      font-weight: 600;
    }
    .btn-group {
      display: flex;
      gap: 10px;
      margin-top: 15px;
    }
    .btn {
      padding: 10px 20px;
      border: none;
      border-radius: 5px;
      font-weight: 500;
      cursor: pointer;
      transition: all 0.3s ease;
      flex: 1;
      text-align: center;
      text-decoration: none;
      color: white;
    }
    .btn-primary {
      background-color: var(--primary);
    }
    .btn-primary:hover {
      background-color: var(--secondary);
      transform: translateY(-2px);
    }
    .btn-danger {
      background-color: var(--danger);
    }
    .btn-danger:hover {
      background-color: #d1146a;
      transform: translateY(-2px);
    }
    .btn-success {
      background-color: var(--success);
    }
    .btn-success:hover {
      background-color: #3aa8d8;
      transform: translateY(-2px);
    }
    .sensor-data {
      display: flex;
      justify-content: space-between;
      margin-bottom: 10px;
    }
    .sensor-value {
      font-weight: 600;
    }
    .status-indicator {
      display: inline-block;
      width: 15px;
      height: 15px;
      border-radius: 50%;
      margin-right: 5px;
    }
    .status-on {
      background-color: var(--success);
    }
    .status-off {
      background-color: var(--danger);
    }
    .update-info {
      font-size: 0.8rem;
      color: #6c757d;
      text-align: right;
      margin-top: 15px;
    }
    /* Estilo do Termômetro */
    .thermometer {
      width: 60px;
      height: 200px;
      margin: 20px auto;
      position: relative;
      background: #f8f9fa;
      border-radius: 30px;
      border: 3px solid #212529;
      box-shadow: inset 0 0 10px rgba(0,0,0,0.2);
      overflow: hidden;
    }
    .thermometer-bulb {
      width: 50px;
      height: 50px;
      background: #f72585;
      border-radius: 50%;
      position: absolute;
      bottom: 10px;
      left: 5px;
      z-index: 2;
      box-shadow: 0 0 5px rgba(0,0,0,0.3);
      transition: background 0.5s ease;
    }
    .thermometer-column {
      position: absolute;
      width: 30px;
      background: linear-gradient(to top, #f72585, #4361ee);
      bottom: 60px;
      left: 15px;
      border-radius: 15px 15px 0 0;
      transition: height 0.5s ease;
      z-index: 1;
    }
    .thermometer-scale {
      position: absolute;
      width: 100%;
      height: 140px;
      bottom: 60px;
      left: 0;
    }
    .thermometer-mark {
      position: absolute;
      width: 100%;
      height: 1px;
      background: #212529;
      left: 0;
    }
    .thermometer-label {
      position: absolute;
      font-size: 10px;
      left: 65px;
      transform: translateY(-50%);
    }
    .temperature-display {
      font-size: 1.8rem;
      font-weight: 600;
      text-align: center;
      margin-top: 10px;
      color: #212529;
    }
    @media (max-width: 600px) {
      .btn-group {
        flex-direction: column;
      }
      .thermometer {
        width: 50px;
        height: 180px;
      }
      .thermometer-bulb {
        width: 40px;
        height: 40px;
        left: 5px;
      }
      .thermometer-column {
        width: 25px;
        left: 12.5px;
      }
    }
  </style>
</head>
<body>
  <div class="container">
    <header>
      <h1>TEAC Smart Control</h1>
      <p>Controle remoto com termômetro visual</p>
    </header>

    <div class="card">
      <div class="card-title">Controle Geral</div>
      <div class="btn-group">
        <a href="/on" class="btn btn-success">Ligar Tudo</a>
        <a href="/off" class="btn btn-danger">Desligar Tudo</a>
      </div>
    </div>

    <div class="card">
      <div class="card-title">Relé 1 (GPIO 26)</div>
      <div class="sensor-data">
        <span>Estado atual:</span>
        <span><span class="status-indicator status-)rawliteral" + rele1State + R"rawliteral("></span>)rawliteral" + rele1State + R"rawliteral(</span>
      </div>
      <div class="btn-group">
        <a href="/26/on" class="btn btn-primary">Ligar</a>
        <a href="/26/off" class="btn btn-danger">Desligar</a>
      </div>
    </div>

    <div class="card">
      <div class="card-title">Relé 2 (GPIO 27)</div>
      <div class="sensor-data">
        <span>Estado atual:</span>
        <span><span class="status-indicator status-)rawliteral" + rele2State + R"rawliteral("></span>)rawliteral" + rele2State + R"rawliteral(</span>
      </div>
      <div class="btn-group">
        <a href="/27/on" class="btn btn-primary">Ligar</a>
        <a href="/27/off" class="btn btn-danger">Desligar</a>
      </div>
    </div>

    <div class="card">
      <div class="card-title">Sensor DHT11</div>
      <div class="sensor-data">
        <span>Umidade:</span>
        <span class="sensor-value">)rawliteral" + String(humidity, 1) + R"rawliteral( %</span>
      </div>
      <div class="sensor-data">
        <span>Status LED:</span>
        <span class="sensor-value">)rawliteral" + getLEDStatus() + R"rawliteral(</span>
      </div>
      <div class="update-info">
        Atualizado em: <span id="update-time">)rawliteral" + String(millis() / 1000) + R"rawliteral( segundos</span>
      </div>
    </div>

    <div class="card">
      <div class="card-title">Termômetro Visual</div>
      
      <div class="thermometer">
        <div class="thermometer-bulb"></div>
        <div class="thermometer-column" id="mercury" 
             style="height: )rawliteral" + String(map(constrain(temperature, 15, 40), 15, 40, 0, 140)) + R"rawliteral(px;"></div>
        <div class="thermometer-scale">
          <div class="thermometer-mark" style="bottom: 0px;"><span class="thermometer-label">40°C</span></div>
          <div class="thermometer-mark" style="bottom: 35px;"><span class="thermometer-label">35°C</span></div>
          <div class="thermometer-mark" style="bottom: 70px;"><span class="thermometer-label">30°C</span></div>
          <div class="thermometer-mark" style="bottom: 105px;"><span class="thermometer-label">25°C</span></div>
          <div class="thermometer-mark" style="bottom: 140px;"><span class="thermometer-label">20°C</span></div>
        </div>
      </div>
      
      <div class="temperature-display">
        Temperatura: <span id="current-temp">)rawliteral" + String(temperature, 1) + R"rawliteral(</span>°C
      </div>
    </div>
  </div>

  <script>
    function fetchData() {
      fetch('/dht')
        .then(response => response.json())
        .then(data => {
          // Atualiza os elementos da página
          document.querySelector('.sensor-value:nth-of-type(1)').textContent = 
            data.humidity.toFixed(1) + ' %';
          document.querySelector('.sensor-value:nth-of-type(2)').textContent = 
            data.led;
          document.getElementById('update-time').textContent = 
            Math.floor(data.uptime / 1000) + ' segundos';
            
          // Atualiza o termômetro
          const temp = parseFloat(data.temperature);
          const height = Math.min(140, Math.max(0, (temp - 15) * (140 / 25)));
          document.getElementById('mercury').style.height = height + 'px';
          document.getElementById('current-temp').textContent = data.temperature.toFixed(1);
          
          // Muda a cor conforme a temperatura
          const bulb = document.querySelector('.thermometer-bulb');
          if(temp < 22) {
            bulb.style.background = '#4cc9f0'; // Azul
          } else if(temp < 30) {
            bulb.style.background = '#f8961e'; // Laranja
          } else {
            bulb.style.background = '#f72585'; // Vermelho
          }
        });
    }
    
    setInterval(fetchData, 10000);
    fetchData(); // Chama imediatamente ao carregar
  </script>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

void handleDHTData() {
  server.send(200, "application/json", getJSONData());
}

void handleAllOn() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  
  rele1State = "on";
  rele2State = "on";
  digitalWrite(RELE_1, HIGH);
  digitalWrite(RELE_2, HIGH);
  
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleAllOff() {
  if (!server.authenticate(http_username, http_password)) return server.requestAuthentication();
  
  rele1State = "off";
  rele2State = "off";
  digitalWrite(RELE_1, LOW);
  digitalWrite(RELE_2, LOW);
  
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleRelayControl(int pin, String &state, bool turnOn) {
  digitalWrite(pin, turnOn ? HIGH : LOW);
  state = turnOn ? "on" : "off";
  
  server.sendHeader("Location", "/");
  server.send(303);
}

// *************** SETUP ***************
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Configuração dos pinos
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(RELE_1, OUTPUT);
  pinMode(RELE_2, OUTPUT);

  // Inicialização dos dispositivos
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(RELE_1, LOW);
  digitalWrite(RELE_2, LOW);

  dht.begin();

  // Inicialização do SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("[ERRO] Falha ao inicializar SPIFFS");
    while(1) delay(1000);
  }
  listSPIFFSFiles();

  // Conexão Wi-Fi
  WiFi.setHostname(hostname);
  WiFi.begin(ssid, password);
  
  Serial.print("[WiFi] Conectando à rede ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n[WiFi] Conectado!");
  Serial.print("[WiFi] IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("[WiFi] Hostname: ");
  Serial.println(WiFi.getHostname());

  // mDNS
  if (!MDNS.begin(hostname)) {
    Serial.println("[ERRO] Falha ao iniciar mDNS");
  } else {
    Serial.println("[mDNS] Iniciado");
  }

  // Configuração do servidor web
  server.on("/", handleRoot);
  server.on("/dht", handleDHTData);
  server.on("/on", handleAllOn);
  server.on("/off", handleAllOff);
  server.on("/26/on", []() { handleRelayControl(RELE_1, rele1State, true); });
  server.on("/26/off", []() { handleRelayControl(RELE_1, rele1State, false); });
  server.on("/27/on", []() { handleRelayControl(RELE_2, rele2State, true); });
  server.on("/27/off", []() { handleRelayControl(RELE_2, rele2State, false); });

  server.begin();
  Serial.println("[HTTP] Servidor iniciado");
}

// *************** LOOP ***************
void loop() {
  server.handleClient();
  
  // Atualiza os sensores a cada 30 segundos
  static unsigned long lastSensorRead = 0;
  if (millis() - lastSensorRead > 30000) {
    lerSensorDHT();
    lastSensorRead = millis();
  }
}