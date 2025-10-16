// ...existing code...
#include <Arduino.h>
#include <PID_v1.h>
#include <WiFi.h>
#include <WebServer.h>

// --- Configurações WiFi (edita) ---
const char* WIFI_SSID = "IEFP-Formacao";
const char* WIFI_PASS = "";

// Hardware
#define LDR_PIN 34
#define PWM_PIN 23

// PWM config
const int pwmChannel = 0;
const int freq = 20000;     // 20 kHz
const int resolution = 10;  // 0..1023
const int MAX_PWM = (1 << resolution) - 1;

// PID / leitura
double setpoint = 2000;            // alvo LDR 0..4095
double inputVal = 0, outputVal = 0;
double Kp = 2.0, Ki = 0.02, Kd = 0.08;
PID myPID(&inputVal, &outputVal, &setpoint, Kp, Ki, Kd, DIRECT);

// filtragem / suavização / ramp
const int AVG_SAMPLES = 12;
const unsigned long PID_SAMPLE_MS = 500;
const int DEADBAND = 12;
double prevOutput = 0;
const double SMOOTH_ALPHA = 0.18;
const double MAX_STEP_PER_SEC = 700.0;

bool manualMode = false;
int manualPWM = 0;

WebServer server(80);
unsigned long lastPid = 0;

int readLdrAvg() {
  long sum = 0;
  for (int i = 0; i < AVG_SAMPLES; ++i) {
    sum += analogRead(LDR_PIN);
    delay(3);
  }
  return (int)(sum / AVG_SAMPLES);
}

String pageHTML() {
  // HTML com placeholders que substituimos abaixo
  String s = R"rawliteral(<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Gestão Luz - ESP32 (24V)</title>
<style>
body{font-family:Arial;margin:20px;}
label{display:block;margin-top:10px;}
.row{display:flex;gap:10px;align-items:center;flex-wrap:wrap;}
.card{border:1px solid #ddd;padding:10px;border-radius:6px;margin-top:10px;}
input[type=range]{width:320px;}
small.note{color:#666}
</style>
</head>
<body>
<h2>Gestão intensidade (ESP32) - Fonte 24V</h2>
<div class="card">
  <div class="row">
    <label>Setpoint (0-4095): <span id="sp_val">__SETPOINT__</span></label>
    <input id="setpoint" type="range" min="0" max="4095" value="__SETPOINT__" oninput="updateSP(this.value)">
    <button onclick="setAuto()">Auto</button>
    <button onclick="setManual()">Manual</button>
  </div>
  <div class="row">
    <label>Manual PWM (0-__MAX_PWM__): <span id="mp">-</span></label>
    <input id="manual" type="range" min="0" max="__MAX_PWM__" value="0" oninput="updateManual(this.value)">
  </div>
  <div style="margin-top:8px;">
    <label>Kp: <input id="kp" type="number" step="0.1" value="__KP__" onchange="tune()"></label>
    <label>Ki: <input id="ki" type="number" step="0.001" value="__KI__" onchange="tune()"></label>
    <label>Kd: <input id="kd" type="number" step="0.1" value="__KD__" onchange="tune()"></label>
    <button onclick="resetTunings()">Reset</button>
  </div>
  <div style="margin-top:8px;">
    <p>Sensor: <span id="sensor">-</span> &nbsp; PWM: <span id="pwm">-</span> &nbsp; Modo: <span id="mode">-</span></p>
    <p class="note">Aviso: ligar GND24V ao GND do ESP32 se não houver isolamento.</p>
  </div>
</div>

<div class="card">
  <canvas id="chart" width="800" height="250"></canvas>
  <p style="font-size:12px;color:#666">Gráfico: intensidade LDR (últimos 60 pontos)</p>
</div>

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script>
let chart;
let maxPoints = 60;
function initChart(){
  const ctx = document.getElementById('chart').getContext('2d');
  chart = new Chart(ctx, {
    type: 'line',
    data: {
      labels: Array(maxPoints).fill(''),
      datasets: [
        { label: 'LDR', data: Array(maxPoints).fill(null), borderColor: 'orange', backgroundColor: 'rgba(255,165,0,0.2)', tension: 0.2 },
        { label: 'Setpoint', data: Array(maxPoints).fill(null), borderColor: 'blue', borderDash: [5,5], fill:false }
      ]
    },
    options: { animation:false, scales: { y: { min: 0, max: 4095 } } }
  });
}
function pushPoint(val, sp){
  chart.data.datasets[0].data.push(val);
  chart.data.datasets[1].data.push(sp);
  if(chart.data.datasets[0].data.length > maxPoints){
    chart.data.datasets[0].data.shift();
    chart.data.datasets[1].data.shift();
  }
  chart.update();
}
function fetchStatus(){
  fetch('/status').then(r=>r.json()).then(j=>{
    document.getElementById('sensor').innerText = j.input;
    document.getElementById('pwm').innerText = j.pwm;
    document.getElementById('sp_val').innerText = j.setpoint;
    document.getElementById('mode').innerText = j.mode ? 'MANUAL' : 'AUTO';
    document.getElementById('manual').value = j.pwm;
    document.getElementById('mp').innerText = j.pwm;
    document.getElementById('kp').value = j.kp;
    document.getElementById('ki').value = j.ki;
    document.getElementById('kd').value = j.kd;
    pushPoint(j.input, j.setpoint);
  }).catch(e=>console.log('err',e));
}
function updateSP(v){ document.getElementById('sp_val').innerText = v; fetch('/setpoint?value='+v); }
function setManual(){ fetch('/mode?m=manual'); }
function setAuto(){ fetch('/mode?m=auto'); }
function updateManual(v){ document.getElementById('mp').innerText = v; fetch('/manual?value='+v); }
function tune(){ const kp = document.getElementById('kp').value; const ki = document.getElementById('ki').value; const kd = document.getElementById('kd').value; fetch('/tune?kp='+kp+'&ki='+ki+'&kd='+kd); }
function resetTunings(){ document.getElementById('kp').value = '__KP__'; document.getElementById('ki').value = '__KI__'; document.getElementById('kd').value = '__KD__'; tune(); }
window.onload = function(){ initChart(); fetchStatus(); setInterval(fetchStatus,1000); };
</script>
</body>
</html>
)rawliteral";

  s.replace("__MAX_PWM__", String(MAX_PWM));
  s.replace("__KP__", String(Kp));
  s.replace("__KI__", String(Ki));
  s.replace("__KD__", String(Kd));
  s.replace("__SETPOINT__", String((int)setpoint));
  return s;
}

void handleRoot(){
  server.send(200, "text/html", pageHTML());
}

void handleStatus(){
  String json = "{";
  json += "\"input\":" + String((int)inputVal) + ",";
  json += "\"pwm\":" + String((int)round(prevOutput)) + ",";
  json += "\"setpoint\":" + String((int)setpoint) + ",";
  json += "\"mode\":" + String(manualMode ? 1 : 0) + ",";
  json += "\"kp\":" + String(Kp, 6) + ",";
  json += "\"ki\":" + String(Ki, 8) + ",";
  json += "\"kd\":" + String(Kd, 6);
  json += "}";
  server.send(200, "application/json", json);
}

void handleSetpoint(){
  if (server.hasArg("value")) {
    int v = server.arg("value").toInt();
    setpoint = constrain(v, 0, 4095);
  }
  server.send(200, "text/plain", "OK");
}

void handleManual(){
  if (server.hasArg("value")) {
    int v = server.arg("value").toInt();
    manualPWM = constrain(v, 0, MAX_PWM);
    manualMode = true;
    prevOutput = manualPWM;
    myPID.SetMode(MANUAL);
  }
  server.send(200, "text/plain", "OK");
}

void handleMode(){
  if (server.hasArg("m")) {
    String m = server.arg("m");
    if (m == "manual") {
      manualMode = true;
      myPID.SetMode(MANUAL);
    } else {
      manualMode = false;
      myPID.SetMode(AUTOMATIC);
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleTune(){
  bool changed = false;
  if (server.hasArg("kp")) { Kp = server.arg("kp").toFloat(); changed = true; }
  if (server.hasArg("ki")) { Ki = server.arg("ki").toFloat(); changed = true; }
  if (server.hasArg("kd")) { Kd = server.arg("kd").toFloat(); changed = true; }
  if (changed) myPID.SetTunings(Kp, Ki, Kd);
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  delay(100);

  analogSetPinAttenuation(LDR_PIN, ADC_11db);

  pinMode(PWM_PIN, OUTPUT);
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(PWM_PIN, pwmChannel);

  myPID.SetOutputLimits(0, MAX_PWM);
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(PID_SAMPLE_MS);
  myPID.SetTunings(Kp, Ki, Kd);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Conectando WiFi");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    Serial.print(".");
    delay(500);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("WiFi fail: iniciando AP modo.");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ESP32_Light_24V");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
  }

  server.on("/", handleRoot);
  server.on("/status", handleStatus);
  server.on("/setpoint", handleSetpoint);
  server.on("/manual", handleManual);
  server.on("/mode", handleMode);
  server.on("/tune", handleTune);
  server.begin();

  Serial.println("Web server iniciado.");
  Serial.println("Editar WIFI_SSID/WIFI_PASS em main.cpp se necessário.");
}

void loop() {
  server.handleClient();

  inputVal = readLdrAvg();
  double error = setpoint - inputVal;

  if (manualMode) {
    ledcWrite(pwmChannel, (int)manualPWM);
    prevOutput = manualPWM;
  } else {
    if (abs(error) <= DEADBAND) {
      ledcWrite(pwmChannel, (int)round(prevOutput));
    } else {
      if (millis() - lastPid >= PID_SAMPLE_MS) {
        lastPid = millis();
        myPID.Compute();
        double target = SMOOTH_ALPHA * outputVal + (1.0 - SMOOTH_ALPHA) * prevOutput;
        target = constrain(target, 0.0, (double)MAX_PWM);
        double maxStep = MAX_STEP_PER_SEC * (PID_SAMPLE_MS / 1000.0);
        double delta = target - prevOutput;
        if (fabs(delta) > maxStep) delta = (delta > 0) ? maxStep : -maxStep;
        double newOut = prevOutput + delta;
        newOut = constrain(newOut, 0.0, (double)MAX_PWM);
        ledcWrite(pwmChannel, (int)round(newOut));
        prevOutput = newOut;
      }
    }
  }

  delay(20);
}
// ...existing code...