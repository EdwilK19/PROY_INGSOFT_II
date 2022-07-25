#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);// si no te sale con esta direccion  puedes usar (0x3f,16,2)||(0x20,16,2)
#include "Sodaq_DS3231.h"
#include <SoftwareSerial.h>
// Creamos un puerto serie virtual para la conexión con el modulo Wifi
SoftwareSerial Wifi(4, 3); // Pin RX, Pin TX

char DiaSemana[][4] = {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};
    // La linea fija la fecha, hora y dia de la semana, se debe suprimir la linea en la segunda carga
    // Ejemplo 2018 noviembre 11, 08:00:00  dia 6-Sabado (0=Dom, 1=Lun, 2=Mar, 3=Mie, 4=Jue, 5=Vie, 6=Sab)
    DateTime dt(2022, 07, 24, 21, 00, 0, 0);

void setup() {
  
 // Creamos la conexion serie para el control desde la consola
    Serial.begin(9600);
    // Creamos la conexión con el modulo Wifi
    Wifi.begin(115200);


 pinMode(2,OUTPUT);
 
 rtc.begin(); 
 Wire.begin();

}

void loop() {
// Si hay datos desde el modulo Wifi
    if (Wifi.available())
    {
        // Leemos un caracter
        char c = BT1.read() ;
        // Y lo escribimos en el puerto de la consola
        Serial.print(c);
    }
    // Si Hay datos disponibles desde la consola
    if (Serial.available())
    {
        // Leemos un caracter
        char c = Serial.read();
        // Y lo escribimos en el modulo Wifi
        Wifi.print(c);
     }


  DateTime now = rtc.now();

int hora    =now.hour();
int minuto  =now.minute();
int segundo = now.second();
   if(minuto >=10 && minuto <=11 ){
   digitalWrite(2,true);
   }
   else {
   digitalWrite(13,false);
   }
}
