/*  
  Rui Santos & Sara Santos - Random Nerd Tutorials
  https://RandomNerdTutorials.com/esp32-web-server-beginners-guide/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Declarar que as funções existem
void handleRoot();
void handleAllOn();
void handleAllOff();

// Replace with your network credentials
const char* ssid = "IEFP-Formacao";
const char* password = "";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 25;
String output26State = "off";
String output27State = "off";

// Create a web server object
WebServer server(8080);

// Função para LIGAR ambos os GPIOs (para o botão "LIGAR")
void handleAllOn() {
  output26State = "on";
  output27State = "on";
  digitalWrite(output26, HIGH);
  digitalWrite(output27, HIGH);
  handleRoot();
}

// Função para DESLIGAR ambos os GPIOs (para o botão "DESLIGAR")
void handleAllOff() {
  output26State = "off";
  output27State = "off";
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);
  handleRoot();
}

// Function to handle turning GPIO 26 on
void handleGPIO26On() {
  output26State = "on";
  digitalWrite(output26, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 26 off
void handleGPIO26Off() {
  output26State = "off";
  digitalWrite(output26, LOW);
  handleRoot();
}

// Function to handle turning GPIO 27 on
void handleGPIO27On() {
  output27State = "on";
  digitalWrite(output27, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 27 off
void handleGPIO27Off() {
  output27State = "off";
  digitalWrite(output27, LOW);
  handleRoot();
}

// Função para servir a página principal
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>";
  html += "@font-face { font-family: 'ArtDeco'; src: url('ArtDeco.woff') format('woff'); }";
  html += "body { background-color: #f5f0e6; color: #2d2d2d; font-family: 'ArtDeco', 'Georgia', serif; text-align: center; margin: 0; padding: 0; }";
  html += "h1 { font-size: 48px; margin-top: 30px; letter-spacing: 2px; color: #b29400; }";
  html += ".button { background-color: #000000; border: 4px double #b29400; color: #f5f0e6; padding: 14px 36px; text-decoration: none; font-size: 28px; margin: 10px; cursor: pointer; font-weight: bold; }";
  html += ".button2 { background-color: #b29400; color: #000000; border: 4px double #000000; }";
  html += "</style></head>";

  html += "<body>";
  html += "<h1>Rui Pais Pereira Web Server</h1>";
  html += "<a class=\"button\" href=\"/on\">LIGAR</a>";
  html += "<a class=\"button button2\" href=\"/off\">DESLIGAR</a>";

  // Display GPIO 26 controls
  html += "<p>GPIO 26 - State " + output26State + "</p>";
  if (output26State == "off") {
    html += "<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>";
  } else {
    html += "<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>";
  }
  // Display GPIO 27 controls
  html += "<p>GPIO 27 - State " + output27State + "</p>";
  if (output27State == "off") {
    html += "<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>";
  } else {
    html += "<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>";
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server to handle different routes
  server.on("/", handleRoot);
  server.on("/on", handleAllOn);     // Botão LIGAR
  server.on("/off", handleAllOff);   // Botão DESLIGAR
  server.on("/26/on", handleGPIO26On);
  server.on("/26/off", handleGPIO26Off);
  server.on("/27/on", handleGPIO27On);
  server.on("/27/off", handleGPIO27Off);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}