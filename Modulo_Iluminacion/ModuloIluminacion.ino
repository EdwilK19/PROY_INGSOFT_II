// Pines y variables a utilizar
int pinsensor = 0;
int value = 0;
char led = 13;


void setup() {
  // Establece la velocidad de datos en bits por segundo para comunicarse con la computadora
  Serial.begin(9600);
}

//Lectura del nivel de iluminación
void loop() {
  value = analogRead(pinsensor);
  Serial.println(value, DEC);
  delay(500);


  //Si la luz detectada es mayor a 0 encender el led
  if (value > 0) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}
