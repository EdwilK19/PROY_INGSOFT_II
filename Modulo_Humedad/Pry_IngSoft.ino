
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>

#include <WiFiClient.h>


// Se definen las credenciales de red
const char* ssid ="ESP32";
const char* password ="12345678";

//Asignacion de pines y variables a utilizar
int sensor_pin = A0;
int humedad;
int val_aire = 0;
int pin_bomba = D2;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.print("Obteniendo datos del sensor...");
  delay(2000);

  WiFi.begin(ssid, password);
  Serial.print("Conectando...");
  while (WiFi.status()!= WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conexión OK!");
  Serial.print("IP Local: ");
  Serial.println(WiFi.localIP());

  //Establecer pin_bomba como salida
  pinMode(pin_bomba, OUTPUT);
}

//Lectura de nivel de humedad
void loop(){
    humedad = analogRead(sensor_pin);
    humedad = map(humedad,847,535,0,100);
    Serial.print("Humedad : ");
    Serial.print(humedad);
    Serial.println(" %");
    delay(500);

    //Condicion para activacion de bomba
    if(humedad <= 30){
      digitalWrite(pin_bomba, HIGH);
      Serial.println("Bomba activada");
    }
    else
    {
      digitalWrite(pin_bomba, LOW);
      Serial.println("Bomba desactivada");
    }
    EnvioDatos();
}

//Rutina de envio de datos por POST
void EnvioDatos(){
  if (WiFi.status() == WL_CONNECTED){ 
     HTTPClient http;  //se crea el objeto http
     String datos_a_enviar = "humedad=" + String(humedad);  

     http.begin(client,"http://ggsxcloud.website/espm_humedad.php");
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
