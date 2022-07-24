#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16, 2); //de no salir esta direccion, usar (0x3f,16,2)||(0x20,16,2)
#include "Sodaq_DS3231.h"
char DiaSemana[][4] = {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};

    // La linea fija la fecha, hora y dia de la semana, se debe suprimir la linea en la segunda carga
    // Ejemplo 2018 noviembre 11, 08:00:00  dia 6-Sabado (0=Dom, 1=Lun, 2=Mar, 3=Mie, 4=Jue, 5=Vie, 6=Sab)
    // DateTime dt(2018, 11, 14, 22, 12, 0, 3);

void setup() {
  
 pinMode(2,OUTPUT);
 
 rtc.begin(); 
 Wire.begin();
 lcd.init();
 lcd.backlight();
 lcd.setCursor (0,0);
 lcd.print ("carlos");
 delay(2000);
 lcd.clear();
   // La linea fija la fecha, hora y dia de la semana, se debe suprimir la linea en la segunda carga 
   // rtc.setDateTime(dt);
}

void loop() {
  DateTime now = rtc.now();
    lcd.setCursor(0,0);
    lcd.print(DiaSemana[now.dayOfWeek()]);
    lcd.print(' ');
    lcd.print(now.date(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.print('/');
    lcd.setCursor(4,1);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC); 
   delay(1000);
   lcd.clear();
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
