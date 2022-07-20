int ledPin = 2; // Pin de referencia al led en la esp8266

int ldrPin = 0; // LDR en el pin analogico 0



int ldrValue = 0; //inicializacion de la variable que almacenara la lectura

 

void setup() {

  Serial.begin(9600);

  pinMode(ledPin,OUTPUT);

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
