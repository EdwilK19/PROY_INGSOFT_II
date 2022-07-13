#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "DHTesp.h"
#include "heltec.h"
DHTesp dht;

// Pines conectados al sensor y a los relés
int pinReleBombillo = 13;
int pinReleVentilador = 2;
int pinSensorTemp = 27;

// Inicializar variables
float tempActual = 0;
float maxTempAlta = 26;
float maxTempBaja = 25.5;

AsyncWebServer server(80);

const char* ssid = "No se conecte :L";
const char* password = "RedPrueba1";

const char* PARAM_INPUT_1 = "maxTempAlta";
const char* PARAM_INPUT_2 = "maxTempBaja";

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Maxima Temperatura Alta: <input type="text" name="maxTempAlta">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    Maxima Temperatura Baja: <input type="text" name="maxTempBaja">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  pinMode(pinReleBombillo, OUTPUT);
  pinMode(pinReleVentilador, OUTPUT);
  dht.setup(27, DHTesp::DHT11);
  pinMode(LED, OUTPUT);

  // Estado inicial
  digitalWrite(pinReleBombillo, HIGH);
  digitalWrite(pinReleVentilador, HIGH);
  digitalWrite(LED, LOW);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, false /*Serial Enable*/);
  Heltec.display->clear();

  // Establece la conexión WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Conexion de WiFi Fallida!");
    return;
  }
  Serial.println();
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Envía página web con input fields al cliente
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // Solicitud GET del valor del primer input en <ESP_IP>/get?maxTempAlta=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      maxTempAlta = inputMessage.toFloat();
      inputParam = PARAM_INPUT_1;
    }
    // Solicitud GET del valor del segundo input en <ESP_IP>/get?maxTempBaja=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      maxTempBaja = inputMessage.toFloat();
      inputParam = PARAM_INPUT_2;
    }
    // Cuando no se realiza otra solicitud.
    else {
      inputMessage = "No se envió ningún mensaje";
      inputParam = "none";
    }
    // Comprueba que efectivamente se han guardado los valores de los inputs.
    Serial.println("Maxima Temperatura Alta: " + (String)maxTempAlta);
    Serial.println("Maxima Temperatura Baja: " + (String)maxTempBaja);
    // Envía al cliente una comprobación de lo introducido.
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field ("
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  regularTemp();
  delay(2000);
}

void regularTemp() {
  tempActual = medirTemp();
  mostrarInfo(0);
  delay(2000);
  if(tempActual>maxTempAlta){
    while(tempActual>maxTempAlta){
      activarVentilador();
      mostrarInfo(1);
      delay(2000);
      tempActual = medirTemp();
    }
    apagarVentilador();
    mostrarInfo(3);
    delay(2000);
  } else if (tempActual<maxTempBaja){
    while(tempActual<maxTempBaja) {
      activarBombillo();
      mostrarInfo(2);
      delay(2000);
      tempActual = medirTemp();
    }
    apagarBombillo();
    mostrarInfo(4);
    delay(2000);
  }
}

float medirTemp() {
  float temp = dht.getTemperature();
  return temp;
}

void activarBombillo() {
  digitalWrite(pinReleBombillo, LOW);
}

void activarVentilador() {
  digitalWrite(pinReleVentilador, LOW);
}

void apagarBombillo() {
  digitalWrite(pinReleBombillo, HIGH);
}

void apagarVentilador() {
  digitalWrite(pinReleVentilador, HIGH);
}

void mostrarInfo(int opcion) {
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Temperatura: " + (String)tempActual + "°C");
  if(opcion != 0) {
    switch(opcion) {
      case 1:
        Heltec.display->drawString(0, 12, "Maxima Temperatura");
        Heltec.display->drawString(0, 24, "Alta (" + (String)maxTempAlta + ") superada");
        Heltec.display->drawString(0, 36, "Sistema de enfriamiento");
        Heltec.display->drawString(0, 48, "activado");
        break;
      case 2:
        Heltec.display->drawString(0, 12, "Maxima Temperatura");
        Heltec.display->drawString(0, 24, "Baja (" + (String)maxTempBaja + ")  superada");
        Heltec.display->drawString(0, 36, "Sistema de calefaccion");
        Heltec.display->drawString(0, 48, "activado");
        break;
      case 3:
        Heltec.display->drawString(0, 12, "Temperatura regulada");
        Heltec.display->drawString(0, 24, "Sistema de enfriamiento");
        Heltec.display->drawString(0, 36, "apagado");
        break;
      case 4:
        Heltec.display->drawString(0, 12, "Temperatura regulada");
        Heltec.display->drawString(0, 24, "Sistema de calefaccion");
        Heltec.display->drawString(0, 36, "apagado");
        break;
      default: break;
    }
  }
  Heltec.display->display();
}
