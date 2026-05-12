#include <DHT.h>
#include <WebServer.h>
#include <WiFi.h>

// ===== Sensor DHT =====
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
WebServer server(8080);

// ===== LEDs =====
const int ledVermelho = 17;
const int ledAmarelo  = 5;
const int ledVerde    = 18;

// ===== Modos =====
int modo = 0; 
// 0 = desligado
// 1 = ligado
// 2 = automatico

void setModo(int novoModo) {
  modo = novoModo;

  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);

  if (modo == 0) {
    digitalWrite(ledVermelho, HIGH);
    Serial.println("Modo DESLIGADO (LED Vermelho)");
    Serial.println("Comandos: 0=desligado | 1=ligado | 2=automatico");
  }
  else if (modo == 1) {
    digitalWrite(ledVerde, HIGH);
    Serial.println("Modo LIGADO (LED Verde)");
    Serial.println("Comandos: s=ler sensor | n=nao ler | 0=desligado | 1=ligado | 2=automatico");
  }
  else if (modo == 2) {
    digitalWrite(ledAmarelo, HIGH);
    Serial.println("Modo AUTOMATICO (LED Amarelo) - Lendo a cada 2 segundos");
    Serial.println("Comandos: 0=desligado | 1=ligado | 2=automatico");
  }
}

float t;
float u;

void lerSensor() {
  if (modo == 0) return;
  u = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(u) || isnan(t)) {
    Serial.println("ERRO: Falha ao ler o sensor!");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(u);
  Serial.print("% | Temperatura: ");
  Serial.print(t);
  Serial.println(" °C");
}

void handleData() {
  if (modo != 0){
    lerSensor();
  }

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

  String json = "{";
  json += "\"temperature\":";
  json += t;
  json += ",\"humidity\":";
  json += u;
  json += ",\"mode\":";
  json += modo;
  json += "}";

  server.send(200, "application/json", json);
}

void handleModo() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");

  if (server.hasArg("plain")) {

    String body = server.arg("plain");

    if (body.indexOf("\"modo\":0") > -1) setModo(0);
    if (body.indexOf("\"modo\":1") > -1) setModo(1);
    if (body.indexOf("\"modo\":2") > -1) setModo(2);
  }

  server.send(200, "application/json", "{\"status\":\"ok\"}");
}

void setup() {
  Serial.begin(115200);

  WiFi.begin("nome do wifi", "senha do wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // Imprime pontinhos enquanto espera
  }
  Serial.println(WiFi.localIP());

  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);

  dht.begin();

  server.on("/data", handleData);
  server.on("/modo", handleModo);
  server.begin();  // Iniciar servidor web

  setModo(0); // começa desligado
}

void loop() {
  server.handleClient();
  // Lê comandos seriais
  if (Serial.available()) {
    char comando = Serial.read();

    if (comando == '0') {
      setModo(0);
    }
    else if (comando == '1') {
      setModo(1);
    }
    else if (comando == '2') {
      setModo(2);
    }
    else if (comando == 's' && modo == 1) {
      lerSensor();  // Lê e volta a aguardar
    }
    else if (comando == 'n' && modo == 1) {
      Serial.println("Aguardando proximo comando...");
      // Não faz nada, só aguarda
    }
    else (Serial.println("Comando invalido, digite novamente"));
  }

  // Executa ações de cada modo
  if (modo == 0) {
    delay(100);
  }
  else if (modo == 1) {
    delay(100);  // Aguarda comandos 's' ou 'n' ou mudança de modo
  }
  else if (modo == 2) {
    lerSensor();
    delay(2000);
  }
}