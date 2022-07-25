#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>

#include <WiFiClient.h>
#include <SPI.h>
#include <MFRC522.h>
constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag,tag1,tag2;
 int huev=0,huevtag1=0,huevtag2=0;
   int x=0,b=0;
   int a=10000;
   int e=100;
const char* ssid ="COWIFI181040130/0";
const char* password ="WiFi-86359240";
WiFiClient client;   
void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  pinMode(D8, OUTPUT);
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
 
  

  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
      
    }
    Serial.println(tag);
    if (tag == "10124111548") {
      tag1=tag;
      Serial.println("Acceso concedido!");
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
       delay(100);
      digitalWrite(D8, LOW);
     delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      x++;
      if (x<2)
      delay(a);
      else
      delay (e);
      if(x>1)
      {
        
        huevtag1++;
        Serial.print("huevos tag1");
    Serial.print('\n');
     Serial.print(huevtag1);
    Serial.print('\n');
    delay(100);
    x=0;
    huev++;
    
      }
      
      
    }
      else if (tag == "2251121322") {
        tag2=tag;
      Serial.println("Acceso concedido!");
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
       delay(100);
      digitalWrite(D8, LOW);
     delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, HIGH);
      delay(100);
      digitalWrite(D8, LOW);
      b++;
      if (b<2)
      delay(a);
      else
      delay (e);
      if(b>1)
      {
        
        huevtag2++;
        Serial.print("huevos tag2");
    Serial.print('\n');
    Serial.print(huevtag2);
    Serial.print('\n');
delay(100);
b=0;
huev++;
      }
      
    }else {
      Serial.println("Acceso Denegado!");
      digitalWrite(D8, HIGH);
      delay(2000);
      digitalWrite(D8, LOW);
    }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
 
    Serial.print("huevos");
    Serial.print('\n');
    Serial.print(huev);
    Serial.print('\n');
    delay(100);
  

  
}
