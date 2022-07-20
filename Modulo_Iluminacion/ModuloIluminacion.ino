#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>

// Se definen las credenciales de red
const char* ssid ="ESP32";
const char* password ="12345678";
WiFiClient client;

int ledPin = 2; // Pin de referencia al led en la esp8266

int ldrPin = 0; // LDR en el pin analogico 0



int ldrValue = 0; //inicializacion de la variable que almacenara la lectura



void setup() {

  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Conectando...");
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexión OK!");
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());

}



void loop() {

  ldrValue = analogRead(ldrPin); //se hace la lectura por el pin analogico 0

  Serial.println(ldrValue); //se imprime el valor en monitor

  // condición para encender el led dependiendo de la intensidad de luz leída

  if (ldrValue >= 100){

    digitalWrite(ledPin,HIGH);

  }

  else {

    digitalWrite(ledPin,LOW);

  }

  delay(500);

}

void EnvioDatos(){
  if (WiFi.status() == WL_CONNECTED){
     HTTPClient http;  //se crea el objeto http
     String datos_a_enviar = "iluminacionm3=" + String(ldrValue);

     http.begin(client,"http://ggsxcloud.website/espm_iluminacionM3.php");
     http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // defino texto plano..

     int codigo_respuesta = http.POST(datos_a_enviar);

     if (codigo_respuesta>0){
      Serial.println("Código HTTP: "+ String(codigo_respuesta));
        if (codigo_respuesta == 200){
          String cuerpo_respuesta = http.getString();
          Serial.println("El servidor respondió: ");
          Serial.println(cuerpo_respuesta);
        }
     } else {
        Serial.print("Error enviado POST, código: ");
        Serial.println(codigo_respuesta);
     }

       http.end();  //se libera recursos recursos

  } else {
     Serial.println("Error en la conexion WIFI");
  }
  delay(3000); //espera 3s
}
